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

#include <QtCore/QTimerEvent>
#include "NZControllerProxy.hh"
#include "NZControllerDelegate.hh"

NZControllerProxy::NZControllerProxy(void) {
  mController = new NZController(this);

  mTimer = startTimer(100);
}

NZControllerProxy::~NZControllerProxy(void) {
  killTimer(mTimer);

  delete mController;
}

void NZControllerProxy::connect(QString hostName, quint16 hostPort) {
  mController->connect(hostName.toStdString(), hostPort);
}

void NZControllerProxy::login(QString loginName, QString loginPwd,
			      QString location, QString userData) {
  mController->login(loginName.toStdString(), loginPwd.toStdString(),
		     location.toStdString(), userData.toStdString());
}

void NZControllerProxy::changeStatus(QString status) {
  mController->changeStatus(status.toStdString());
}

void NZControllerProxy::sendMessage(QString contactTo, QString message) {
  mController->sendMessage(contactTo.toStdString(), message.toStdString());
}

QString NZControllerProxy::login(void) const {
  return QString::fromStdString(mController->login());
}

void NZControllerProxy::timerEvent(QTimerEvent* eve) {
  if (eve->timerId() == mTimer)
    mController->loop();
}

void NZControllerProxy::receivedMessage(const std::string& contactFrom, const std::string& message) {
  emit proxyReceivedMessage(QString::fromStdString(contactFrom),
			    QString::fromStdString(message));
}

void NZControllerProxy::userStatusChange(const std::string& user, const std::string& status) {
  emit proxyUserStatusChange(QString::fromStdString(user),
			     QString::fromStdString(status));
}

void NZControllerProxy::userLogin(const std::string& user) {
  emit proxyUserLogin(QString::fromStdString(user));
}

void NZControllerProxy::userLogout(const std::string& user) {
  emit proxyUserLogout(QString::fromStdString(user));
}

void NZControllerProxy::connectionStatusChange(bool connected) {
  emit proxyConnectionStatusChange(connected);
}

void NZControllerProxy::connectionError(int error) {
  emit proxyConnectionError(error);
}

void NZControllerProxy::authAllowed(void) {
  emit proxyAuthAllowed();
}

void NZControllerProxy::authSucceeded(void) {
  emit proxyAuthSucceeded();
}

void NZControllerProxy::close(void) {
  mController->socket()->disconnect();
}

bool NZControllerProxy::isConnected(void) const {
  return mController->socket()->isConnected();
}
