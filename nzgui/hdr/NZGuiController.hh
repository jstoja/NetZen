#ifndef NZGUICONTROLLER_HH_
#define NZGUICONTROLLER_HH_

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtGui/QIcon>
#include "NZContact.hh"

class NZMainWindow;
class NZControllerProxy;
class NZConversation;
class NZMessage;

class NZGuiController : public QObject {
  Q_OBJECT

public:
  NZGuiController(QObject* parent = NULL);
  ~NZGuiController(void);
  static NZGuiController* instance(void);

  NZContact* me(void) const;
  QIcon guiIcon(void) const;

public slots:
  void showMainWindow(void);
  void addContact(void);
  void removeContact(NZContact* contact);
  void createChat(void);
  void createChatWith(NZContact* contact);
  void connectionRequested(QString hostName, quint16 hostPort, QString userName, QString userPwd,
			   QString userLocation, QString userData);
  void statusChangeRequested(NZContact::Status status);
  void relayMessage(NZMessage* message);

signals:
  void contactAdded(NZContact* contact);
  void contactRemoved(NZContact* contact);
  void chatCreated(NZConversation* conversation);
  void loginChange(QString login);
  void connectionBegin(void);
  void authAllowed(void);
  void authSucceeded(void);
  void authFailed(void);
  void connectionReset(void);
  void statusChanged(NZContact::Status status);

private slots:
  void authAllowedPrivate(void);
  void loginChangePrivate(QString);
  void authSucceededPrivate(void);
  void connectionError(int error);
  void receivedMessagePrivate(QString contactFrom, QString message);

private:
  NZMainWindow* mainWindow;
  NZControllerProxy* controller;
  NZContact* mMe;

  QList<NZContact*> mContactList;
  QList<NZConversation*> mConversationList;

  QIcon mGuiIcon;

  // Used for connection only !
  QString mUserLogin;
  QString mUserPwd;
  QString mUserLocation;
  QString mUserData;

  static NZGuiController* mInstance;
};

#endif
