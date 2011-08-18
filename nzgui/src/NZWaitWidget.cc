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

#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QProgressBar>
#include <QtGui/QLabel>
#include "NZWaitWidget.hh"

NZWaitWidget::NZWaitWidget(QWidget* parent) : QWidget(parent) {
  mCenterLayout = new QHBoxLayout;
  mMainLayout = new QVBoxLayout;
  mText = new QLabel;
  mProgress = new QProgressBar;

  mText->setText(tr("Please wait."));

  mProgress->setRange(0, 0);
  mProgress->setFixedWidth(250);
  mProgress->setTextVisible(false);

  mMainLayout->addStretch();
  mMainLayout->addWidget(mText);
  mMainLayout->addWidget(mProgress);
  mMainLayout->addStretch();

  mCenterLayout->addStretch();
  mCenterLayout->addLayout(mMainLayout);
  mCenterLayout->addStretch();

  setLayout(mCenterLayout);
}

void NZWaitWidget::progress(void) {
  mText->setVisible(false);
  mProgress->setRange(0, 0);
}

void NZWaitWidget::progress(QString text) {
  mText->setVisible(true);
  mText->setText(text);
  mProgress->setRange(0, 0);
}

void NZWaitWidget::progress(int percent) {
  mText->setVisible(false);
  mProgress->setRange(0, 100);
  mProgress->setValue(percent);
}

void NZWaitWidget::progress(int percent, QString text) {
  mText->setVisible(true);
  mText->setText(text);
  mProgress->setRange(0, 100);
  mProgress->setValue(percent);
}
