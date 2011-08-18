#include <QtGui/QApplication>
#include <QtCore/QTextCodec>
#include "NZGuiController.hh"

int main(int argc, char** argv) {
  QApplication qtApp(argc, argv);

  QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

  NZGuiController nzApp;
  nzApp.showMainWindow();

  return qtApp.exec();
}
