#pragma once

#include "Event.h"

class InputManager {
public:
  InputManager(EventDispatcher *dispacter);
  ~InputManager();

  void GetInput();

private:
  EventDispatcher *m_Dispatcher;
};
