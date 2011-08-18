#include "NZConversation.hh"

NZConversation::NZConversation(NZContact* contactTo, QObject* parent) : QObject(parent) {
  mContactTo = contactTo;
}

NZConversation::~NZConversation(void) {
  int i = 0;
  while (i < mMessageList.count()) {
    delete mMessageList.at(i);
    i++;
  }
  mMessageList.clear();
}

void NZConversation::addMessage(NZMessage* message) {
  mMessageList.append(message);
  emit updated();
}

int NZConversation::messageCount(void) const {
  return mMessageList.count();
}

NZMessage* NZConversation::messageForIndex(int index) const {
  if (index < 0 || index >= mMessageList.count())
    return NULL;

  return mMessageList.at(index);
}

int NZConversation::indexForMessage(NZMessage* message) const {
  if (mMessageList.contains(message))
    return mMessageList.indexOf(message);
  return -1;
}

NZContact* NZConversation::contactTo(void) const {
  return mContactTo;
}
