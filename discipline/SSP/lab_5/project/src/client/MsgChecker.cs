using System;
using System.ServiceModel;
using System.Collections.Generic;
using System.Threading;

using Gtk;
using Glade;

namespace Msg
{  
  public class MsgChecker
  {
    // Shared message client
    MsgClient _client = null;
    
    // New messages from server
    List<Message> _messages = null;
  
    // Lock for shared message client and messages list
    object _lock = null;

    // Callback to notify main thread about new messages
    gotNewMessagesCallback _callback = null;
    
    // Timestamp of last refresh
    DateTime _lrTimestamp = new DateTime(0);

    public MsgChecker(MsgClient client, List<Message> messages,
                      object shareLock, gotNewMessagesCallback callback)
    {
      _client = client;
      _messages = messages;
      _lock = shareLock;
      _callback = callback;
    }

    // Check new messages in quite way
    public void periodicalCheckNewMessages()
    {
      int maxTimeToSleep = 5000,
        minTimeToSleep = 200,
        curTimeToSleep = 0;
      bool gotNewMessages = false;
      
      while (true)
        {
          Thread.Sleep(curTimeToSleep);          
          List <Message> newMessages = null;
          
          lock(_lock)
            {       
              try
                {
                  newMessages = _client.getMessages(_lrTimestamp);
                  _lrTimestamp = DateTime.Now;
                }
              catch (EndpointNotFoundException)
                {
                  Console.WriteLine("Cannot connect to server! " +
                                    "Please, check connection details");           
                }
              catch (FaultException)
                {
                  continue; // Deal with Mono bug
                }
            
              if (newMessages != null)
                {
                  if (newMessages.Count > 0)
                    {
                      gotNewMessages = true;
                      // Append new messages to _messages
                      foreach (Message msg in newMessages)                        
                        _messages.Add(msg);                      
                      
                      // Increase timeToSleep
                      curTimeToSleep /= 2;
                      if (curTimeToSleep > maxTimeToSleep)
                        curTimeToSleep = maxTimeToSleep;
                    }
                  else // There is no new messages
                    {
                      gotNewMessages = false;
                      
                      // Decrease timeToSleep
                      curTimeToSleep *= 2;
                      if (curTimeToSleep < minTimeToSleep)
                        curTimeToSleep = minTimeToSleep;
                    }                
                }
            }
          if (gotNewMessages == true && _callback != null)
            Gtk.Application.Invoke(delegate { _callback(); });
        }
    }
  
    // Get new messages from server
    List<Message> getNewMessages()
    {
      List<Message> messages = null;
      try
        {
          messages = _client.getMessages(_lrTimestamp);
          _lrTimestamp = DateTime.Now;
        }
      catch (EndpointNotFoundException)
        {
          Console.WriteLine("Cannot connect to server! " +
                            "Please, check connection details");
          messages = null;
        }
      return messages; 
    }
  }

}