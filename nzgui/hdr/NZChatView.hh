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

#ifndef NZCHATVIEW_HH_
#define NZCHATVIEW_HH_

#include <QtGui/QWidget>
#include <QtWebKit/QWebView>

class NZConversation;
class NZMessage;

class NZChatView : public QWebView {
  Q_OBJECT

public:
  NZChatView(NZConversation* conversation, QWidget* parent = NULL);

  NZConversation* conversation(void) const;

public slots:
  void conversationUpdated(void);
  void conversationViewUpdated();

private slots:
  void doneLoading(void);

private:
  NZConversation* mConversation;
  NZMessage* lastAddedMessage;
};

#endif
