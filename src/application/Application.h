#pragma once

#include "Editor.h"
#include "TUI.h"
#include "Window.h"

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
  TUI m_MainWindow;
  Window *m_SecondaryWindow;
  bool m_IsRunning;
};
