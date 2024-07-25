#pragma once

#include "Editor.h"
#include "TUI.h"
#include <ncurses.h>

class Application {
public:
  Application();
  ~Application();

  void ProcessInput();
  void Clear();
  void Draw();
  void Refresh();
  void Run();

private:
  Editor m_Editor;
  TUI m_TUI;
  WINDOW *win;
  bool m_IsRunning;
};
