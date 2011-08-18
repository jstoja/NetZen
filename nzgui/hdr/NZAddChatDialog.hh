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
