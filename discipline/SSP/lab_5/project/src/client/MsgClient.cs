using System;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Collections.Generic;

using Messenger.Common;
using Messenger.Service;

namespace Messenger.Client
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
  
    public List<Messenger.Common.Message>
    getMessages(DateTime fromDate)
    {
      return Channel.getMessages(fromDate);
    }

    public void
    sendMessage (Messenger.Common.Message msg)
    {
      Channel.sendMessage(msg);
    }
  }

}