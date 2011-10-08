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

#ifndef NZCONTACT_HH_
#define NZCONTACT_HH_

#include <QtCore/QObject>
#include <QtGui/QPixmap>

#define gIconSize 32

class NZContact : public QObject {
  Q_OBJECT
  Q_ENUMS(Status)
  Q_PROPERTY(QString login READ login)
  Q_PROPERTY(Status status READ status WRITE setStatus)
  Q_PROPERTY(QString location READ location WRITE setLocation)
  Q_PROPERTY(QString userData READ userData WRITE setUserData)
  Q_PROPERTY(bool favorite READ isFavorite WRITE setFavorite)
  Q_PROPERTY(QPixmap userImage READ userImage WRITE setUserImage)

public:
  enum Status {
    nzDisconnected,
    nzConnection,
    nzActif,
    nzAway,
    nzLock,
    nzServer
  };

  NZContact(const QString& login,
	    Status status = nzDisconnected,
	    QObject* parent = NULL);

  QString login(void) const;
  Status status(void) const;
  QString location(void) const;
  QString userData(void) const;
  bool isFavorite(void) const;
  QPixmap userImage(void) const;
  QPixmap generateUserImage(void) const;

public slots:
  void setStatus(Status status);
  void setLocation(QString location);
  void setUserData(QString userData);
  void setFavorite(bool favorite);
  void setUserImage(QPixmap userImage);

signals:
  void statusChanged(NZContact* who, NZContact::Status status);
  void locationChanged(NZContact* who, QString location);
  void userDataChanged(NZContact* who, QString userData);
  void infoUpdated(NZContact* who);

private:
  QString mLogin;
  Status mStatus;
  QString mLocation;
  QString mUserData;
  QPixmap mUserPixmap;
  bool mIsFavorite;
};

#define NZContactStatus NZContact::Status

#endif
