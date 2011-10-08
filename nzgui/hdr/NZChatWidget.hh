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

#ifndef NZCHATWIDGET_HH_
#define NZCHATWIDGET_HH_

#include <QtGui/QWidget>
#include "NZContact.hh"

class NZConversation;
class NZChatView;
class QLineEdit;
class QVBoxLayout;
class QLabel;
class QHBoxLayout;
class QFrame;

class NZChatWidget : public QWidget {
  Q_OBJECT

public:
  NZChatWidget(NZConversation* conversation, QWidget* parent = NULL);

  NZConversation* conversation(void) const;

public slots:
  void sendMessage(void);
  void contactStatusChange(NZContact* who, NZContact::Status status);

protected:
  void resizeEvent(QResizeEvent*);

private:
  NZConversation* mConversation;

  QFrame* mViewWrapper;
  QVBoxLayout* mViewLayout;
  NZChatView* mView;
  QLineEdit* mEdit;
  QVBoxLayout* mLayout;
  QLabel* mUserIcon;
  QLabel* mUserLogin;
  QHBoxLayout* mTopLayout;
};

#endif
