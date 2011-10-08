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
  connect(page()->mainFrame(), SIGNAL(contentsSizeChanged(QSize)), this, SLOT(conversationViewUpdated()));
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

void NZChatView::conversationViewUpdated(void) {
  page()->mainFrame()->setScrollBarValue(Qt::Vertical, page()->mainFrame()->scrollBarMaximum(Qt::Vertical));
}
