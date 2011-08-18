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

#include <QtGui/QMenu>
#include <QtGui/QAction>
#include "NZContactListWidget.hh"
#include "NZContact.hh"
#include "NZContactModel.hh"

NZContactListWidget::NZContactListWidget(QWidget* parent) : QTreeView(parent) {
  setIconSize(QSize(32, 32));
  setRootIsDecorated(false);

  mModel = new NZContactModel;
  setModel(mModel);

  mContextMenu = new QMenu;
  mDeleteContactAction = new QAction(this);
  mDeleteContactAction->setText(tr("Delete contact"));
  mContextMenu->addAction(mDeleteContactAction);

  setContextMenuPolicy(Qt::CustomContextMenu);

  connect(this, SIGNAL(customContextMenuRequested(QPoint)),
	  this, SLOT(rightClicked(QPoint)));
  connect(mDeleteContactAction, SIGNAL(triggered()),
	  this, SLOT(removeContactAction()));
  connect(this, SIGNAL(activated(QModelIndex)),
	  this, SLOT(itemActive(QModelIndex)));
}

NZContactListWidget::~NZContactListWidget(void) {
  delete mModel;
  delete mContextMenu;
}

void NZContactListWidget::addContact(NZContact* contact) {
  connect(contact, SIGNAL(infoUpdated(NZContact*)), this, SLOT(contactUpdated(NZContact*)));
  mModel->addContact(contact);
}

void NZContactListWidget::removeContact(NZContact* contact) {
  disconnect(contact, SIGNAL(infoUpdated(NZContact*)), this, SLOT(contactUpdated(NZContact*)));
  mModel->removeContact(contact);
}

void NZContactListWidget::contactUpdated(NZContact* contact) {
  // TO DO
}

void NZContactListWidget::rightClicked(const QPoint& where) {
  QModelIndex index = indexAt(where);
  if (!index.isValid())
    return ;

  mContextMenu->popup(mapToGlobal(where), mDeleteContactAction);
}

void NZContactListWidget::removeContactAction(void) {
  NZContact* c = mModel->contactForIndex(currentIndex());
  emit contactRemoveRequested(c);
}

void NZContactListWidget::itemActive(const QModelIndex& i) {
  NZContact* who = mModel->contactForIndex(i);
  if (who == NULL)
    return ;

  emit newChatRequested(who);
}

