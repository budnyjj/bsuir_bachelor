using System;
using System.ServiceModel;
using System.Collections.Generic;
using System.Threading;

using Gtk;
using Glade;

namespace Msg
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
  
    MsgClient _client = null;
  
    MsgChecker _checker = null;
    object _checkerLock = new object();
    Thread _checkerThread = null;

    List<Message> _newMessages = new List<Message>();
  
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
                            "Please, check connection details...");
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
                          "Please, check connection details...");
          return;
        }
      
      _username = usernameEntry.Text.Trim();
      if (_username.Length == 0)
        {
          showErrorDialog("Please, choose non-empty username!");
          return;        
        }

      _client = new MsgClient(new BasicHttpBinding(), ea);          

      if (checkConnection() == false)
        {
          showErrorDialog("Cannot connect to server! " +
                          "Please, check connection details...");
          return;
        }

      disconnectButton.Sensitive = true;
      connectButton.Sensitive = false;

      serverUriEntry.Sensitive = false;
      usernameEntry.Sensitive = false;
    
      sendButton.Sensitive = true;

      conversationTextView.Buffer.Text = "";      
    
      _checker =
        new MsgChecker(_client, _newMessages, _checkerLock,
                       new gotNewMessagesCallback(appendMessagesToConversation));
      _checkerThread =
        new Thread(new ThreadStart(_checker.periodicalCheckNewMessages));
      _checkerThread.Start();
    }

    public void onDisconnect(object obj, EventArgs args)
    {
      // Need to pause/stop message checker
      _checkerThread.Abort();
      _checker = null;
      _client = null;
    
      connectButton.Sensitive = true;
      disconnectButton.Sensitive = false;

      serverUriEntry.Sensitive = true;
      usernameEntry.Sensitive = true;
    
      sendButton.Sensitive = false;
    }

    public void onSend(object obj, EventArgs args)
    {
      String content = messageTextView.Buffer.Text.Trim();
      if (content.Length == 0)
        return;
    
      Message msg = new Message(_username, content, DateTime.Now);
      if (sendMessage(msg) == true)
        messageTextView.Buffer.Text = "";
    }
  
    public void onWindowDestroy(object obj, EventArgs args)
    {
      // Need to pause/stop message checker
      _checkerThread.Abort();
      _checker = null;
      _client = null;
      Application.Quit();
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

    // Check connection to server
    bool checkConnection()
    {
      bool status = false;
      lock (_checkerLock)
        {          
          while (true)
            {
              try
                {
                  status = _client.checkConnection(); // status = true
                  break;
                }
              catch (EndpointNotFoundException)
                {
                  status = false;
                  break;
                }
              catch (FaultException)
                {
                  Console.WriteLine("Caught System.ServiceModel.FaultException");
                  continue; // Deal with Mono bug
                }
            }
        }
      return status;
    }
  
    // Send message to server
    // Return true if success, false otherwise
    bool sendMessage(Message msg)
    {
      bool status = false;
      lock(_checkerLock)
        {
          while (true)
            {            
              try
                {
                  _client.sendMessage(msg);
                  status = true;
                  break;
                }
              catch (EndpointNotFoundException)
                {
                  showErrorDialog("Cannot connect to server! " +
                                  "Please, check connection details...");
                  status = false;
                  break;
                }
              catch (FaultException)
                {
                  Console.WriteLine("Caught System.ServiceModel.FaultException");
                  continue; // Deal with Mono bug
                }
            }
        }
      return status;
    }

    void appendMessagesToConversation()
    {
      String fmtMessages = "";
      lock (_checkerLock)
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