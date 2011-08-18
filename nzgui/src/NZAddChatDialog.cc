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
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QPushButton>
#include "NZAddChatDialog.hh"

NZAddChatDialog::NZAddChatDialog(QWidget* parent) : QDialog(parent) {
  setWindowTitle(tr("Begin chat"));

  mIcon = new QLabel;
  // Allow widget to grow to bottom to respect layout
  mIcon->setFixedWidth(32);
  mIcon->setPixmap(QPixmap(":/res/24/balloon-add.png"));
  mIcon->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

  mText = new QLabel;
  mText->setText(tr("<b>Add chat</b><br /><br />"
		    "Enter the login of the person you want to chat with :"));
  mText->setWordWrap(true);

  mEntry = new QLineEdit;

  mButtons = new QDialogButtonBox;
  mButtons->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

  mLayout = new QGridLayout;
  mLayout->addWidget(mIcon, 0, 0, 2, 1);
  mLayout->addWidget(mText, 0, 1);
  mLayout->addWidget(mEntry, 1, 1);
  mLayout->setRowMinimumHeight(2, 10);
  mLayout->addWidget(mButtons, 3, 1);
  mLayout->setSpacing(10);
  mLayout->setContentsMargins(15, 15, 15, 15);

  mButtons->button(QDialogButtonBox::Ok)->setEnabled(false);

  connect(mEntry, SIGNAL(textEdited(QString)), this, SLOT(somethingChanged()));
  connect(mButtons, SIGNAL(accepted()), this, SLOT(accept()));
  connect(mButtons, SIGNAL(rejected()), this, SLOT(reject()));

  setLayout(mLayout);
}

QString NZAddChatDialog::contactName(void) const {
  return mEntry->text();
}

QString NZAddChatDialog::getContactName(QWidget* w) {
  NZAddChatDialog* d = new NZAddChatDialog(w);

  int r = d->exec();
  if (r == QDialog::Rejected) {
    delete d;
    return QString();
  }
  
  QString s = d->contactName();
  delete d;
  return s;
}

void NZAddChatDialog::somethingChanged(void) {
  if (mEntry->text().length() == 0)
    mButtons->button(QDialogButtonBox::Ok)->setEnabled(false);
  else
    mButtons->button(QDialogButtonBox::Ok)->setEnabled(true);
}
