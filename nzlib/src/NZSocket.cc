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

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <errno.h>
#include <cstring>
#include <iostream>
#include "NZSocket.hh"
#include "NZDelegate.hh"

NZSocket::NZSocket(NZDelegate* delegate) {
  mSock = -1;
  mDelegate = delegate;
  mHostPort = 0;
}

void NZSocket::connect(const std::string& hostName, unsigned short hostPort) {
  if (isConnected())
    return ;

  mSock = socket(AF_INET, SOCK_STREAM, 0);
  if (mSock == -1) {
    mDelegate->connectionError(nzSocketError);
    return ;
  }

  sockaddr_in sin;
  hostent* hInfo;

  hInfo = gethostbyname(hostName.c_str());
  if (!hInfo) {
    mDelegate->connectionError(nzResolverError);
    disconnect();
    return ;
  }

  memset(&sin, 0, sizeof sin);

  sin.sin_addr = *(in_addr*)(hInfo->h_addr);
  sin.sin_port = htons(hostPort);
  sin.sin_family = AF_INET;

  if (::connect(mSock, (sockaddr*)(&sin), sizeof sin) == -1) {
    mDelegate->connectionError(nzConnectionError);
    disconnect();
    return ;
  }

  int sMode;
  if ((sMode = fcntl(mSock, F_GETFL)) == -1)
    sMode = 0;
  fcntl(mSock, F_SETFL, sMode | O_NONBLOCK);

  mHostName = hostName;
  mHostPort = hostPort;

  mDelegate->connectionStatusChange(true);
}

void NZSocket::disconnect(void) {
  if (!isConnected())
    return ;

  close(mSock);
  mSock = -1;
  mBuffer = "";
  mHostName = "";
  mHostPort = 0;
  mDelegate->connectionStatusChange(false);
}

bool NZSocket::isConnected(void) const {
  return (mSock >= 0);
}

void NZSocket::sendData(const std::string& data) {
  if (!isConnected())
    return ;

  if (send(mSock, data.c_str(), data.length(), 0) == -1)
    handleError();

  std::cout << "\e[31m" << data << "\e[0m";

  if (data[data.length() - 1] != '\n') {
    if (send(mSock, "\n", 1, 0) == -1)
      handleError();
    std::cout << std::endl;
  }
}

#define _LOCALBUF_SIZE 512

std::string NZSocket::getNextLine(void) {
  char localbuf[_LOCALBUF_SIZE + 1];
  int size;
  std::string ret;

  while (mBuffer.find("\n") == std::string::npos) {
    memset(localbuf, 0, _LOCALBUF_SIZE + 1);
    size = recv(mSock, localbuf, _LOCALBUF_SIZE, 0);
    if (size == 0) {
      ret = mBuffer;
      disconnect();
      return ret;
    }

    if (size == -1) {
      handleError();
      return std::string();
    }

    mBuffer += localbuf;
  }

  ret = mBuffer.substr(0, mBuffer.find("\n"));
  mBuffer = mBuffer.substr(mBuffer.find("\n") + 1, std::string::npos);
  return ret;
}

NZDelegate* NZSocket::delegate(void) const {
  return mDelegate;
}

void NZSocket::handleError(void) {
  if (errno == EAGAIN)
    return ;

  if (errno == ECONNRESET)
    mDelegate->connectionError(nzConnResetError);
  else if (errno == ENOTCONN)
    mDelegate->connectionError(nzConnClosedError);
  else if (errno == ETIMEDOUT)
    mDelegate->connectionError(nzConnTimedOutError);
  else
    return ;

  disconnect();
}
