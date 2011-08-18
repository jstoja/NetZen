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

#include "NZSideBarWidget.hh"
#include "NZConversation.hh"
#include "NZContact.hh"

NZSideBarWidget::NZSideBarWidget(QWidget* parent) :QTreeWidget(parent) {
  setRootIsDecorated(false);
  setExpandsOnDoubleClick(false);

  mNetZenItem = new QTreeWidgetItem(this);
  mNetZenItem->setText(0, tr("NetZen"));
  mNetZenItem->setFlags(mNetZenItem->flags() & ~Qt::ItemIsSelectable);
  mNetZenItem->setExpanded(true);

  mChatItem = new QTreeWidgetItem(this);
  mChatItem->setText(0, tr("Chats"));
  mChatItem->setFlags(mNetZenItem->flags() & ~Qt::ItemIsSelectable);
  mChatItem->setExpanded(true);

  mContactListItem = new QTreeWidgetItem(mNetZenItem);
  mContactListItem->setText(0, tr("Contacts"));
  mContactListItem->setIcon(0, QIcon(":/res/16/address-book.png"));

  setHeaderHidden(true);

  connect(this, SIGNAL(itemClicked(QTreeWidgetItem*, int)),
	  this, SLOT(itemActive(QTreeWidgetItem*, int)));
  connect(this, SIGNAL(itemActivated(QTreeWidgetItem*, int)),
	  this, SLOT(itemActive(QTreeWidgetItem*, int)));
}

void NZSideBarWidget::chatOpened(NZConversation* conversation) {
  if (mChatListItems.contains(conversation))
    return ;

  QTreeWidgetItem* newItem = new QTreeWidgetItem(mChatItem);
  newItem->setText(0, conversation->contactTo()->login());
  newItem->setIcon(0, QIcon(":/res/16/balloons.png"));

  mChatListItems.insert(conversation, newItem);
}

void NZSideBarWidget::chatClosed(NZConversation* conversation) {
  if (!mChatListItems.contains(conversation))
    return ;

  QTreeWidgetItem* i = mChatListItems.value(conversation);
  mChatListItems.remove(conversation);

  delete i;
}

void NZSideBarWidget::chatUnread(NZConversation* /* conversation */, int /* messages */) {
  // TO DO
}

void NZSideBarWidget::chatActive(NZConversation* /* conversation */) {
  // TO DO
}

void NZSideBarWidget::itemActive(QTreeWidgetItem* item, int column) {
  if (item == NULL)
    return ;

  if (item == mNetZenItem || item == mChatItem)
    return ;

  if (item == mContactListItem) {
    emit contactListRequested();
    return ;
  }

  NZConversation* chat = mChatListItems.key(item);
  emit chatRequested(chat);
}

void NZSideBarWidget::contactListActive(void) {
  setCurrentItem(mContactListItem);
}
