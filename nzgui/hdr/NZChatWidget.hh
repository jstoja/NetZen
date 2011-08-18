#ifndef NZCHATWIDGET_HH_
#define NZCHATWIDGET_HH_

#include <QtGui/QWidget>

class NZConversation;
class NZChatView;
class QLineEdit;
class QVBoxLayout;
class QLabel;
class QHBoxLayout;
class QFrame;

class NZChatWidget : public QWidget {
  Q_OBJECT

public:
  NZChatWidget(NZConversation* conversation, QWidget* parent = NULL);

  NZConversation* conversation(void) const;

public slots:
  void sendMessage(void);

protected:
  void resizeEvent(QResizeEvent*);

private:
  NZConversation* mConversation;

  QFrame* mViewWrapper;
  QVBoxLayout* mViewLayout;
  NZChatView* mView;
  QLineEdit* mEdit;
  QVBoxLayout* mLayout;
  QLabel* mUserIcon;
  QLabel* mUserLogin;
  QHBoxLayout* mTopLayout;
};

#endif
