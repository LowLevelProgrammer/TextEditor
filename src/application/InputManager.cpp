#include "InputManager.h"

#include "Event.h"
#include "KeyboardEvent.h"
#include <ncurses.h>

InputManager::InputManager(EventDispatcher *dispacter)
    : m_Dispatcher(dispacter) {}

InputManager::~InputManager() {}

void InputManager::GetInput(WINDOW *win) {
  int key = wgetch(win);

  if (key != ERR) {
    KeyEvent keyEvent(key);
    m_Dispatcher->Dispatch(keyEvent);
  }
}
