using NUnit.Framework;
using System;
using System.IO;
using System.Collections.Generic;

using Messenger.Server;
using Messenger.Common;

[TestFixture]
public class MsgDBTest : Assert
{
  MsgDB db = null;
  
  [SetUp]
  public void GetReady()
  {
    db = new MsgDB("test.sqlite");
  }

  [TearDown]
  public void Clean()
  {
    File.Delete("test.sqlite");
  }

  [Test]
  public void selectNoMessagesTest()
  {
    Message msg = new Message("Vasya", "Hello world!", DateTime.Now);
    db.insertMessage(msg);
    
    List<Message> oMsgs = db.selectMessages(DateTime.Now);
    Assert.IsEmpty(oMsgs);
  }

  [Test]
  public void selectAllMessagesTest()
  {
    DateTime dt = DateTime.Now;
    List<Message> iMsgs = new List<Message>();

    iMsgs.Add(new Message("Vasya1", "Hello world 1", dt));
    iMsgs.Add(new Message("Vasya2", "Hello world 2", dt));
    iMsgs.Add(new Message("Vasya3", "Hello world 3", dt));

    foreach (Message iMsg in iMsgs)
      {
        db.insertMessage(iMsg);        
      }
    
    List<Message> oMsgs = db.selectMessages(dt);

    for (int i = 0; i < iMsgs.Count; i++)
      {
        Assert.AreEqual(iMsgs[i].Sender,     oMsgs[i].Sender);
        Assert.AreEqual(iMsgs[i].Content,    oMsgs[i].Content);
        Assert.AreEqual(iMsgs[i].Timestamp,  oMsgs[i].Timestamp);            
      }
  }

  
  // An nice way to test for exceptions the class under test should 
  // throw is:
  /*
	[Test]
	[ExpectedException(typeof(ArgumentNullException))]
	public void OnValid() {
    ConcreteCollection myCollection;
    myCollection = new ConcreteCollection();
    ....
    AssertEquals ("#UniqueID", expected, actual);
    ....
    Fail ("Message");
	}
  */
}