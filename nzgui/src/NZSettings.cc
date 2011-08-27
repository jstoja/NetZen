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

#include <QtCore/QDir>
#include <QtCore/QFile>
#include "NZSettings.hh"

#define NZSETTINGS_MAGIC 0x312e736461ul

struct NZSettingsKey {
  QString keyName;
  NZSettings::KeyType keyType;
  void* value;
  int size;
};

NZSettings::NZSettings(void) {
  // load();
  mDirty = false;
}

NZSettings::NZSettings(QString file) {
  load(file);
  mDirty = false;
}

NZSettings::~NZSettings(void) {
  clear();
}

NZSettingsKey* NZSettings::retrieveKey(QString key) const {
  int i = 0;
  while (i < mKeys.count()) {
    if (mKeys.at(i)->keyName == key)
      return mKeys.at(i);
    i++;
  }

  return NULL;
}

bool NZSettings::keyExists(QString key) const {
  NZSettingsKey* k = retrieveKey(key);

  return (k != NULL);
}

NZSettings::KeyType NZSettings::keyType(QString key) const {
  NZSettingsKey* k = retrieveKey(key);

  if (k)
    return k->keyType;
  else
    return Unknown;
}

bool NZSettings::boolKey(QString key) const {
  NZSettingsKey* k = retrieveKey(key);

  if (k) {
    if (k->keyType == Bool) {
      char val = *(char *)(k->value);
      return (val != 0);
    } else {
      return false;
    }
  } else {
    return false;
  }
}

int NZSettings::intKey(QString key) const {
  NZSettingsKey* k = retrieveKey(key);

  if (k) {
    if (k->keyType == Integer) {
      int val = *(int *)(k->value);
      return val;
    } else {
      return 0;
    }
  } else {
    return 0;
  }
}

QString NZSettings::stringKey(QString key) const {
  NZSettingsKey* k = retrieveKey(key);

  if (k) {
    if (k->keyType == String) {
      char* str = (char *)(k->value);

      QString s = QString::fromAscii(str, k->size);
      return s;
    } else {
      return QString();
    }
  } else {
    return QString();
  }
}

QStringList NZSettings::stringListKey(QString key) const {
  NZSettingsKey* k = retrieveKey(key);
  void* ptr;
  int size;
  char* str;
  QStringList list;

  if (k) {
    if (k->keyType == StringList) {
      ptr = k->value;
      size = *(int *)(ptr);
      str = (char *)((int *)ptr + 1);
      
      while (size != -1) {
	list.append(QString::fromAscii(str, size));
	
	ptr = str + size;
	size = *(int *)(ptr);
	str = (char *)((int *)ptr + 1);
      }
      
      return list;
    } else {
      return QStringList();
    }
  } else {
    return QStringList();
  }
}

void NZSettings::setKey(QString key, bool value) {
  NZSettingsKey* k = retrieveKey(key);

  if (k) {
    if (k->keyType == Bool) {
      char* c = (char*)(k->value);
      *c = value ? 1 : 0;
    } else {
      char* c = new char;
      *c = value ? 1 : 0;
      delete (char *)k->value;
      k->size = sizeof(char);
      k->keyType = Bool;
      k->value = c;
    }
  } else {
    k = new NZSettingsKey;
    k->keyName = key;
    k->keyType = Bool;
    k->size = sizeof(int);

    char* c = new char;
    *c = value ? 1 : 0;
    k->value = c;

    mKeys.append(k);
  }

  mDirty = true;
}

void NZSettings::setKey(QString key, int value) {
  NZSettingsKey* k = retrieveKey(key);

  if (k) {
    if (k->keyType == Integer) {
      int* i = (int*)(k->value);
      *i = value;
    } else {
      int* i = new int;
      *i = value;
      delete (char *)k->value;
      k->size = sizeof(int);
      k->keyType = Integer;
      k->value = i;
    }
  } else {
    k = new NZSettingsKey;
    k->keyName = key;
    k->keyType = Integer;
    k->size = sizeof(int);

    int* i = new int;
    *i = value;
    k->value = i;

    mKeys.append(k);
  }

  mDirty = true;
}

void NZSettings::setKey(QString key, QString value) {
  NZSettingsKey* k = retrieveKey(key);

  if (!k) {
    k = new NZSettingsKey;
    k->keyName = key;
    k->value = NULL;
    mKeys.append(k);
  }

  void* ptr = new char[value.length()];
  char* buf = (char*)ptr;

  memcpy(buf, value.toAscii().constData(), value.length());

  k->keyType = String;
  k->size = value.length();
  if (k->value)
    delete (char*)k->value;
  k->value = ptr;

  mDirty = true;
}

void NZSettings::setKey(QString key, QStringList value) {
  NZSettingsKey* k = retrieveKey(key);

  if (!k) {
    k = new NZSettingsKey;
    k->keyName = key;
    k->value = NULL;
    mKeys.append(k);
  }

  int totalsize = 0;
  int i = 0;

  while (i < value.count()) {
    totalsize += sizeof(int) + value.at(i).length();
    i++;
  }

  void* vptr = new char[totalsize + sizeof(int)];
  void* ptr = vptr;
  i = 0;

  while (i < value.count()) {
    int* size = (int *)ptr;
    char* str = (char *)((int *)ptr + 1);

    *size = value.at(i).length();
    memcpy(str, value.at(i).toAscii().constData(), value.at(i).length());

    ptr = str + *size;
    i++;
  }

  int* c = (int*)ptr;
  *c = -1;

  k->size = totalsize + sizeof(int);
  k->keyType = StringList;
  if (k->value)
    delete (char*)k->value;
  k->value = vptr;

  mDirty = true;
}

void NZSettings::renameKey(QString key, QString newName) {
  NZSettingsKey* k = retrieveKey(key);

  if (!k)
    return ;

  k->keyName = newName;

  mDirty = true;
}

void NZSettings::copyKey(QString key, QString newName) {
  NZSettingsKey* k = retrieveKey(key);

  if (!k)
    return ;

  NZSettingsKey* copy = new NZSettingsKey;
  copy->keyName = newName;
  copy->keyType = k->keyType;
  copy->size = k->size;

  void* copyPtr;
  copyPtr = new char[k->size];
  memcpy(copyPtr, k->value, k->size);
  copy->value = copyPtr;

  mKeys.append(copy);

  mDirty = true;
}

void NZSettings::deleteKey(QString key) {
  NZSettingsKey* k = retrieveKey(key);

  if (!k)
    return ;

  mKeys.removeOne(k);
  delete (char*)k->value;
  delete k;

  mDirty = true;
}

void NZSettings::clear() {
  int i = 0;

  while (i < mKeys.count()) {
    delete (char *)mKeys.at(i)->value;
    delete mKeys.at(i);
    i++;
  }

  mKeys.clear();
  mDirty = true;
}

void NZSettings::load(void) {
  load(QDir::homePath() + "/.adaedra/netzen/settings.ads");
}

void NZSettings::load(QString file) {
  if (!QFile::exists(file))
    return ;

  QFile f(file);
  if (!f.open(QIODevice::ReadOnly))
    return ;

  unsigned long magic;
  magic = *(unsigned long *)(f.read(sizeof(unsigned long)).constData());

  if (magic != NZSETTINGS_MAGIC)
    return ;

  while (!f.atEnd()) {
    NZSettingsKey* k;
    int nameSize;

    nameSize = *(int *)(f.read(sizeof(int)).constData());
    QString name = QString(f.read(nameSize));

    k = new NZSettingsKey;
    k->keyName = name;
    k->keyType = (KeyType)(*(f.read(sizeof(char)).constData()));

    if (k->keyType == Bool) {
      k->value = new char;
      k->size = sizeof(bool);
      *(char *)(k->value) = *(f.read(sizeof(char)).data());
    } else if (k->keyType == Integer) {
      k->value = new int;
      k->size = sizeof(int);
      *(int *)(k->value) = *(int *)(f.read(sizeof(int)).constData());
    } else if (k->keyType == String) {
      k->size = *(int *)(f.read(sizeof(int)).constData());
      k->value = new char[k->size];
      memcpy(k->value, f.read(k->size).constData(), k->size);
    } else if (k->keyType == StringList) {
      k->size = *(int *)(f.read(sizeof(int)).constData());
      k->value = new char[k->size];
      memcpy(k->value, f.read(k->size).constData(), k->size);
    }

    NZSettingsKey* oldK;
    if ((oldK = retrieveKey(name)) != NULL) {
      oldK->size = k->size;
      oldK->value = k->value;
      oldK->keyType = k->keyType;
      delete k;
      k = oldK;
    } else {
      mKeys.append(k);
    }
  }

  f.close();
}

void NZSettings::save(void) {
  save(QDir::homePath() + "/.adaedra/netzen/settings.ads");
}

void NZSettings::save(QString file) {
  QFile f(file);

  if (!QDir("/").exists(file.left(file.lastIndexOf("/")))) {
    QDir("/").mkpath(file.left(file.lastIndexOf("/")));
  }

  if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate))
    return ;

  unsigned long magic = NZSETTINGS_MAGIC;
  f.write((char *)(&magic), sizeof(unsigned long));

  int i = 0;
  while (i < mKeys.count()) {
    int ibuf;
    char cbuf;
    NZSettingsKey* k = mKeys.at(i);

    ibuf = k->keyName.length();
    f.write((char *)(&ibuf), sizeof(ibuf));
    f.write(k->keyName.toAscii().constData(), ibuf);

    cbuf = (int)k->keyType;
    f.write(&cbuf, sizeof(cbuf));

    if (k->keyType == Bool) {
      f.write((char*)k->value, sizeof(char));
    } else if (k->keyType == Integer) {
      f.write((char*)k->value, sizeof(int));
    } else if (k->keyType == String) {
      ibuf = k->size;
      f.write((char*)(&ibuf), sizeof(ibuf));
      f.write((char*)k->value, ibuf);
    } else if (k->keyType == StringList) {
      ibuf = k->size;
      f.write((char*)(&ibuf), sizeof(ibuf));
      f.write((char*)k->value, ibuf);
    }

    i++;
  }

  f.close();
}

bool NZSettings::isDirty(void) const {
  return mDirty;
}
