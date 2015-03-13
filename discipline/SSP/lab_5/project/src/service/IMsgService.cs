using System;
using System.ServiceModel;
using System.Collections.Generic;

[ServiceContract]
public interface IMsgService
{
  [OperationContract]
  List<Message> getAllMessages();

  [OperationContract]
  List<Message> getMessages(DateTime fromDate);

  [OperationContract]
  void sendMessage (Message msg);
}