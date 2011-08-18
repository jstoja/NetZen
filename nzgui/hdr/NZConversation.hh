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

#ifndef NZCONVERSATION_HH_
#define NZCONVERSATION_HH_

#include <QtCore/QObject>
#include <QtCore/QList>

class NZMessage;
class NZContact;

class NZConversation : public QObject {
  Q_OBJECT

public:
  NZConversation(NZContact* contactTo, QObject* parent = NULL);
  ~NZConversation(void);

public slots:
  void addMessage(NZMessage* message);

signals:
  void updated(void) const;

public:
  int messageCount(void) const;
  NZMessage* messageForIndex(int index) const;
  int indexForMessage(NZMessage* message) const;
  NZContact* contactTo(void) const;

private:
  NZContact* mContactTo;
  QList<NZMessage*> mMessageList;
};

#endif
