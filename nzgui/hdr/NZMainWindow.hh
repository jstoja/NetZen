#ifndef NZMAINWINDOW_HH_
#define NZMAINWINDOW_HH_

#include <QtGui/QMainWindow>
#include <QtGui/QToolBar>
#include <QtGui/QToolButton>
#include <QtGui/QStackedWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include "NZContact.hh"
#include "NZStatusWidget.hh"
#include "NZSideBarWidget.hh"
#include "NZContactListWidget.hh"
#include "NZChatWidget.hh"
#include "NZConnectionWidget.hh"
#include "NZWaitWidget.hh"

class NZMainWindow : public QMainWindow {
  Q_OBJECT

public:
  NZMainWindow(QWidget* parent = NULL);

signals:
  void statusChangeRequested(NZContact::Status status);
  void addContactRequested(void);
  void addChatRequested(void);
  void addChatWithRequested(NZContact* contact);
  void removeContactRequested(NZContact* contact);
  void connectionRequested(QString hostName, quint16 hostPort, QString userName, QString userPwd,
			   QString userLocation, QString userData);

public slots:
  void statusChange(NZContact::Status status);
  void contactAdded(NZContact* contact);
  void contactUpdated(NZContact* contact);
  void contactRemoved(NZContact* contact);
  void chatOpened(NZConversation* conversation);
  void chatClosed(NZConversation* conversation);
  void chatMessage(NZConversation* conversation, int messages);
  void activateChat(NZConversation* conversation);
  void showContactList(void);
  void connectionBegin(void);
  void authAllowed(void);
  void authSucceeded(void);
  void connectionReset(void);
  void loginChanged(QString login);

private:
  QToolBar*		mainToolBar;
  NZStatusWidget*	statusWidget;
  QToolButton*		addContactButton;
  QToolButton*		addChatButton;
  NZSideBarWidget*	sideBar;
  QStackedWidget*	stackWidget;
  NZContactListWidget*	contactList;
  QHBoxLayout*		mainLayout;
  QWidget*		qCentralWidget;
  NZConnectionWidget*	connectionWidget;
  NZWaitWidget*		waitWidget;
  QLabel*		statusText;

  QList<NZChatWidget *>	chatList;
};

#endif
