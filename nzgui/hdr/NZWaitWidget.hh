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

#ifndef NZWAITWIDGET_HH_
#define NZWAITWIDGET_HH_

#include <QtGui/QWidget>

class QHBoxLayout;
class QVBoxLayout;
class QProgressBar;
class QLabel;

class NZWaitWidget : public QWidget {
public:
  NZWaitWidget(QWidget* parent = NULL);

  void progress(void);
  void progress(QString text);
  void progress(int percent);
  void progress(int percent, QString text);

private:
  QHBoxLayout* mCenterLayout;
  QVBoxLayout* mMainLayout;
  QLabel* mText;
  QProgressBar* mProgress;
};

#endif
