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

#ifndef NZCONNECTIONWIDGET_HH_
#define NZCONNECTIONWIDGET_HH_

#include <QtGui/QWidget>

class QLabel;
class QLineEdit;
class QSpinBox;
class QCheckBox;
class QPushButton;
class QComboBox;
class QGroupBox;
class QVBoxLayout;
class QHBoxLayout;
class QFormLayout;
class QDialogButtonBox;

class NZConnectionWidget : public QWidget {
  Q_OBJECT

public:
  NZConnectionWidget(QWidget* parent = NULL);

public slots:
  void expandServer(void);
  void collapseServer(void);
  void expandUser(void);
  void somethingChanged(void);
  void uiReady(void);

signals:
  void connectionRequested(QString hostName, quint16 hostPort, QString userName, QString userPwd,
			   QString userLocation, QString userData);

private slots:
  void connectionRequestedPrivate(void);

private:
  QLabel* mIcon;
  QLabel* mHeaderText;
  QLabel* mServerLabel;
  QLabel* mAppearAfterLoginLabel;
  QLabel* mServerColumn;
  QLineEdit* mHostName;
  QLineEdit* mUserLogin;
  QLineEdit* mUserPwd;
  QLineEdit* mLocation;
  QLineEdit* mUserData;
  QSpinBox* mHostPort;
  QCheckBox* mSavePwd;
  QPushButton* mEditServer;
  QPushButton* mDefaultServer;
  QPushButton* mUserMore;
  QPushButton* mConnect;
  QComboBox* mAppearAfterLogin;
  QGroupBox* mServerGroup;
  QGroupBox* mUserGroup;
  QDialogButtonBox* mButtonBox;
  QVBoxLayout* mMainLayout;
  QHBoxLayout* mCenterLayout;
  QHBoxLayout* mHeadLayout;
  QHBoxLayout* mHeadServerLayout;
  QHBoxLayout* mServerLayout;
  QHBoxLayout* mUserMoreLayout;
  QHBoxLayout* mDefaultServerLayout;
  QFormLayout* mServerGroupLayout;
  QFormLayout* mUserLayout;
};

#endif
