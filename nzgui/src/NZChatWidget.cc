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

#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QScrollArea>
#include <QtGui/QLabel>
#include <QtGui/QHBoxLayout>
#include "NZConversation.hh"
#include "NZChatView.hh"
#include "NZChatWidget.hh"
#include "NZContact.hh"
#include "NZMessage.hh"
#include "NZGuiController.hh"

NZChatWidget::NZChatWidget(NZConversation* conversation, QWidget* parent) : QWidget(parent) {
  mConversation = conversation;

  mViewWrapper = new QFrame;
  mViewLayout = new QVBoxLayout;
  mView = new NZChatView(conversation);
  mEdit = new QLineEdit;
  mLayout = new QVBoxLayout;
  mUserIcon = new QLabel;
  mUserLogin = new QLabel;
  mTopLayout = new QHBoxLayout;

  mViewWrapper->setFrameShadow(QFrame::Sunken);
  mViewWrapper->setFrameShape(QFrame::StyledPanel);

  mUserIcon->setPixmap(conversation->contactTo()->generateUserImage());
  mUserIcon->setFixedSize(QSize(gIconSize, gIconSize));

  mUserLogin->setText(conversation->contactTo()->login());

  mTopLayout->addWidget(mUserIcon);
  mTopLayout->addWidget(mUserLogin);

  mViewLayout->addWidget(mView);
  mViewLayout->setContentsMargins(0, 0, 0, 0);
  mViewWrapper->setLayout(mViewLayout);

  mLayout->addLayout(mTopLayout);
  mLayout->addWidget(mViewWrapper, 1);
  mLayout->addWidget(mEdit);
  // Margins of main window are used
  mLayout->setContentsMargins(0, 0, 0, 0);
  setLayout(mLayout);

  connect(mConversation, SIGNAL(updated()), mView, SLOT(conversationUpdated()));
  connect(mEdit, SIGNAL(returnPressed()), this, SLOT(sendMessage()));
}

NZConversation* NZChatWidget::conversation(void) const {
  return mConversation;
}

void NZChatWidget::sendMessage(void) {
  if (mEdit->text().length() == 0)
    return ;

  NZMessage* message = new NZMessage(mConversation, mEdit->text());
  mConversation->addMessage(message);
  mEdit->setText(QString());

  NZGuiController::instance()->relayMessage(message);
}

void NZChatWidget::resizeEvent(QResizeEvent*) {
}
