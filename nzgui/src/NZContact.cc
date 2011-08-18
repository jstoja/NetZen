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

#include "NZContact.hh"
#include <QtGui/QPainter>
#include <QtGui/QPixmap>

NZContact::NZContact(const QString& login, Status status, QObject* parent) : QObject(parent) {
  mLogin = login;
  mStatus = status;
}

QString NZContact::login(void) const {
  return mLogin;
}

NZContactStatus NZContact::status(void) const {
  return mStatus;
}

QString NZContact::location(void) const {
  return mLocation;
}

QString NZContact::userData(void) const {
  return mUserData;
}

bool NZContact::isFavorite(void) const {
  return mIsFavorite;
}

QPixmap NZContact::userImage(void) const {
  return mUserPixmap;
}

void NZContact::setStatus(Status status) {
  if (mStatus != status) {
    mStatus = status;
    emit statusChanged(this, status);
  }
}

void NZContact::setLocation(QString location) {
  if (mLocation != location) {
    mLocation = location;
    emit locationChanged(this, location);
  }
}

void NZContact::setUserData(QString userData) {
  if (mUserData != userData) {
    mUserData = userData;
    emit userDataChanged(this, userData);
  }
}

void NZContact::setFavorite(bool favorite) {
  if (mIsFavorite != favorite) {
    mIsFavorite = favorite;
    emit infoUpdated(this);
  }
}

void NZContact::setUserImage(QPixmap userImage) {
  mUserPixmap = userImage.scaled(QSize(48, 48));
  emit infoUpdated(this);
}

QPixmap NZContact::generateUserImage(void) const {
  QImage base(gIconSize, gIconSize, QImage::Format_ARGB32);
  base.fill(0x00000000);

  QPainter p(&base);

  if (!mUserPixmap.isNull()) {
    QPixmap up = mUserPixmap;

    if (up.width() > gIconSize || up.height() > gIconSize)
      up = up.scaled(QSize(gIconSize, 32), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    p.drawPixmap((gIconSize - up.width()) / 2, (gIconSize - up.height()) / 2, up);
  } else {
    p.drawPixmap((gIconSize - 24) / 2, (gIconSize - 24) / 2, QPixmap(":/res/24/user.png"));
  }

  const char* i = NULL;
  
  switch (mStatus) {
  case NZContact::nzDisconnected:
    i = ":/res/16/cross.png";
    break;
  case NZContact::nzConnection:
    i = ":/res/16/plug.png";
    break;
  case NZContact::nzAway:
    i = ":/res/16/minus-circle.png";
    break;
  case NZContact::nzLock:
    i = ":/res/16/lock.png";
    break;
  case NZContact::nzServer:
    i = ":/res/16/server.png";
    break;
  }

  if (i) {
    p.drawPixmap(gIconSize - 16, gIconSize - 16, QPixmap(i));
  }

  return QPixmap::fromImage(base);
}
