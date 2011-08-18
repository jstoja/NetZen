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

#ifndef NZADDCHATDIALOG_HH_
#define NZADDCHATDIALOG_HH_

#include <QtGui/QDialog>

class QLabel;
class QLineEdit;
class QDialogButtonBox;
class QGridLayout;

class NZAddChatDialog : public QDialog {
  Q_OBJECT

public:
  NZAddChatDialog(QWidget* parent = NULL);

  QString contactName(void) const;

  static QString getContactName(QWidget* parent);

private slots:
  void somethingChanged(void);

private:
  QLabel* mIcon;
  QLabel* mText;
  QLineEdit* mEntry;
  QDialogButtonBox* mButtons;

  QGridLayout* mLayout;
};

#endif
