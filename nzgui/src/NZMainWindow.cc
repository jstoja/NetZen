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

#include <QtGui/QAction>
#include <QtGui/QStatusBar>
#include "NZMainWindow.hh"

NZMainWindow::NZMainWindow(QWidget* parent) : QMainWindow(parent) {
  setWindowTitle(tr("Adædra NetZen"));

  mainToolBar = new QToolBar(tr("Main Toolbar"));
  mainToolBar->setMovable(false);
  mainToolBar->setIconSize(QSize(24, 24));
  mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  mainToolBar->toggleViewAction()->setVisible(false);
  addToolBar(mainToolBar);

  statusWidget = new NZStatusWidget;

  addContactButton = new QToolButton(this);
  addContactButton->setText(tr("Add Contact"));
  addContactButton->setIcon(QIcon(":/res/24/user-add.png"));
  addContactButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  addContactButton->setEnabled(false);

  addChatButton = new QToolButton(this);
  addChatButton->setText(tr("Begin Chat"));
  addChatButton->setIcon(QIcon(":/res/24/balloon-add.png"));
  addChatButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  addChatButton->setEnabled(false);

  mainToolBar->addWidget(statusWidget);
  mainToolBar->addWidget(addContactButton);
  mainToolBar->addWidget(addChatButton);

  sideBar = new NZSideBarWidget;
  sideBar->setFixedWidth(200);
  sideBar->setEnabled(false);

  stackWidget = new QStackedWidget;

  contactList = new NZContactListWidget;

  connectionWidget = new NZConnectionWidget;
  stackWidget->addWidget(connectionWidget);

  waitWidget = new NZWaitWidget;
  stackWidget->addWidget(waitWidget);

  mainLayout = new QHBoxLayout;

  qCentralWidget = new QWidget;

  stackWidget->addWidget(contactList);

  mainLayout->addWidget(sideBar);
  mainLayout->addWidget(stackWidget);
  qCentralWidget->setLayout(mainLayout);

  setCentralWidget(qCentralWidget);

  statusText = new QLabel;
  statusText->setText(tr("Welcome to Adædra NetZen."));

  statusBar()->addWidget(statusText, 1);

  connect(addContactButton, SIGNAL(clicked()), this, SIGNAL(addContactRequested()));
  connect(addChatButton, SIGNAL(clicked()), this, SIGNAL(addChatRequested()));
  connect(statusWidget, SIGNAL(userStatusChanged(NZContact::Status)),
	  this, SIGNAL(statusChangeRequested(NZContact::Status)));
  connect(contactList, SIGNAL(contactRemoveRequested(NZContact*)),
	  this, SIGNAL(removeContactRequested(NZContact*)));
  connect(sideBar, SIGNAL(contactListRequested()),
	  this, SLOT(showContactList()));
  connect(sideBar, SIGNAL(chatRequested(NZConversation*)),
	  this, SLOT(activateChat(NZConversation*)));
  connect(contactList, SIGNAL(newChatRequested(NZContact*)),
	  this, SIGNAL(addChatWithRequested(NZContact*)));
  connect(connectionWidget,
	  SIGNAL(connectionRequested(QString, quint16, QString, QString, QString, QString)),
	  this,
	  SIGNAL(connectionRequested(QString, quint16, QString, QString, QString, QString)));
  connect(statusWidget, SIGNAL(userStatusChanged(NZContact::Status)),
	  this, SIGNAL(statusChangeRequested(NZContact::Status)));

  setUnifiedTitleAndToolBarOnMac(true);
  // setMinimumSize(sizeHint());
}

void NZMainWindow::statusChange(NZContactStatus status) {
  statusWidget->setUserStatus(status);
}

void NZMainWindow::contactAdded(NZContact* contact) {
  contactList->addContact(contact);
}

void NZMainWindow::contactRemoved(NZContact* contact) {
  contactList->removeContact(contact);
}

void NZMainWindow::contactUpdated(NZContact* contact) {
  contactList->contactUpdated(contact);
}

void NZMainWindow::chatOpened(NZConversation* conversation) {
  // Check for existing item
  for (int i = 0; i < chatList.count(); i++) {
    NZChatWidget* w = chatList.at(i);
    if (w->conversation() == conversation)
      return ;
  }

  NZChatWidget* newChat = new NZChatWidget(conversation);
  chatList.append(newChat);
  stackWidget->addWidget(newChat);
  stackWidget->setCurrentWidget(newChat);

  // This will disturb people typing in a conversation
  // when opening a new. To fix !
  sideBar->chatOpened(conversation);
  sideBar->chatActive(conversation);
}

void NZMainWindow::chatClosed(NZConversation* conversation) {
  sideBar->chatClosed(conversation);

  for (int i = 0; i < chatList.count(); i++) {
    NZChatWidget* w = chatList.at(i);

    if (w->conversation() == conversation) {
      chatList.removeOne(w);
      stackWidget->removeWidget(w);
      delete w;
    }
  }
}

void NZMainWindow::chatMessage(NZConversation* conversation, int messages) {
  sideBar->chatUnread(conversation, messages);
}

void NZMainWindow::activateChat(NZConversation* conversation) {
  if (static_cast<NZChatWidget*>(stackWidget->currentWidget())->conversation() == conversation)
    return ;

  for (int i = 0; i < chatList.count(); i++) {
    NZChatWidget* w = chatList.at(i);
    if (w->conversation() == conversation) {
      stackWidget->setCurrentWidget(w);
    }
  }

  sideBar->chatActive(conversation);
}

void NZMainWindow::showContactList(void) {
  stackWidget->setCurrentWidget(contactList);
  sideBar->contactListActive();
}

void NZMainWindow::connectionBegin(void) {
  stackWidget->setCurrentWidget(waitWidget);
  statusText->setText(tr("Waiting for server..."));
  waitWidget->progress(tr("Connecting to the NetSoul server..."));
}

void NZMainWindow::authAllowed(void) {
  statusText->setText(tr("ID Send, waiting for answer..."));
  waitWidget->progress(50, tr("Logging in..."));
}

void NZMainWindow::authSucceeded(void) {
  statusText->setText(tr("Connected to NetSoul Server."));
  sideBar->setEnabled(true);
  addContactButton->setEnabled(true);
  addChatButton->setEnabled(true);
  stackWidget->setCurrentWidget(contactList);
}

void NZMainWindow::connectionReset(void) {
  statusText->setText(tr("Connection closed."));
  sideBar->setEnabled(false);
  addContactButton->setEnabled(false);
  addChatButton->setEnabled(false);
  stackWidget->setCurrentWidget(connectionWidget);
}

void NZMainWindow::loginChanged(QString login) {
  statusWidget->setUserLogin(login);
}

void NZMainWindow::saveContacts(void) {
  contactList->saveContacts();
}

void NZMainWindow::uiReady(void) {
  connectionWidget->uiReady();
}
