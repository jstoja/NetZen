#ifndef NZCONTROLLERPROXY_HH_
#define NZCONTROLLERPROXY_HH_

#include <QtCore/QObject>
#include "NZController.hh"
#include "NZDelegate.hh"
#include "NZSocket.hh"

class NZControllerProxy : public QObject, public NZDelegate {
  Q_OBJECT
  Q_ENUMS(CoreError)

public:
  enum CoreError {
    SocketError = nzSocketError,
    ResolverError = nzResolverError,
    ConnectionError = nzConnectionError,
    ConnResetError = nzConnResetError,
    ConnClosedError = nzConnClosedError,
    ConnTimedOutError = nzConnTimedOutError,
    AuthRefusedError = nzAuthRefusedError,
    AuthFailedError = nzAuthFailedError
  };

  NZControllerProxy(void);
  ~NZControllerProxy(void);

  void connect(QString hostName, quint16 hostPort);
  void login(QString loginName, QString loginPwd,
	     QString location, QString userData);
  void changeStatus(QString status);
  void sendMessage(QString contactTo, QString message);
  void close(void);

  QString login(void) const;
  bool isConnected(void) const;

  void receivedMessage(const std::string& contactFrom, const std::string& message);
  void userStatusChange(const std::string& user, const std::string& status);
  void userLogin(const std::string& user);
  void userLogout(const std::string& user);
  void connectionStatusChange(bool connected);
  void connectionError(int error);
  void authAllowed(void);
  void authSucceeded(void);

signals:
  void proxyReceivedMessage(QString contactFrom, QString message);
  void proxyUserStatusChange(QString user, QString status);
  void proxyUserLogin(QString user);
  void proxyUserLogout(QString user);
  void proxyConnectionStatusChange(bool connected);
  void proxyConnectionError(int error);
  void proxyAuthAllowed(void);
  void proxyAuthSucceeded(void);
  void connectionReset(void);

protected:
  void timerEvent(QTimerEvent* eve);

private:
  NZController* mController;

  int mTimer;
};

#endif
