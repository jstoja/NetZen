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

#ifndef NZDELEGATE_HH_
#define NZDELEGATE_HH_

#include <string>

class NZDelegate {
public:
  inline NZDelegate(void) { };
  virtual inline ~NZDelegate(void) { };

  virtual void receivedMessage(const std::string& contactFrom, const std::string& message) = 0;
  virtual void userStatusChange(const std::string& user, const std::string& status) = 0;
  virtual void userLogin(const std::string& user) = 0;
  virtual void userLogout(const std::string& user) = 0;
  virtual void connectionStatusChange(bool connected) = 0;
  virtual void connectionError(int error) = 0;
  virtual void authAllowed(void) = 0;
  virtual void authSucceeded(void) = 0;
};

#endif
