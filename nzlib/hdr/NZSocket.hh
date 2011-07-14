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

#ifndef NZSOCKET_HH_
#define NZSOCKET_HH_

#include <string>

#define nzSocketError		1
#define nzResolverError		2
#define nzConnectionError	3
#define nzConnResetError	4
#define nzConnClosedError	5
#define nzConnTimedOutError	6
#define nzAuthRefusedError	7
#define nzAuthFailedError	8

class NZDelegate;

class NZSocket {
public:
  NZSocket(NZDelegate* delegate);

  void connect(const std::string& hostName, unsigned short hostPort);
  void disconnect(void);
  bool isConnected(void) const;
  std::string hostName(void) const;
  unsigned short hostPort(void) const;
  void sendData(const std::string& data);
  std::string getNextLine(void);

  NZDelegate* delegate(void) const;

private:
  void handleError(void);

  NZDelegate* mDelegate;
  std::string mBuffer;
  int mSock;
  std::string mHostName;
  unsigned short mHostPort;
};

#endif
