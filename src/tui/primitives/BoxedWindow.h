#pragma once

#include "Window.h"

class BoxedWindow : public Window {
public:
  BoxedWindow(int h, int w, int y, int x);
  ~BoxedWindow();

  void Draw(const std::string &content) override;
};
