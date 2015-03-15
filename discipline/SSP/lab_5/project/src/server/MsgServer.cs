using System;
using System.ServiceModel;
using System.Net.Sockets;
using System.Collections.Generic;

public class MsgService : IMsgService
{
  MsgDB db = null;

  public MsgService()
  {
    db = new MsgDB(MsgServer.dbPath);
  }

  public bool checkConnection()
  {
    return true;
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

public static class MsgServer
{
  public static int port;
  public static String dbPath;
  
  static int parsePort(string[] args)
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

  static String parseDBPath(string[] args)
    {
      String dbPath = "messages.sqlite";
      if (args.Length > 1)
        {
          dbPath = args[1];
        }
      return dbPath;
    }
  
  public static void Main(string[] args)
  {
    int port = parsePort(args);
    dbPath = parseDBPath(args);
    
    BasicHttpBinding binding = new BasicHttpBinding();
    Uri address = new Uri ("http://localhost:" + port.ToString());

    ServiceHost host = new ServiceHost(typeof(MsgService));

    host.AddServiceEndpoint (typeof(IMsgService), binding, address);       

    try
      { 
        host.Open();
        Console.WriteLine ("Press <Enter> to stop...");
        Console.ReadLine ();

      }
    catch (SocketException)
      {
        Console.WriteLine("Address already in use: " + address);            
      }
    finally
      {
        host.Close();            
      }
  }
}