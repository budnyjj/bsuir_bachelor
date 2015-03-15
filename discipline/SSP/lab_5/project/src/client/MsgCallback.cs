using System;

namespace Messenger.Client
{
  public delegate void gotNewMessageCallback();
  public delegate void gotErrorCallback(String msg);
}