#ifndef NZWAITWIDGET_HH_
#define NZWAITWIDGET_HH_

#include <QtGui/QWidget>

class QHBoxLayout;
class QVBoxLayout;
class QProgressBar;
class QLabel;

class NZWaitWidget : public QWidget {
public:
  NZWaitWidget(QWidget* parent = NULL);

  void progress(void);
  void progress(QString text);
  void progress(int percent);
  void progress(int percent, QString text);

private:
  QHBoxLayout* mCenterLayout;
  QVBoxLayout* mMainLayout;
  QLabel* mText;
  QProgressBar* mProgress;
};

#endif
