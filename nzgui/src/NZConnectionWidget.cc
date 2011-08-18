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

#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpinBox>
#include <QtGui/QCheckBox>
#include <QtGui/QPushButton>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QFormLayout>
#include <QtGui/QDialogButtonBox>
#include "NZConnectionWidget.hh"
#include "NZGuiController.hh"

NZConnectionWidget::NZConnectionWidget(QWidget* parent) : QWidget(parent) {
  mIcon = new QLabel;
  mIcon->setFixedWidth(64);
  mIcon->setMinimumHeight(64);
  mIcon->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
  mIcon->setPixmap(NZGuiController::instance()->guiIcon().pixmap(QSize(64, 64)));

  mHeaderText = new QLabel;
  mHeaderText->setText(tr("<p><b>Welcome to Ad&#230;dra NetZen</b></p>"
			  "<p>Before using NetZen, please enter your login informations "
			  "to connect to your NetSoul Server</p>"));
  mHeaderText->setWordWrap(true);

  mServerLabel = new QLabel;
  mServerLabel->setText(tr("Server : Epitech/Epita"));

  mAppearAfterLoginLabel = new QLabel;
  mAppearAfterLoginLabel->setText(tr("Once logged, appear as :"));
  mAppearAfterLoginLabel->setEnabled(false);

  mServerColumn = new QLabel;
  mServerColumn->setText(tr(":"));

  mHostName = new QLineEdit;
  mHostName->setText("ns-server.epitech.eu");

  mUserLogin = new QLineEdit;

  mUserPwd = new QLineEdit;
  mUserPwd->setEchoMode(QLineEdit::Password);

  mLocation = new QLineEdit;
  mLocation->setText(tr("Home"));

  mUserData = new QLineEdit;
  mUserData->setText(tr("Using NetZen"));

  mHostPort = new QSpinBox;
  mHostPort->setRange(1, 65535);
  mHostPort->setValue(4242);
  mHostPort->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

  mSavePwd = new QCheckBox;
  mSavePwd->setText(tr("Save password"));
  mSavePwd->setChecked(true);

  mEditServer = new QPushButton;
  mEditServer->setText(tr("Edit"));

  mDefaultServer = new QPushButton;
  mDefaultServer->setText(tr("Use default"));

  mUserMore = new QPushButton;
  mUserMore->setText(tr("More"));

  mConnect = new QPushButton;
  mConnect->setText(tr("Connect"));
  mConnect->setEnabled(false);

  mAppearAfterLogin = new QComboBox;
  mAppearAfterLogin->addItem(tr("Connected"));
  mAppearAfterLogin->addItem(tr("Away"));
  mAppearAfterLogin->addItem(tr("Lock"));
  mAppearAfterLogin->addItem(tr("Server"));
  mAppearAfterLogin->setEnabled(false);

  mServerGroup = new QGroupBox;
  mServerGroup->setTitle(tr("Server"));
  mServerGroup->setVisible(false);

  mUserGroup = new QGroupBox;
  mUserGroup->setTitle(tr("User"));

  mButtonBox = new QDialogButtonBox;
  mButtonBox->setStandardButtons(QDialogButtonBox::Cancel);
  mButtonBox->addButton(mConnect, QDialogButtonBox::AcceptRole);

  mMainLayout = new QVBoxLayout;
  mCenterLayout = new QHBoxLayout;
  mHeadLayout = new QHBoxLayout;
  mHeadServerLayout = new QHBoxLayout;
  mServerLayout = new QHBoxLayout;
  mUserMoreLayout = new QHBoxLayout;
  mDefaultServerLayout = new QHBoxLayout;
  mServerGroupLayout = new QFormLayout;
  mUserLayout = new QFormLayout;

  mMainLayout->addStretch();
  mMainLayout->addLayout(mHeadLayout);
  mMainLayout->addLayout(mHeadServerLayout);
  mMainLayout->addWidget(mServerGroup);
  mMainLayout->addWidget(mUserGroup);
  mMainLayout->addWidget(mAppearAfterLoginLabel);
  mMainLayout->addWidget(mAppearAfterLogin);
  mMainLayout->addWidget(mButtonBox);
  mMainLayout->addStretch();

  mCenterLayout->addStretch();
  mCenterLayout->addLayout(mMainLayout);
  mCenterLayout->addStretch();

  mHeadLayout->addWidget(mIcon);
  mHeadLayout->addWidget(mHeaderText);

  mHeadServerLayout->addWidget(mServerLabel);
  mHeadServerLayout->addStretch();
  mHeadServerLayout->addWidget(mEditServer);

  mServerLayout->addWidget(mHostName);
  mServerLayout->addWidget(mServerColumn);
  mServerLayout->addWidget(mHostPort);

  mUserMoreLayout->addStretch();
  mUserMoreLayout->addWidget(mUserMore);

  mDefaultServerLayout->addStretch();
  mDefaultServerLayout->addWidget(mDefaultServer);

  mServerGroupLayout->addRow(tr("Host :"), mServerLayout);
  mServerGroupLayout->addRow(mDefaultServerLayout);

  mUserLayout->addRow(tr("&Login :"), mUserLogin);
  mUserLayout->addRow(tr("&Password :"), mUserPwd);
  mUserLayout->addRow("", mSavePwd);
  mUserLayout->addRow(tr("L&ocation :"), mLocation);
  mUserLayout->addRow(tr("&User data :"), mUserData);
  mUserLayout->addRow(mUserMoreLayout);

  mServerGroup->setLayout(mServerGroupLayout);
  mUserGroup->setLayout(mUserLayout);

  mMainLayout->setSpacing(10);
  setLayout(mCenterLayout);

  mUserData->setVisible(false);
  mUserLayout->labelForField(mUserData)->setVisible(false);

  connect(mEditServer, SIGNAL(clicked()), this, SLOT(expandServer()));
  connect(mDefaultServer, SIGNAL(clicked()), this, SLOT(collapseServer()));
  connect(mUserMore, SIGNAL(clicked()), this, SLOT(expandUser()));
  connect(mHostName, SIGNAL(textChanged(QString)), this, SLOT(somethingChanged()));
  connect(mUserLogin, SIGNAL(textChanged(QString)), this, SLOT(somethingChanged()));
  connect(mUserPwd, SIGNAL(textChanged(QString)), this, SLOT(somethingChanged()));
  connect(mLocation, SIGNAL(textChanged(QString)), this, SLOT(somethingChanged()));
  connect(mUserData, SIGNAL(textChanged(QString)), this, SLOT(somethingChanged()));
  connect(mConnect, SIGNAL(clicked()), this, SLOT(connectionRequestedPrivate()));
  connect(mHostName, SIGNAL(returnPressed()), this, SLOT(connectionRequestedPrivate()));
  connect(mUserLogin, SIGNAL(returnPressed()), this, SLOT(connectionRequestedPrivate()));
  connect(mUserPwd, SIGNAL(returnPressed()), this, SLOT(connectionRequestedPrivate()));
  connect(mLocation, SIGNAL(returnPressed()), this, SLOT(connectionRequestedPrivate()));
  connect(mUserData, SIGNAL(returnPressed()), this, SLOT(connectionRequestedPrivate()));
}

void NZConnectionWidget::expandServer(void) {
  mServerLabel->setVisible(false);
  mEditServer->setVisible(false);
  mServerGroup->setVisible(true);
}

void NZConnectionWidget::collapseServer(void) {
  mServerGroup->setVisible(false);
  mHostName->setText("ns-server.epitech.eu");
  mHostPort->setValue(4242);
  mServerLabel->setVisible(true);
  mEditServer->setVisible(true);
}

void NZConnectionWidget::expandUser(void) {
  mUserMore->setVisible(false);
  mUserData->setVisible(true);
  mUserLayout->labelForField(mUserData)->setVisible(true);
}

void NZConnectionWidget::somethingChanged(void) {
  bool isOk = true;

  if (mHostName->text().length() == 0)
    isOk = false;

  if (mUserLogin->text().length() == 0)
    isOk = false;

  if (mUserPwd->text().length() == 0)
    isOk = false;

  if (mLocation->text().length() == 0)
    isOk = false;

  if (mUserData->text().length() == 0)
    isOk = false;

  mConnect->setEnabled(isOk);
}

void NZConnectionWidget::connectionRequestedPrivate(void) {
  if (!mConnect->isEnabled())
    return ;

  emit connectionRequested(mHostName->text(), mHostPort->value(),
			   mUserLogin->text(), mUserPwd->text(),
			   mLocation->text(), mUserData->text());
}
