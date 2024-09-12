#pragma once

#include "Event.h"
#include <ncurses.h>

class InputManager {
public:
  InputManager(EventDispatcher *dispacter);
  ~InputManager();

  void GetInput(WINDOW *win);

private:
  EventDispatcher *m_Dispatcher;
};
