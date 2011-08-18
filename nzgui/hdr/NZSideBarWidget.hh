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

#ifndef NZSIDEBARWIDGET_HH_
#define NZSIDEBARWIDGET_HH_

#include <QtGui/QTreeWidget>
#include <QtCore/QMap>

class QTreeWidgetItem;
class NZConversation;

class NZSideBarWidget : public QTreeWidget {
  Q_OBJECT

public:
  NZSideBarWidget(QWidget* parent = NULL);

public slots:
  void chatOpened(NZConversation* conversation);
  void chatClosed(NZConversation* conversation);
  void chatUnread(NZConversation* conversation, int messages);
  void chatActive(NZConversation* conversation);
  void contactListActive(void);

signals:
  void contactListRequested(void);
  void chatRequested(NZConversation* conversation);

private slots:
  void itemActive(QTreeWidgetItem* item, int column);

private:
  QTreeWidgetItem* mNetZenItem;
  QTreeWidgetItem* mChatItem;

  QTreeWidgetItem* mContactListItem;

  QMap<NZConversation*, QTreeWidgetItem*> mChatListItems;
};

#endif
