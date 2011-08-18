#include "NZStatusWidget.hh"
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QComboBox>

NZStatusWidget::NZStatusWidget(QWidget* parent) : QWidget(parent) {
  mainLayout = new QHBoxLayout;
  subLayout = new QVBoxLayout;

  mUserLogin = tr("norris_c");
  mUserStatus = NZContact::nzDisconnected;

  iconFrame = new QLabel;
  iconFrame->setFixedSize(QSize(48, 48));
  iconFrame->setFrameShadow(QFrame::Sunken);
  iconFrame->setFrameShape(QFrame::StyledPanel);

  loginLabel = new QLabel;
  loginLabel->setText(tr("<b>%1</b> - <i>Offline</i>").arg(mUserLogin));

  statusBox = new QComboBox;
  statusBox->addItem(tr("Connected"));
  statusBox->addItem(tr("Away"));
  statusBox->addItem(tr("Lock"));
  statusBox->addItem(tr("Server"));
  statusBox->setVisible(false);

  subLayout->addWidget(loginLabel);
  subLayout->addWidget(statusBox);

  mainLayout->addWidget(iconFrame);
  mainLayout->addLayout(subLayout);

  setLayout(mainLayout);

  setFixedWidth(250);

  connect(statusBox, SIGNAL(currentIndexChanged(int)), this, SLOT(comboChanged(int)));
}

QString NZStatusWidget::userLogin(void) const {
  return mUserLogin;
}

NZContactStatus NZStatusWidget::userStatus(void) const {
  return mUserStatus;
}

void NZStatusWidget::setUserLogin(const QString& login) {
  mUserLogin = login;
  if (mUserStatus <= NZContact::nzConnection)
    loginLabel->setText(tr("<b>%1</b> - <i>Offline</i>").arg(mUserLogin));
  else
    loginLabel->setText(tr("<b>%1</b>").arg(mUserLogin));
}

void NZStatusWidget::setUserStatus(NZContactStatus status) {
  mUserStatus = status;
  if (mUserStatus <= NZContact::nzConnection) {
    statusBox->setVisible(false);
    loginLabel->setText(tr("<b>%1</b> - <i>Offline</i>").arg(mUserLogin));
  } else {
    statusBox->setCurrentIndex((int)status - (int)NZContact::nzActif);
    statusBox->setVisible(true);
    loginLabel->setText(tr("<b>%1</b>").arg(mUserLogin));
  }
}

void NZStatusWidget::comboChanged(int index) {
  NZContact::Status s = (NZContact::Status)(NZContact::nzActif + index);
  emit userStatusChanged(s);
}
