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

#include <stdlib.h> // abort()
#include <QtGui/QMessageBox>
#include "NZGuiController.hh"
#include "NZMainWindow.hh"
#include "NZControllerProxy.hh"
#include "NZAddContactDialog.hh"
#include "NZAddChatDialog.hh"
#include "NZConversation.hh"
#include "NZMessage.hh"

NZGuiController* NZGuiController::mInstance = NULL;

NZGuiController::NZGuiController(QObject* parent) : QObject(parent),
						    mGuiIcon(":/res/icon/256.png") {
  if (mInstance != NULL) {
    qCritical("Trying to allocate multiple NZGuiController's");
    abort();
  }

  mInstance = this;
  mainWindow = new NZMainWindow;
  controller = new NZControllerProxy;
  mMe = NULL;

  // mGuiIcon.addFile(":/res/icon/256.png", QSize(256, 256));
  mGuiIcon.addFile(":/res/icon/128.png", QSize(128, 128));
  mGuiIcon.addFile(":/res/icon/64.png", QSize(64, 64));
  mGuiIcon.addFile(":/res/icon/48.png", QSize(48, 48));
  mGuiIcon.addFile(":/res/icon/32.png", QSize(32, 32));
  mGuiIcon.addFile(":/res/icon/16.png", QSize(16, 16));

  connect(mainWindow, SIGNAL(addContactRequested()), this, SLOT(addContact()));
  connect(this, SIGNAL(contactAdded(NZContact*)), mainWindow, SLOT(contactAdded(NZContact*)));
  connect(mainWindow, SIGNAL(removeContactRequested(NZContact*)),
	  this, SLOT(removeContact(NZContact*)));
  connect(this, SIGNAL(contactRemoved(NZContact*)),
	  mainWindow, SLOT(contactRemoved(NZContact*)));
  connect(mainWindow, SIGNAL(addChatRequested()), this, SLOT(createChat()));
  connect(this, SIGNAL(chatCreated(NZConversation*)), mainWindow, SLOT(chatOpened(NZConversation*)));
  connect(mainWindow, SIGNAL(addChatWithRequested(NZContact*)),
	  this, SLOT(createChatWith(NZContact*)));
  connect(mainWindow,
	  SIGNAL(connectionRequested(QString, quint16, QString, QString, QString, QString)),
	  this,
	  SLOT(connectionRequested(QString, quint16, QString, QString, QString, QString)));
  connect(controller, SIGNAL(proxyAuthAllowed()), this, SLOT(authAllowedPrivate()));
  connect(controller, SIGNAL(proxyAuthSucceeded()), this, SLOT(authSucceededPrivate()));
  connect(this, SIGNAL(connectionBegin()), mainWindow, SLOT(connectionBegin()));
  connect(this, SIGNAL(authAllowed()), mainWindow, SLOT(authAllowed()));
  connect(this, SIGNAL(authSucceeded()), mainWindow, SLOT(authSucceeded()));
  connect(controller, SIGNAL(proxyConnectionError(int)), this, SLOT(connectionError(int)));
  connect(this, SIGNAL(connectionReset()), mainWindow, SLOT(connectionReset()));
  connect(this, SIGNAL(loginChange(QString)), mainWindow, SLOT(loginChanged(QString)));
  connect(this, SIGNAL(statusChanged(NZContact::Status)),
	  mainWindow, SLOT(statusChange(NZContact::Status)));
  connect(mainWindow, SIGNAL(statusChangeRequested(NZContact::Status)),
	  this, SLOT(statusChangeRequested(NZContact::Status)));
  connect(controller, SIGNAL(proxyReceivedMessage(QString, QString)),
	  this, SLOT(receivedMessagePrivate(QString, QString)));

  mContactsChanged = false;
  mSettings.load();
}

NZGuiController::~NZGuiController(void) {
  mainWindow->close();

  if (mContactsChanged) {
    qDebug("Save contacts");
    mainWindow->saveContacts();
  }

  if (mSettings.isDirty()) {
    qDebug("Save settings");
    mSettings.save();
  }

  delete mainWindow;
  delete controller;

  for (int i = 0; i < mContactList.count(); i++) {
    delete mContactList.at(i);
  }
  mContactList.clear();
}

void NZGuiController::showMainWindow(void) {
  mainWindow->show();
  mainWindow->uiReady();
}

void NZGuiController::addContact(void) {
  QString newContact = NZAddContactDialog::getContactName(mainWindow);

  if (newContact.length() == 0)
    return ;
  for (int i = 0; i < mContactList.count(); i++) {
    NZContact* c = mContactList.at(i);
    if (c->login() == newContact) {
      emit contactAdded(c);
      return ;
    }
  }

  NZContact* nc = new NZContact(newContact);
  mContactList.append(nc);
  mContactsChanged = true;
  emit contactAdded(nc);
}

void NZGuiController::removeContact(NZContact* contact) {
  if (!mContactList.contains(contact))
    return ;

  emit contactRemoved(contact);

  for (int i = 0; i < mConversationList.count(); i++) {
    // If a conversation is engaged with this contact,
    // keep it in database.
    if (mConversationList.at(i)->contactTo() == contact)
      return ;
  }
  mContactList.removeOne(contact);
  mContactsChanged = true;
  contact->deleteLater();
}

void NZGuiController::createChat(void) {
  QString newChat = NZAddChatDialog::getContactName(mainWindow);

  if (newChat.length() == 0)
    return ;

  for (int i = 0; i < mContactList.count(); i++) {
    if (mContactList.at(i)->login() == newChat) {
      createChatWith(mContactList.at(i));
      return ;
    }
    i++;
  }

  NZContact* c = new NZContact(newChat);
  mContactList.append(c);
  createChatWith(c);
}

void NZGuiController::createChatWith(NZContact* contact) {
  for (int i = 0; i < mConversationList.count(); i++) {
    if (mConversationList.at(i)->contactTo() == contact)
      return ;
  }

  NZConversation* nc = new NZConversation(contact);
  mConversationList.append(nc);
  emit chatCreated(nc);
}

NZContact* NZGuiController::me(void) const {
  return mMe;
}

NZGuiController* NZGuiController::instance(void) {
  return mInstance;
}

QIcon NZGuiController::guiIcon(void) const {
  return mGuiIcon;
}

void NZGuiController::connectionRequested(QString hostName, quint16 hostPort,
					  QString userName, QString userPwd,
					  QString userLocation, QString userData) {
  loginChangePrivate(userName);
  emit connectionBegin();

  if (mSettings.stringKey("adaedra.netzen.nzgui.host") != hostName)
    mSettings.setKey("adaedra.netzen.nzgui.host", hostName);
  if (mSettings.intKey("adaedra.netzen.nzgui.host.port") != hostPort)
    mSettings.setKey("adaedra.netzen.nzgui.host.port", (int)hostPort);
  if (mSettings.stringKey("adaedra.netzen.nzgui.user") != userName)
    mSettings.setKey("adaedra.netzen.nzgui.user", userName);
  if (mSettings.stringKey("adaedra.netzen.nzgui.location") != userLocation)
    mSettings.setKey("adaedra.netzen.nzgui.location", userLocation);
  if (mSettings.stringKey("adaedra.netzen.nzgui.userData") != userData)
    mSettings.setKey("adaedra.netzen.nzgui.userData", userData);

  mUserLogin = userName;
  mUserPwd = userPwd;
  mUserLocation = userLocation;
  mUserData = userData;

  controller->connect(hostName, hostPort);
}

void NZGuiController::authAllowedPrivate(void) {
  emit authAllowed();
  controller->login(mUserLogin, mUserPwd, mUserLocation, mUserData);

  // Cleanup, as long as these values are not used anymore
  mUserLogin = "";
  mUserPwd = "";
  mUserLocation = "";
  mUserData = "";
}

void NZGuiController::authSucceededPrivate(void) {
  controller->changeStatus("actif");
  emit authSucceeded();
  mMe->setStatus(NZContact::nzActif);
  emit statusChanged(NZContact::nzActif);

  QStringList contactList = mSettings.stringListKey("adaedra.netzen.nzgui.contacts");


  int i = 0;
  if (mContactList.count() > 0) {
    while (i < mContactList.count()) {
      delete mContactList.at(i);
      i++;
    }

    mContactList.clear();
  }

  i = 0;
  while (i < contactList.count()) {
    NZContact* c = new NZContact(contactList.at(i));
    
    mContactList.append(c);
    emit contactAdded(c);

    i++;
  }
}

void NZGuiController::loginChangePrivate(QString login) {
  NZContact* newMe = new NZContact(login);
  if (mMe) {
    newMe->setStatus(mMe->status());
    newMe->setLocation(mMe->location());
    newMe->setUserData(mMe->userData());

    delete mMe;
  }
  mMe = newMe;

  emit loginChange(login);
}

void NZGuiController::connectionError(int error) {
  controller->close();
  // Will be better soon
  QMessageBox::critical(mainWindow, tr("Connection Error"),
			tr("Connection failed. (Error %1)").arg(error));
  emit connectionReset();
}

void NZGuiController::statusChangeRequested(NZContact::Status status) {
  if (status <= NZContact::nzConnection)
    return ;
  if (mMe->status() == status)
    return ;

  switch(status) {
  case NZContact::nzActif:
    controller->changeStatus("actif");
    break;
  case NZContact::nzAway:
    controller->changeStatus("away");
    break;
  case NZContact::nzLock:
    controller->changeStatus("lock");
    break;
  case NZContact::nzServer:
    controller->changeStatus("server");
    break;
    };

  mMe->setStatus(status);
  emit statusChanged(status);
}

void NZGuiController::relayMessage(NZMessage* message) {
  if (message->messageType() != nzSendMessage)
    return ;

  NZContact* contactTo = message->conversation()->contactTo();

  controller->sendMessage(contactTo->login(), message->message());
}

void NZGuiController::receivedMessagePrivate(QString contactFrom, QString message) {
  int i = 0;

  while (i < mConversationList.count()) {
    if (mConversationList.at(i)->contactTo()->login() == contactFrom) {
      NZMessage* m = new NZMessage(mConversationList.at(i), message, nzReceivedMessage);
      mConversationList.at(i)->addMessage(m);

      return ;
    }
    i++;
  }

  i = 0;
  while (i < mContactList.count()) {
    if (mContactList.at(i)->login() == contactFrom) {
      NZConversation* c = new NZConversation(mContactList.at(i));
      mConversationList.append(c);
      emit chatCreated(c);

      NZMessage* m = new NZMessage(c, message, nzReceivedMessage);
      c->addMessage(m);

      return ;
    }

    i++;
  }

  NZContact* c = new NZContact(contactFrom);
  mContactList.append(c);

  NZConversation* cv = new NZConversation(c);
  mConversationList.append(cv);
  emit chatCreated(cv);

  NZMessage* m = new NZMessage(cv, message, nzReceivedMessage);
  cv->addMessage(m);
}

NZSettings* NZGuiController::settings(void) {
  return &mSettings;
}
