using System;
using System.ServiceModel;
using System.Collections.Generic;

public class MsgService : IMsgService
{
  MsgDB db = null;

  public MsgService()
  {
    db = new MsgDB("messages.sqlite");
  }

  public List<Message> getAllMessages()
  {
    return db.selectMessages(new DateTime(0));
  }
  
  public List<Message> getMessages(DateTime fromDate)
  {
    return db.selectMessages(fromDate);        
  }

  public void sendMessage(Message msg)
  {
    db.insertMessage(msg);
  }
}

public class MsgServer
{
  static int ParsePort(string[] args)
  {
    int port = 8080;

    if (args.Length > 0)
      {
        try
          {
            port = Convert.ToInt32(args[0]);
          }
        catch (FormatException)
          {
            port = 8080;
          }
        catch (OverflowException)
          {
            port = 8080;
          }
      }

    // Port number should be in correct range
    if ((port < 1024) || (port > 65535))
      port = 8080;

    return port;
  }
  
  public static void Main(string[] args)
  {
    int port = ParsePort(args);
    
    BasicHttpBinding binding = new BasicHttpBinding();
    Uri address = new Uri ("http://localhost:" + port.ToString());

    ServiceHost host = new ServiceHost (typeof(MsgService));
    host.AddServiceEndpoint (typeof(IMsgService), binding, address);
    host.Open();
    
    Console.WriteLine ("Press <Enter> to stop...");
    Console.ReadLine ();

    host.Close();
  }
}