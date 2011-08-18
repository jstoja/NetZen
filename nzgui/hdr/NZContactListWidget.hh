#ifndef NZCONTACTLISTWIDGET_HH_
#define NZCONTACTLISTWIDGET_HH_

#include <QtGui/QTreeView>

class NZContact;
class NZContactModel;
class QMenu;
class QAction;

class NZContactListWidget : public QTreeView {
  Q_OBJECT

public:
  NZContactListWidget(QWidget* parent = NULL);
  ~NZContactListWidget(void);

signals:
  void contactRemoveRequested(NZContact* contact);
  void newChatRequested(NZContact* contact);

public slots:
  void addContact(NZContact* contact);
  void removeContact(NZContact* contact);
  void contactUpdated(NZContact* contact);
  void rightClicked(const QPoint& where);
  void removeContactAction(void);

private slots:
  void itemActive(const QModelIndex& i);

private:
  NZContactModel* mModel;

  QMenu* mContextMenu;
  QAction* mDeleteContactAction;
};

#endif
