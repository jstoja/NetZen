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

#ifndef NZCONTACTMODEL_HH_
#define NZCONTACTMODEL_HH_

#include <QtCore/QAbstractListModel>
#include <QtCore/QList>
#include "NZContact.hh"

class NZContactModel : public QAbstractListModel {
  Q_OBJECT

public:
  NZContactModel(QObject* parent = NULL);

  int rowCount(const QModelIndex& index) const;
  int columnCount(const QModelIndex& index) const;
  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

  void addContact(NZContact* contact);
  void removeContact(NZContact* contact);
  void clearContacts(void);

  NZContact* contactForIndex(const QModelIndex& index) const;
  NZContact* contactForIndex(int index) const;

  int indexForContact(NZContact* contact) const;
  QModelIndex modelIndexForContact(NZContact* contact, int column = 0) const;

public slots:
  void contactUpdated(NZContact* who);

private:
  QList<NZContact*> mContacts;
};

#endif
