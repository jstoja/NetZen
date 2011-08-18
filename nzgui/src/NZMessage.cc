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

#include "NZMessage.hh"

NZMessage::NZMessage(NZConversation* parent, QString message,
		     NZMessageType messageType, QDateTime timeStamp) {
  mParent = parent;
  mMessage = message;
  mMessageType = messageType;
  mTimeStamp = timeStamp;
}

QString NZMessage::message(void) const {
  return mMessage;
}

NZMessageType NZMessage::messageType(void) const {
  return mMessageType;
}

QDateTime NZMessage::timeStamp(void) const {
  return mTimeStamp;
}

NZConversation* NZMessage::conversation(void) const {
  return mParent;
}
