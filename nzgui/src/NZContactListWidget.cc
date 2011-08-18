#include <QtGui/QMenu>
#include <QtGui/QAction>
#include "NZContactListWidget.hh"
#include "NZContact.hh"
#include "NZContactModel.hh"

NZContactListWidget::NZContactListWidget(QWidget* parent) : QTreeView(parent) {
  setIconSize(QSize(32, 32));
  setRootIsDecorated(false);

  mModel = new NZContactModel;
  setModel(mModel);

  mContextMenu = new QMenu;
  mDeleteContactAction = new QAction(this);
  mDeleteContactAction->setText(tr("Delete contact"));
  mContextMenu->addAction(mDeleteContactAction);

  setContextMenuPolicy(Qt::CustomContextMenu);

  connect(this, SIGNAL(customContextMenuRequested(QPoint)),
	  this, SLOT(rightClicked(QPoint)));
  connect(mDeleteContactAction, SIGNAL(triggered()),
	  this, SLOT(removeContactAction()));
  connect(this, SIGNAL(activated(QModelIndex)),
	  this, SLOT(itemActive(QModelIndex)));
}

NZContactListWidget::~NZContactListWidget(void) {
  delete mModel;
  delete mContextMenu;
}

void NZContactListWidget::addContact(NZContact* contact) {
  connect(contact, SIGNAL(infoUpdated(NZContact*)), this, SLOT(contactUpdated(NZContact*)));
  mModel->addContact(contact);
}

void NZContactListWidget::removeContact(NZContact* contact) {
  disconnect(contact, SIGNAL(infoUpdated(NZContact*)), this, SLOT(contactUpdated(NZContact*)));
  mModel->removeContact(contact);
}

void NZContactListWidget::contactUpdated(NZContact* contact) {
  // TO DO
}

void NZContactListWidget::rightClicked(const QPoint& where) {
  QModelIndex index = indexAt(where);
  if (!index.isValid())
    return ;

  mContextMenu->popup(mapToGlobal(where), mDeleteContactAction);
}

void NZContactListWidget::removeContactAction(void) {
  NZContact* c = mModel->contactForIndex(currentIndex());
  emit contactRemoveRequested(c);
}

void NZContactListWidget::itemActive(const QModelIndex& i) {
  NZContact* who = mModel->contactForIndex(i);
  if (who == NULL)
    return ;

  emit newChatRequested(who);
}

