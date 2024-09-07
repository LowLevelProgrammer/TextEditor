#pragma once

#include "Editor.h"
#include "MainWindow.h"
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
  TUI m_TUI;
  Editor m_Editor;
  MainWindow *m_MainWindow;
  Window *m_SecondaryWindow;
  bool m_IsRunning;
};
