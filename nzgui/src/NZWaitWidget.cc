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
