#ifndef NZCONVERSATION_HH_
#define NZCONVERSATION_HH_

#include <QtCore/QObject>
#include <QtCore/QList>

class NZMessage;
class NZContact;

class NZConversation : public QObject {
  Q_OBJECT

public:
  NZConversation(NZContact* contactTo, QObject* parent = NULL);
  ~NZConversation(void);

public slots:
  void addMessage(NZMessage* message);

signals:
  void updated(void) const;

public:
  int messageCount(void) const;
  NZMessage* messageForIndex(int index) const;
  int indexForMessage(NZMessage* message) const;
  NZContact* contactTo(void) const;

private:
  NZContact* mContactTo;
  QList<NZMessage*> mMessageList;
};

#endif
