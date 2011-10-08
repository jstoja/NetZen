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

#include "NZContactModel.hh"
#include <QtGui/QIcon>

#define ICON_SIZE 32

struct _status_text {
  NZContact::Status status;
  const char* text;
};

_status_text gStatusText[] = {
  { NZContact::nzDisconnected, QT_TR_NOOP("Disconnected") },
  { NZContact::nzConnection, QT_TR_NOOP("Connection") },
  { NZContact::nzActif, QT_TR_NOOP("Connected") },
  { NZContact::nzAway, QT_TR_NOOP("Away") },
  { NZContact::nzLock, QT_TR_NOOP("Lock") },
  { NZContact::nzServer, QT_TR_NOOP("Server") }
};

NZContactModel::NZContactModel(QObject* parent) : QAbstractListModel(parent) {
  
}

int NZContactModel::rowCount(const QModelIndex& index) const {
  if (index.isValid())
    return 0;
  return mContacts.count();
}

int NZContactModel::columnCount(const QModelIndex& index) const {
  return 2;
}

QVariant NZContactModel::headerData(int section, Qt::Orientation orientation, int role) const {
  if (section == 0 && orientation == Qt::Horizontal && role == Qt::DisplayRole) {
    return QVariant(tr("Contact"));
  }

  if (section == 1 && orientation == Qt::Horizontal && role == Qt::DisplayRole) {
    return QVariant(tr("Location"));
  }

  return QVariant();
}

QVariant NZContactModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid())
    return QVariant(); // Nothing to send

  NZContact* contact = contactForIndex(index);
  if (contact == NULL)
    return QVariant();

  if (index.column() == 0 && role == Qt::DisplayRole)
    return QVariant(contact->login());

  if (index.column() == 0 && role == Qt::DecorationRole) {
    return QVariant(contact->generateUserImage());
  }

  if (index.column() == 1 && role == Qt::DisplayRole && contact->status() > NZContact::nzDisconnected)
    return QVariant(contact->location());

  return QVariant();
}

void NZContactModel::addContact(NZContact* contact) {
  int v = 0;
  int i = 0;

  if (mContacts.count() > 0) {
    while (i < mContacts.count()) {
      if (mContacts.at(i)->login() < contact->login())
	v = i + 1;
      i++;
    }
  }

  beginInsertRows(QModelIndex(), v, v);
  mContacts.insert(v, contact);
  connect(contact, SIGNAL(statusChanged(NZContact*, NZContact::Status)),
	  this, SLOT(contactUpdated(NZContact*)));
  connect(contact, SIGNAL(locationChanged(NZContact*, QString)),
	  this, SLOT(contactUpdated(NZContact*)));
  connect(contact, SIGNAL(userDataChanged(NZContact*, QString)),
	  this, SLOT(contactUpdated(NZContact*)));
  connect(contact, SIGNAL(infoUpdated(NZContact*)),
	  this, SLOT(contactUpdated(NZContact*)));
  endInsertRows();
}

void NZContactModel::removeContact(NZContact* contact) {
  int i = indexForContact(contact);

  beginRemoveRows(QModelIndex(), i, i);
  mContacts.removeAt(i);
  disconnect(contact, SIGNAL(statusChanged(NZContact*, NZContact::Status)),
	     this, SLOT(contactUpdated(NZContact*)));
  disconnect(contact, SIGNAL(locationChanged(NZContact*, QString)),
	     this, SLOT(contactUpdated(NZContact*)));
  disconnect(contact, SIGNAL(userDataChanged(NZContact*, QString)),
	     this, SLOT(contactUpdated(NZContact*)));
  disconnect(contact, SIGNAL(infoUpdated(NZContact*)),
	     this, SLOT(contactUpdated(NZContact*)));
  endRemoveRows();
}

void NZContactModel::clearContacts(void) {
  // TO DO
}

NZContact* NZContactModel::contactForIndex(const QModelIndex& index) const {
  return contactForIndex(index.row());
}

NZContact* NZContactModel::contactForIndex(int index) const {
  NZContact* c = NULL;

  if (index >= 0 && index < mContacts.count()) {
    c = mContacts.at(index);
  }

  return c;
}

int NZContactModel::indexForContact(NZContact* contact) const {
  int index = -1;

  if (mContacts.contains(contact)) {
    index = mContacts.indexOf(contact);
  }

  return index;
}

QModelIndex NZContactModel::modelIndexForContact(NZContact* contact, int column) const {
  int index = indexForContact(contact);

  if (index == -1)
    return QModelIndex();
  else
    return createIndex(index, column);
}

void NZContactModel::contactUpdated(NZContact* who) {
  int i = indexForContact(who);

  qDebug("Row %d updated", i);

  emit dataChanged(sibling(i, 0, QModelIndex()),
		   sibling(i, columnCount(QModelIndex()), QModelIndex()));
}
