#include "InputManager.h"

#include "Event.h"
#include "KeyboardEvent.h"
#include <ncurses.h>

InputManager::InputManager(EventDispatcher *dispacter)
    : m_Dispatcher(dispacter) {}

InputManager::~InputManager() {}

void InputManager::GetInput() {
  int key = getch();

  if (key != ERR) {
    KeyEvent keyEvent(key);
    m_Dispatcher->Dispatch(keyEvent);
  }
}
