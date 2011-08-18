#include "NZChatView.hh"
#include "NZConversation.hh"
#include "NZMessage.hh"
#include "NZGuiController.hh"
#include <QtGui/QTextDocument>
#include <QtGui/QPainter>
#include <QtWebKit/QWebFrame>

NZChatView::NZChatView(NZConversation* conversation, QWidget* parent) : QWebView(parent) {
  mConversation = conversation;

  setRenderHint(QPainter::Antialiasing, true);
  setRenderHint(QPainter::TextAntialiasing, true);

  connect(mConversation, SIGNAL(updated()), this, SLOT(conversationUpdated()));
  connect(this, SIGNAL(loadFinished(bool)), this, SLOT(doneLoading()));
  load(QUrl("qrc:/res/html/conversation.html"));
  lastAddedMessage = NULL;
}

void NZChatView::conversationUpdated(void) {
  int i = mConversation->indexForMessage(lastAddedMessage) + 1;

  while (i < mConversation->messageCount()) {
    NZMessage* m = mConversation->messageForIndex(i);

    if (m->messageType() == nzReceivedMessage) {
      page()->mainFrame()->evaluateJavaScript(QString("nz.addInMessage(\"%1\", \"%2\");")
					      .arg(Qt::escape(m->message()))
					      .arg(m->timeStamp().toString("hh:mm")));
    } else {
      page()->mainFrame()->evaluateJavaScript(QString("nz.addOutMessage(\"%1\", \"%2\");")
					      .arg(Qt::escape(m->message()))
					      .arg(m->timeStamp().toString("hh:mm")));
    }

    i++;
  }

  lastAddedMessage = mConversation->messageForIndex(i - 1);
}

NZConversation* NZChatView::conversation(void) const {
  return mConversation;
}

void NZChatView::doneLoading(void) {
  // This is tricky; could we try to determinate real factor to apply ?
  setTextSizeMultiplier(0.8);

  page()->mainFrame()->evaluateJavaScript(QString("nz.init(\"%1\", \"%2\");")
					  .arg(NZGuiController::instance()->me()->login())
					  .arg(mConversation->contactTo()->login()));
  page()->mainFrame()->evaluateJavaScript(QString("nz.initStyle(\"%1\", \"%2\");")
					  .arg(font().family()).arg(font().pixelSize()));

  lastAddedMessage = NULL;
  conversationUpdated();
}
