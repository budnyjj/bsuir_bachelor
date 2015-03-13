using System;
using System.ServiceModel;
using System.Collections.Generic;

using Gtk;
using Glade;

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
  Button refreshButton;

  [Widget]
  Button sendButton;

  String username = "";
  String uri = "";
  
  BasicHttpBinding binding = new BasicHttpBinding(); 
  MsgClient client = null;

  DateTime lastRefreshTimestamp = new DateTime(0);
  
  public MsgClientApp(string[] args)
  {
    Application.Init();
    
    Glade.XML gxml = new Glade.XML(null, "ui.glade", "mainWindow", null);
    gxml.Autoconnect(this);

    serverUriEntry.Text = "http://localhost:8080";

    disconnectButton.Sensitive = false;
    refreshButton.Sensitive = false;
    sendButton.Sensitive = false;
    
    Application.Run();
  }

  public void onConnect(object obj, EventArgs args)
  {
    EndpointAddress ea = null;
    try
      {
        ea = new EndpointAddress(serverUriEntry.Text);
      }
    catch (UriFormatException)
      {
        showErrorDialog("Cannot connect to server! " +
                        "Please, check connection details");
        return;
      }
    
    username = usernameEntry.Text.Trim();
    if (username.Length == 0)
      {
        showErrorDialog("Please, choose non-empty username!");
        return;        
      }

    
    client = new MsgClient(binding, ea);

    List<Message> messages = getNewMessages();

    if (messages == null)
      {
        return;
      }

    foreach (Message msg in messages)
      {
        appendMessageToConversation(msg);
      }
    
    disconnectButton.Sensitive = true;
    connectButton.Sensitive = false;

    serverUriEntry.Sensitive = false;
    usernameEntry.Sensitive = false;
    
    refreshButton.Sensitive = true;
    sendButton.Sensitive = true; 
  }

  public void onDisconnect(object obj, EventArgs args)
  {
    client = null;
    
    connectButton.Sensitive = true;
    disconnectButton.Sensitive = false;

    serverUriEntry.Sensitive = true;
    usernameEntry.Sensitive = true;
    
    refreshButton.Sensitive = false;
    sendButton.Sensitive = false;
  }

  public void onRefresh(object obj, EventArgs args)
  {
    List<Message> messages = getNewMessages();

    if (messages != null)
      {
        foreach (Message msg in messages)
          {
            appendMessageToConversation(msg);
          }        
      }
  }

  public void onSend(object obj, EventArgs args)
  {
    String content = messageTextView.Buffer.Text.Trim();
    if (content.Length == 0)
      {
        return;
      }

    messageTextView.Buffer.Text = "";
    
    Message sMsg = new Message(username, content, DateTime.Now);
    
    if (sendMessage(sMsg))
      {
        List<Message> messages = getNewMessages();
        if (messages != null)
          {
            foreach (Message rMsg in messages)
              {
                appendMessageToConversation(rMsg);
              }        
          }        
      }
  }
  
  public void onWindowDestroy(object obj, EventArgs args)
  {
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

  void appendMessageToConversation(Message msg)
  {
    String fmtMsg = "";
    fmtMsg += msg.Timestamp + " | " + msg.Sender + " >\n" + msg.Content + "\n\n";
    conversationTextView.Buffer.Text += fmtMsg;
  }

  List<Message> getNewMessages()
  {
    List<Message> messages = null;
    try
      {
        messages = client.getMessages(lastRefreshTimestamp);
        lastRefreshTimestamp = DateTime.Now;
      }
    catch (EndpointNotFoundException ex)
      {
        showErrorDialog("Cannot connect to server! " +
                        "Please, check connection details");             
      }
    return messages;
  }

  bool sendMessage(Message msg)
  {
    try
      {
        client.sendMessage(msg);
      }
    catch (EndpointNotFoundException ex)
      {
        showErrorDialog("Cannot connect to server! " +
                        "Please, check connection details");
        return false;
      }
    return true;
  }

  
  public static void Main(string[] args)
  {
    new MsgClientApp(args);
  }
}
