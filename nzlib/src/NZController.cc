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

#include <stdio.h>
#include <iostream>
#include <cstring>
#include <ctime>

#include "NZController.hh"
#include "NZSocket.hh"
#include "NZDelegate.hh"
#include "md5.h"

NZController::NZController(NZDelegate* delegate) {
  mDelegate = delegate;
  mSocket = new NZSocket(delegate);

  mIsAuth = false;
  mIsAuthAllowed = false;
  mHostMd5 = "";
  mClientHost = "";
  mClientPort = 0;
}

NZController::~NZController(void) {
  delete mSocket;
}

NZDelegate* NZController::delegate(void) const {
  return mDelegate;
}

NZSocket* NZController::socket(void) const {
  return mSocket;
}

void NZController::connect(const std::string& hostName, unsigned short hostPort) {
  if (mSocket->isConnected())
    return ;

  mSocket->connect(hostName, hostPort);
  mHostMd5 = "";
  mIsAuth = false;
  mIsAuthAllowed = false;
}

#define REP_OK "rep 002"

void NZController::loop(void) {
  std::string data;

  while (mSocket->isConnected() &&
	 (data = mSocket->getNextLine()).length() > 0) {

    if (mHostMd5.length() == 0)
      cutSalutString(data);
    else if (!mIsAuthAllowed) {
      if (data.compare(0, strlen(REP_OK), REP_OK) == 0) {
	mIsAuthAllowed = true;
	mDelegate->authAllowed();
      }
      else
	mDelegate->connectionError(nzAuthRefusedError);
    } else if (!mIsAuth) {
      if (data.compare(0, strlen(REP_OK), REP_OK) == 0) {
	mIsAuth = true;
	mDelegate->authSucceeded();
      } else {
	mLogin = "";
	mDelegate->connectionError(nzAuthFailedError);
      }
    } else {
      if (data.compare(0, 4, "rep ") == 0) {
	// Answer to something, surely irrelevant.
      }
      if (data.compare(0, 5, "ping ") == 0) {
	mSocket->sendData(data);
      }
      if (data.compare(0, 9, "user_cmd ") == 0
	  || data.compare(0, 4, "cmd ") == 0) {
	cutCmd(data);
      }
    }
  }

  if (!mSocket->isConnected()) {
    mLogin = "";
    mHostMd5 = "";
  }
}

#define SALUT_BEGIN "salut "

void NZController::cutSalutString(const std::string& salut) {
  if (0 != salut.compare(0, strlen(SALUT_BEGIN), SALUT_BEGIN)) {
    // Server sends shit, cancel that.
    mSocket->disconnect();
    return ;
  }

  const char* cmdline = salut.c_str();
  char md5hash[32 + 1];
  char clientIp[16];
  unsigned int clientPort;
  memset(md5hash, 0, 32 + 1);
  memset(md5hash, 0, 16);

  if (sscanf(cmdline, "salut %*d %32c %s %ud", md5hash, clientIp, &clientPort) < 3) {
    // Error while parsing string
    mSocket->disconnect();
    return ;
  }

  mHostMd5 = md5hash;
  mClientHost = clientIp;
  mClientPort = clientPort;

  mSocket->sendData("auth_ag ext_user none none");
}

void NZController::login(const std::string& loginName, const std::string& loginPwd,
			 const std::string& location, const std::string& userData) {
  if (!mIsAuthAllowed)
    return ;

  std::string myHash;
  char clientPort_s[6];
  sprintf(clientPort_s, "%u", mClientPort);

  myHash.append(mHostMd5).append("-").append(mClientHost).append("/").append(clientPort_s);
  myHash.append(loginPwd);

  myHash = NZController::md5(myHash);

  std::string loginCmd;

  loginCmd.append("ext_user_log ").append(loginName).append(" ")
    .append(myHash).append(" ");
  loginCmd.append(NZController::urlEncode(location)).append(" ");
  loginCmd.append(NZController::urlEncode(userData));

  mSocket->sendData(loginCmd);
  mLogin = loginName;
}

void NZController::changeStatus(const std::string& status) {
  std::string command;
  char timestamp[11];

  sprintf(timestamp, "%ld", time(NULL));
  
  command.append("state ").append(status).append(":").append(timestamp);
  mSocket->sendData(command);
}

void NZController::sendMessage(const std::string& contactTo, const std::string& message) {
  std::string cmd;

  cmd.append("user_cmd msg_user ").append(contactTo).append(" msg ");
  cmd.append(NZController::urlEncode(message));

  mSocket->sendData(cmd);
}

void NZController::cutCmd(const std::string& cmd) {
  char fromLogin[256];
  char command[256];
  int commandBegin;

  fromLogin[0] = 0;
  command[0] = 0;

  // user_cmd [socket]:user:[trust level]:[login]@[ip]:[machine type]:[location]:[group] |
  // [command] [args] ...
  if (sscanf(cmd.c_str(),
	     "%*s %*d:user:%*[^:]:%[^:@]@%*[^:]:%*[^:]:%*[^:]:%*s | %s%n",
	     fromLogin, command, &commandBegin) < 2) {
    return ;
  }
  
  if (strcmp(command, "msg") == 0) {
    std::string msg = cmd.substr(commandBegin + 1, std::string::npos);
    msg = NZController::urlDecode(msg.substr(0, msg.find(' ')));
    mDelegate->receivedMessage(fromLogin, msg);
  } else if (strcmp(command, "login") == 0) {
    mDelegate->userLogin(fromLogin);
  } else if (strcmp(command, "logout") == 0) {
    mDelegate->userLogout(fromLogin);
  } else if (strcmp(command, "state") == 0) {
    std::string status = cmd.substr(commandBegin + 1, std::string::npos);
    status = status.substr(0, status.find(':'));
    mDelegate->userStatusChange(fromLogin, status);
  } else if (strcmp(command, "who") == 0) {
    std::string whoData = cmd.substr(commandBegin + 1, std::string::npos);
    cutWho(fromLogin, whoData);
  }
}

#define UNENCODED "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-"
#define MKUCHAR(x) ((x) < 0 ? 127 + 0 - (x) : (x))

std::string NZController::urlEncode(const std::string& str) {
  size_t pos = 0;
  size_t nos = 0;
  std::string ret;
  char buf[4];

  memset(buf, 0, 4);
  while (pos != std::string::npos) {
    nos = str.find_first_not_of(UNENCODED, pos);
      ret += str.substr(pos, nos - pos);
    if (nos != std::string::npos) {
      snprintf(buf, 4, "%%%02X", MKUCHAR(str[nos]));
      ret += buf;
      pos = nos + 1;
    } else {
      pos = nos;
    }
  }

  return ret;
}

std::string NZController::urlDecode(const std::string& str) {
  std::string ret;
  size_t pos = 0;
  size_t nos;
  std::string nbr_s;
  unsigned int nbr_c;

  while (pos != std::string::npos) {
    nos = str.find('%', pos);
    ret += str.substr(pos, nos - pos);
    if (nos + 2 > str.length()) {
      pos = nos + 1;
    } else if (nos != std::string::npos) {
      nbr_s = str.substr(nos + 1, 2);
      sscanf(nbr_s.c_str(), "%X", &nbr_c);
      ret += (unsigned char)nbr_c;
      pos = nos + 3;
    } else {
      // ret += str.substr(pos, std::string::npos);
      pos = nos;
    }
  }

  std::cout << "[NZLib] Decoded this :" << ret << std::endl;
  std::cout << "[NZLib] From this :" << str << std::endl;
  return ret;
}

std::string NZController::md5(const std::string str) {
  md5_state_t pms;
  unsigned char basic_hash[16];
  std::string hash;

  md5_init(&pms);
  md5_append(&pms, (const md5_byte_t*)str.c_str(), str.length());
  md5_finish(&pms, basic_hash);

  char buf[3];
  for (int i = 0; i < 16; i++) {
    sprintf(buf, "%02x", basic_hash[i]);
    hash += buf;
  }

  return hash;
}

std::string NZController::login(void) const {
  return mLogin;
}

void NZController::watchUser(const std::string& user) {
  std::string cmd = "user_cmd watch_log_user {";
  cmd.append(user);
  cmd.append("}");

  mSocket->sendData(cmd);
}

void NZController::askUserStatus(const std::string& user) {
  std::string cmd = "user_cmd who {";
  cmd.append(user);
  cmd.append("}");

  mSocket->sendData(cmd);
}

void NZController::cutWho(const std::string& user, const std::string& whoData) {
  // [sock] [user] [ip] [logintime] [statustime] [trust/l] [trust/h] [workstation] [location]
  // [group] [status:time] [userdata]

  char location[128];
  char status[128];

  if (strncmp(whoData.c_str(), REP_OK, strlen(REP_OK)) == 0)
    return ;

  sscanf(whoData.c_str(),
	 "%*s %*s %*s %*s %*s %*s %*s %*s %s %*s %s %*s",
	 location, status);

  std::string status_s = status;
  // status_s = status_s.substr(0, status_s.find(':'));

  mDelegate->userStatusChange(user, status_s);
  mDelegate->locationChange(user, urlDecode(std::string(location)));

  std::cout << "[NZLib] User " << user << " is at " << location << std::endl;
}
