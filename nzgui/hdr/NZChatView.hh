#ifndef NZCHATVIEW_HH_
#define NZCHATVIEW_HH_

#include <QtGui/QWidget>
#include <QtWebKit/QWebView>

class NZConversation;
class NZMessage;

class NZChatView : public QWebView {
  Q_OBJECT

public:
  NZChatView(NZConversation* conversation, QWidget* parent = NULL);

  NZConversation* conversation(void) const;

public slots:
  void conversationUpdated(void);

private slots:
  void doneLoading(void);

private:
  NZConversation* mConversation;
  NZMessage* lastAddedMessage;
};

#endif
