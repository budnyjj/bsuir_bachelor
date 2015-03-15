using System;
using System.ServiceModel;
using System.Collections.Generic;

[ServiceContract]
public interface IMsgService
{
  [FaultContract(typeof(FaultException))]
  [OperationContract]
  bool checkConnection();

  [FaultContract(typeof(FaultException))]
  [OperationContract]
  List<Message> getMessages(DateTime fromDate);

  [FaultContract(typeof(FaultException))]
  [OperationContract]
  void sendMessage(Message msg);
}