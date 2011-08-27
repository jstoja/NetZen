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

#ifndef NZSETTINGS_HH_
#define NZSETTINGS_HH_

struct NZSettingsKey;

class NZSettings {
public:
  enum KeyType {
    Unknown = 0,
    Bool,
    Integer,
    String,
    StringList
  };

  NZSettings(void);
  NZSettings(QString file);
  ~NZSettings(void);

  bool keyExists(QString key) const;
  KeyType keyType(QString key) const;

  bool boolKey(QString key) const;
  int intKey(QString key) const;
  QString stringKey(QString key) const;
  QStringList stringListKey(QString key) const;

  void setKey(QString key, bool value);
  void setKey(QString key, int value);
  void setKey(QString key, QString value);
  void setKey(QString key, QStringList value);

  void renameKey(QString key, QString newName);
  void copyKey(QString key, QString newName);
  void deleteKey(QString key);

  void clear(void);
  void load(void);
  void load(QString file);
  void save(void);
  void save(QString file);

  bool isDirty(void) const;

private:
  NZSettingsKey* retrieveKey(QString key) const;
  QList<NZSettingsKey*> mKeys;
  bool mDirty;
};

#endif
