#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QPushButton>
#include <QtGui/QApplication>
#include "NZAddContactDialog.hh"

NZAddContactDialog::NZAddContactDialog(QWidget* parent) : QDialog(parent) {
  setWindowTitle(tr("Add contact"));

  mIcon = new QLabel;
  // Allow widget to grow to bottom to respect layout
  mIcon->setFixedWidth(32);
  mIcon->setPixmap(QPixmap(":/res/24/user-add.png"));
  mIcon->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

  mText = new QLabel;
  mText->setText(tr("<b>Add contact</b><br /><br />"
		    "Enter the login of the new contact to be added to your"
		    " contact list :"));
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

QString NZAddContactDialog::contactName(void) const {
  return mEntry->text();
}

QString NZAddContactDialog::getContactName(QWidget* w) {
  NZAddContactDialog* d = new NZAddContactDialog(w);

  int r = d->exec();
  if (r == QDialog::Rejected) {
    delete d;
    return QString();
  }
  
  QString s = d->contactName();
  delete d;
  return s;
}

void NZAddContactDialog::somethingChanged(void) {
  if (mEntry->text().length() == 0)
    mButtons->button(QDialogButtonBox::Ok)->setEnabled(false);
  else
    mButtons->button(QDialogButtonBox::Ok)->setEnabled(true);
}
