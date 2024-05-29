#pragma once

#include "Editor.h"
#include "TUI.h"

class Application {
public:
  Application();
  ~Application();

  void Run();

private:
  Editor m_Editor;
  TUI m_TUI;
  bool m_IsRunning;
};
