#ifndef NZSTATUSWIDGET_HH_
#define NZSTATUSWIDGET_HH_

#include <QtGui/QWidget>
#include "NZContact.hh"

class QLabel;
class QComboBox;
class QVBoxLayout;
class QHBoxLayout;

class NZStatusWidget : public QWidget {
  Q_OBJECT
  Q_ENUMS(NZContactStatus)

public:
  NZStatusWidget(QWidget* parent = NULL);

  QString userLogin(void) const;
  NZContactStatus userStatus(void) const;

public slots:
  void setUserLogin(const QString& login);
  void setUserStatus(NZContact::Status status);

signals:
  void userStatusChanged(NZContact::Status status);

private slots:
  void comboChanged(int index);

private:
  QString mUserLogin;
  NZContactStatus mUserStatus;

  QLabel* iconFrame;
  QLabel* loginLabel;
  QComboBox* statusBox;
  QHBoxLayout* mainLayout;
  QVBoxLayout* subLayout;
};

#endif
