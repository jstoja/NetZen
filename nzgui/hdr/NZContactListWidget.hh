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

#ifndef NZCONTACTLISTWIDGET_HH_
#define NZCONTACTLISTWIDGET_HH_

#include <QtGui/QTreeView>

class NZContact;
class NZContactModel;
class QMenu;
class QAction;

class NZContactListWidget : public QTreeView {
  Q_OBJECT

public:
  NZContactListWidget(QWidget* parent = NULL);
  ~NZContactListWidget(void);

signals:
  void contactRemoveRequested(NZContact* contact);
  void newChatRequested(NZContact* contact);

public slots:
  void addContact(NZContact* contact);
  void removeContact(NZContact* contact);
  void contactUpdated(NZContact* contact);
  void rightClicked(const QPoint& where);
  void removeContactAction(void);
  void saveContacts(void);

private slots:
  void itemActive(const QModelIndex& i);

private:
  NZContactModel* mModel;

  QMenu* mContextMenu;
  QAction* mDeleteContactAction;
};

#endif
