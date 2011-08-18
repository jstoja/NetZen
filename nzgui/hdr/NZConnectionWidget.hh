#ifndef NZCONNECTIONWIDGET_HH_
#define NZCONNECTIONWIDGET_HH_

#include <QtGui/QWidget>

class QLabel;
class QLineEdit;
class QSpinBox;
class QCheckBox;
class QPushButton;
class QComboBox;
class QGroupBox;
class QVBoxLayout;
class QHBoxLayout;
class QFormLayout;
class QDialogButtonBox;

class NZConnectionWidget : public QWidget {
  Q_OBJECT

public:
  NZConnectionWidget(QWidget* parent = NULL);

public slots:
  void expandServer(void);
  void collapseServer(void);
  void expandUser(void);
  void somethingChanged(void);

signals:
  void connectionRequested(QString hostName, quint16 hostPort, QString userName, QString userPwd,
			   QString userLocation, QString userData);

private slots:
  void connectionRequestedPrivate(void);

private:
  QLabel* mIcon;
  QLabel* mHeaderText;
  QLabel* mServerLabel;
  QLabel* mAppearAfterLoginLabel;
  QLabel* mServerColumn;
  QLineEdit* mHostName;
  QLineEdit* mUserLogin;
  QLineEdit* mUserPwd;
  QLineEdit* mLocation;
  QLineEdit* mUserData;
  QSpinBox* mHostPort;
  QCheckBox* mSavePwd;
  QPushButton* mEditServer;
  QPushButton* mDefaultServer;
  QPushButton* mUserMore;
  QPushButton* mConnect;
  QComboBox* mAppearAfterLogin;
  QGroupBox* mServerGroup;
  QGroupBox* mUserGroup;
  QDialogButtonBox* mButtonBox;
  QVBoxLayout* mMainLayout;
  QHBoxLayout* mCenterLayout;
  QHBoxLayout* mHeadLayout;
  QHBoxLayout* mHeadServerLayout;
  QHBoxLayout* mServerLayout;
  QHBoxLayout* mUserMoreLayout;
  QHBoxLayout* mDefaultServerLayout;
  QFormLayout* mServerGroupLayout;
  QFormLayout* mUserLayout;
};

#endif
