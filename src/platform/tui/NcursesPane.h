#pragma once

#include "IPane.h"
#include <ncurses.h>

class NcursesPane : public IPane {
public:
  NcursesPane(int height, int width, int y, int x);
  ~NcursesPane();

  virtual void Render(IRenderer *renderer) = 0;
  virtual void OnEvent(Event &event) = 0;
  virtual Position GetCaretPosition() const = 0;
};
