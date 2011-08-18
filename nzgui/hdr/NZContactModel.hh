#ifndef NZCONTACTMODEL_HH_
#define NZCONTACTMODEL_HH_

#include <QtCore/QAbstractListModel>
#include <QtCore/QList>
#include "NZContact.hh"

class NZContactModel : public QAbstractListModel {
  Q_OBJECT

public:
  NZContactModel(QObject* parent = NULL);

  int rowCount(const QModelIndex& index) const;
  int columnCount(const QModelIndex& index) const;
  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

  void addContact(NZContact* contact);
  void removeContact(NZContact* contact);
  void clearContacts(void);

  NZContact* contactForIndex(const QModelIndex& index) const;
  NZContact* contactForIndex(int index) const;

  int indexForContact(NZContact* contact) const;
  QModelIndex modelIndexForContact(NZContact* contact, int column = 0) const;

public slots:
  void contactUpdated(NZContact* who);

private:
  QList<NZContact*> mContacts;
};

#endif
