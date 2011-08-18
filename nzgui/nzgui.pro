TEMPLATE         = app
TARGET           = nzgui
QT               = core gui webkit

include(../mk/qt.pri)

LIBS            += -L../lib -lnzlib -lmd5

SOURCES          = NZAddChatDialog.cc      \
                   NZAddContactDialog.cc   \
                   NZChatView.cc           \
                   NZChatWidget.cc         \
                   NZConnectionWidget.cc   \
                   NZContact.cc            \
                   NZContactListWidget.cc  \
                   NZContactModel.cc       \
                   NZControllerProxy.cc    \
                   NZConversation.cc       \
                   NZGuiController.cc      \
                   NZMainWindow.cc         \
                   NZMessage.cc            \
                   NZSideBarWidget.cc      \
                   NZStatusWidget.cc       \
                   NZWaitWidget.cc         \
                   main.cc
HEADERS          = NZAddChatDialog.hh      \
                   NZAddContactDialog.hh   \
                   NZChatView.hh           \
                   NZChatWidget.hh         \
                   NZConnectionWidget.hh   \
                   NZContact.hh            \
                   NZContactListWidget.hh  \
                   NZContactModel.hh       \
                   NZControllerProxy.hh    \
                   NZConversation.hh       \
                   NZGuiController.hh      \
                   NZMainWindow.hh         \
                   NZMessage.hh            \
                   NZSideBarWidget.hh      \
                   NZStatusWidget.hh       \
                   NZWaitWidget.hh
RESOURCES        = nzgui.qrc

