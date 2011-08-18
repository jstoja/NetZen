#include "NZMessage.hh"

NZMessage::NZMessage(NZConversation* parent, QString message,
		     NZMessageType messageType, QDateTime timeStamp) {
  mParent = parent;
  mMessage = message;
  mMessageType = messageType;
  mTimeStamp = timeStamp;
}

QString NZMessage::message(void) const {
  return mMessage;
}

NZMessageType NZMessage::messageType(void) const {
  return mMessageType;
}

QDateTime NZMessage::timeStamp(void) const {
  return mTimeStamp;
}

NZConversation* NZMessage::conversation(void) const {
  return mParent;
}
