#ifndef NZADDCONTACTDIALOG_HH_
#define NZADDCONTACTDIALOG_HH_

#include <QtGui/QDialog>

class QLabel;
class QLineEdit;
class QDialogButtonBox;
class QGridLayout;

class NZAddContactDialog : public QDialog {
  Q_OBJECT

public:
  NZAddContactDialog(QWidget* parent = NULL);

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
