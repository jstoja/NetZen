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
  void watchUser(QString user);
  void getUserInfo(QString user);

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
  void locationChange(const std::string& user, const std::string& location);

signals:
  void proxyReceivedMessage(QString contactFrom, QString message);
  void proxyUserStatusChange(QString user, QString status);
  void proxyUserLogin(QString user);
  void proxyUserLogout(QString user);
  void proxyConnectionStatusChange(bool connected);
  void proxyConnectionError(int error);
  void proxyAuthAllowed(void);
  void proxyAuthSucceeded(void);
  void proxyLocationChange(QString user, QString location);
  void connectionReset(void);

protected:
  void timerEvent(QTimerEvent* eve);

private:
  NZController* mController;

  int mTimer;
};

#endif
