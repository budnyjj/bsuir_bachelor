using System;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Collections.Generic;

public class MsgClient : ClientBase<IMsgService>, IMsgService
{
  public MsgClient(Binding binding, EndpointAddress address)
  : base(binding, address)
  {
  }

  public List<Message> getAllMessages()
  {
    return Channel.getAllMessages();
  }

  public List<Message> getMessages(DateTime fromDate)
  {
    return Channel.getMessages(fromDate);
  }

  public void sendMessage (Message msg)
  {
    Channel.sendMessage(msg);
  }
}

// public class Test
// {
//   public static void Main (string [] args)
//   {
//     string name = args.Length > 0 ? args [0] : "Anonymous Joe";
//     var binding = new BasicHttpBinding (); 
//     var address = new EndpointAddress ("http://localhost:8080");
//     var client = new HelloClient (binding, address);
//     Console.WriteLine (client.Greet (name));
//   }
// }