using System;

namespace Messenger.Common
{  
  public class Message
  {
    public String Sender
    {
      get;
      set;
    }

    public String Content
    {
      get;
      set;
    }
  
    public DateTime Timestamp
    {
      get;
      set;
    }
  
    public Message(String Sender, String Content, DateTime Timestamp)
    {
      this.Sender = Sender;
      this.Content = Content;
      this.Timestamp = Timestamp;
    }
  }
}