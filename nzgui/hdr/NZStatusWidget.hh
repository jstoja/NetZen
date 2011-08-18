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

#ifndef NZSTATUSWIDGET_HH_
#define NZSTATUSWIDGET_HH_

#include <QtGui/QWidget>
#include "NZContact.hh"

class QLabel;
class QComboBox;
class QVBoxLayout;
class QHBoxLayout;

class NZStatusWidget : public QWidget {
  Q_OBJECT
  Q_ENUMS(NZContactStatus)

public:
  NZStatusWidget(QWidget* parent = NULL);

  QString userLogin(void) const;
  NZContactStatus userStatus(void) const;

public slots:
  void setUserLogin(const QString& login);
  void setUserStatus(NZContact::Status status);

signals:
  void userStatusChanged(NZContact::Status status);

private slots:
  void comboChanged(int index);

private:
  QString mUserLogin;
  NZContactStatus mUserStatus;

  QLabel* iconFrame;
  QLabel* loginLabel;
  QComboBox* statusBox;
  QHBoxLayout* mainLayout;
  QVBoxLayout* subLayout;
};

#endif
