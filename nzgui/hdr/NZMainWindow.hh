// Adaedra NetZen
// Copyright (C) 2011 Adaedra
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
  void saveContacts(void);
  void uiReady(void);

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
