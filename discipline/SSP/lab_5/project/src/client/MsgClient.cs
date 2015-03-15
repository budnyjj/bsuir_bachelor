using System;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Collections.Generic;

namespace Msg
{
  public class MsgClient : ClientBase<IMsgService>, IMsgService
  {
    public MsgClient(Binding binding, EndpointAddress address)
    : base(binding, address)
    {
    }

    public bool checkConnection()
    {
      return Channel.checkConnection();
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

}