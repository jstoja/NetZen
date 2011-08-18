#ifndef NZMESSAGE_HH_
#define NZMESSAGE_HH_

#include <QtCore/QString>
#include <QtCore/QDateTime>

class NZConversation;
class NZContact;

enum NZMessageType {
  nzReceivedMessage,
  nzSendMessage
};

class NZMessage {
public:
  NZMessage(NZConversation* parent, QString message,
	    NZMessageType messageType = nzSendMessage,
	    QDateTime timeStamp = QDateTime::currentDateTime());

  QString message(void) const;
  QDateTime timeStamp(void) const;
  NZMessageType messageType(void) const;
  NZConversation* conversation(void) const;

private:
  NZConversation* mParent;
  QString mMessage;
  NZMessageType mMessageType;
  QDateTime mTimeStamp;
};

#endif
