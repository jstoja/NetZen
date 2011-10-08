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

#ifndef NZGUICONTROLLER_HH_
#define NZGUICONTROLLER_HH_

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtGui/QIcon>
#include "NZContact.hh"
#include "NZSettings.hh"

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

  NZSettings* settings();

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
  void watchUser(NZContact* contact);
  void getUserInfo(NZContact* contact);

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
  void locationChangePrivate(QString user, QString location);
  void userStatusChangePrivate(QString user, QString location);

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

  NZSettings mSettings;
  bool mContactsChanged;

  static NZGuiController* mInstance;
};

#endif
