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

#ifndef NZCONTROLLER_HH_
#define NZCONTROLLER_HH_

#include <string>

class NZDelegate;
class NZSocket;

class NZController {
public:
  NZController(NZDelegate* delegate);
  ~NZController(void);

  NZDelegate* delegate(void) const;
  NZSocket* socket(void) const;
  void connect(const std::string& hostName, unsigned short hostPort);
  void login(const std::string& loginName, const std::string& loginPwd,
	     const std::string& location, const std::string& userData);
  void changeStatus(const std::string& status);
  void sendMessage(const std::string& contactTo, const std::string& message);

  void loop(void);

  std::string login(void) const;

  static std::string urlEncode(const std::string& str);
  static std::string urlDecode(const std::string& str);
  static std::string md5(const std::string str);

private:
  void cutSalutString(const std::string& salut);
  void cutCmd(const std::string& cmd);

  NZDelegate* mDelegate;
  NZSocket* mSocket;

  bool mIsAuth;
  bool mIsAuthAllowed;
  std::string mHostMd5;
  std::string mClientHost;
  unsigned short mClientPort;
  std::string mLogin;
};

#endif
