using System;
using System.ServiceModel;
using System.Collections.Generic;
using System.Threading;

using Gtk;
using Glade;

using Messenger.Common;

namespace Messenger.Client
{  
  public class MsgDispatcher
  {
    // Shared message client
    MsgClient _client = null;
    
    // New messages from server
    List<Message> _messages = null;
  
    // Lock for shared messages list
    object _newMessagesLock = null;
    
    // Callback to notify main thread about new messages
    gotNewMessageCallback _newMsgCallback = null;

    // Callback to notify main thread about errors
    gotErrorCallback _errorCallback = null;
    
    // Timestamp of last refresh
    DateTime _lrTimestamp = new DateTime(0);

    public MsgDispatcher(EndpointAddress ea, List<Message> messages,
                         object newMessagesLock,
                         gotNewMessageCallback newMsgCallback,
                         gotErrorCallback errorCallback)
    {
      _client = new MsgClient(new BasicHttpBinding(), ea);
      _newMessagesLock = newMessagesLock;
      _messages = messages;
      _newMsgCallback = newMsgCallback;
      _errorCallback = errorCallback;
    }

    // Check new messages in quite way
    public void periodicalCheckNewMessages()
    {
      // Define time to sleep
      int maxTTS = 5000, minTTS = 200, curTTS = 200;
      bool gotNewMessages = false;
      
      while (true)
        {
          Thread.Sleep(curTTS);          
          List <Message> newMessages = null;
          
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
                      
                  // Decrease timeToSleep
                  curTTS /= 2;
                  if (curTTS < minTTS)
                    curTTS = minTTS;
                }
              else // There is no new messages
                {
                  gotNewMessages = false;

                  // Increase timeToSleep
                  curTTS *= 2;
                  if (curTTS > maxTTS)
                    curTTS = maxTTS;
                }                
            }
          if (gotNewMessages == true)
            {
              lock (_newMessagesLock)
                {
                  // Append new messages to _messages
                  foreach (Message msg in newMessages)                        
                    _messages.Add(msg);                                            
                }
              Gtk.Application.Invoke(delegate { _newMsgCallback(); });
            }
        }
    }
  
    // Check connection to server
    public bool checkConnection()
    {
      bool status = false;
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
      return status;
    }

    // Send message to server
    // Return true if success, false otherwise
    public bool sendMessage(Message msg)
    {
      bool status = false;
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
              Gtk.Application.Invoke(delegate
                { _errorCallback("Cannot connect to server! " +
                                 "Please, check connection details..."); });
              status = false;
              break;
            }
          catch (FaultException)
            {
              Console.WriteLine("Caught System.ServiceModel.FaultException");
              continue; // Deal with Mono bug
            }
        }
      return status;
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