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

#include "NZConversation.hh"

NZConversation::NZConversation(NZContact* contactTo, QObject* parent) : QObject(parent) {
  mContactTo = contactTo;
}

NZConversation::~NZConversation(void) {
  int i = 0;
  while (i < mMessageList.count()) {
    delete mMessageList.at(i);
    i++;
  }
  mMessageList.clear();
}

void NZConversation::addMessage(NZMessage* message) {
  mMessageList.append(message);
  emit updated();
}

int NZConversation::messageCount(void) const {
  return mMessageList.count();
}

NZMessage* NZConversation::messageForIndex(int index) const {
  if (index < 0 || index >= mMessageList.count())
    return NULL;

  return mMessageList.at(index);
}

int NZConversation::indexForMessage(NZMessage* message) const {
  if (mMessageList.contains(message))
    return mMessageList.indexOf(message);
  return -1;
}

NZContact* NZConversation::contactTo(void) const {
  return mContactTo;
}
