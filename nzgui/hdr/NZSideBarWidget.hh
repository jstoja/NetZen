#ifndef NZSIDEBARWIDGET_HH_
#define NZSIDEBARWIDGET_HH_

#include <QtGui/QTreeWidget>
#include <QtCore/QMap>

class QTreeWidgetItem;
class NZConversation;

class NZSideBarWidget : public QTreeWidget {
  Q_OBJECT

public:
  NZSideBarWidget(QWidget* parent = NULL);

public slots:
  void chatOpened(NZConversation* conversation);
  void chatClosed(NZConversation* conversation);
  void chatUnread(NZConversation* conversation, int messages);
  void chatActive(NZConversation* conversation);
  void contactListActive(void);

signals:
  void contactListRequested(void);
  void chatRequested(NZConversation* conversation);

private slots:
  void itemActive(QTreeWidgetItem* item, int column);

private:
  QTreeWidgetItem* mNetZenItem;
  QTreeWidgetItem* mChatItem;

  QTreeWidgetItem* mContactListItem;

  QMap<NZConversation*, QTreeWidgetItem*> mChatListItems;
};

#endif
