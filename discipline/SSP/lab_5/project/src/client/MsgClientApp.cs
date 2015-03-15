using System;
using System.ServiceModel;
using System.Collections.Generic;
using System.Threading;

using Gtk;
using Glade;

using Messenger.Common;

namespace Messenger.Client
{
  public class MsgClientApp
  {
    [Widget]
    Window mainWindow;

    [Widget]
    Entry serverUriEntry;
  
    [Widget]
    Entry usernameEntry;

    [Widget]
    TextView conversationTextView;

    [Widget]
    TextView messageTextView;
  
    [Widget]
    Button connectButton;

    [Widget]
    Button disconnectButton;

    [Widget]
    Button sendButton;

    String _username = "";
  
    MsgDispatcher _dispatcher = null;
   
    Thread _checkNewMessagesThread = null;

    List<Message> _newMessages = new List<Message>();
    object _newMessagesLock = new object();
    
    public MsgClientApp(string[] args)
    {
      Application.Init();
    
      Glade.XML gxml = new Glade.XML(null, "ui.glade", "mainWindow", null);
      gxml.Autoconnect(this);

      this.conversationTextView.SizeAllocated += new SizeAllocatedHandler(scrollToEnd);
      
      serverUriEntry.Text = "http://localhost:8080";

      disconnectButton.Sensitive = false;
      sendButton.Sensitive = false;
      
      Application.Run();
    }

    public void onConnect(object obj, EventArgs args)
    {
      String uri = serverUriEntry.Text.Trim();
      if (uri.StartsWith("http://") == false)
          {
            showErrorDialog("URI Format is incorrect! " +
                            "Please, check connection details");
            return;
          }

      EndpointAddress ea = null;
      try
        {
          ea = new EndpointAddress(serverUriEntry.Text);
        }
      catch (UriFormatException)
        {
          showErrorDialog("URI Format is incorrect! " +
                          "Please, check connection details");
          return;
        }
      
      _username = usernameEntry.Text.Trim();
      if (_username.Length == 0)
        {
          showErrorDialog("Please, choose non-empty username!");
          return;        
        }

      _dispatcher =
        new MsgDispatcher(ea, _newMessages, _newMessagesLock,
                          new gotNewMessageCallback(appendMessagesToConversation),
                          new gotErrorCallback(showErrorDialog));

      if (_dispatcher.checkConnection() == false)
        {
          showErrorDialog("Cannot connect to server! " +
                          "Please, check connection details");
          return;
        }

      disconnectButton.Sensitive = true;
      connectButton.Sensitive = false;

      serverUriEntry.Sensitive = false;
      usernameEntry.Sensitive = false;
    
      sendButton.Sensitive = true;

      conversationTextView.Buffer.Text = "";      

      _checkNewMessagesThread =
        new Thread(new ThreadStart(_dispatcher.periodicalCheckNewMessages));
      _checkNewMessagesThread.Start();
    }

    public void onDisconnect(object obj, EventArgs args)
    {
      disconnectFromServer();
    }

    public void onSend(object obj, EventArgs args)
    {
      String content = messageTextView.Buffer.Text.Trim();
      if (content.Length == 0)
        return;
    
      Message msg = new Message(_username, content, DateTime.Now);

      if (_dispatcher.sendMessage(msg) == true)
        messageTextView.Buffer.Text = "";
      else // cannot connect to server
        {
          disconnectFromServer();
        }
    }
  
    public void onWindowDestroy(object obj, EventArgs args)
    {
      if (_dispatcher != null)
        disconnectFromServer();
      
      Application.Quit();
    }

    void disconnectFromServer()
    {
      // Need to pause/stop message checker
      _checkNewMessagesThread.Abort();
      _dispatcher = null;
    
      connectButton.Sensitive = true;
      disconnectButton.Sensitive = false;

      serverUriEntry.Sensitive = true;
      usernameEntry.Sensitive = true;
    
      sendButton.Sensitive = false;
    }
    
    void showErrorDialog(String errorMessage)
    {
      MessageDialog md = new MessageDialog(mainWindow,
                                           DialogFlags.DestroyWithParent,
                                           MessageType.Error,
                                           ButtonsType.Close,
                                           errorMessage);
      md.Run();
      md.Destroy();
    }

    void appendMessagesToConversation()
    {
      String fmtMessages = "";
      lock (_newMessagesLock)
        {       
          foreach (Message msg in _newMessages)
            {
              fmtMessages +=
                msg.Timestamp + " | " +
                msg.Sender + " >\n" +
                msg.Content + "\n\n";
            }
          _newMessages.Clear();
        }
      conversationTextView.Buffer.Text += fmtMessages;
    }

    void scrollToEnd(object sender, Gtk.SizeAllocatedArgs e)
    {
      conversationTextView.ScrollToIter(conversationTextView.Buffer.EndIter,
                                        0, false, 0, 0);
    }
    
    public static void Main(string[] args)
    {
      new MsgClientApp(args);
    }
  }
}