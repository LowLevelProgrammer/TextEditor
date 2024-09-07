#pragma once

#include "Editor.h"
#include "Window.h"
class MainWindow {
public:
  MainWindow(Editor &editor);
  ~MainWindow();

  void ProcessInput();
  void Clear();
  void Draw();
  void Refresh();
  void RefreshCursor();
  bool ShouldQuit() { return m_QuitFlag; }

private:
  Editor &m_Editor;
  bool m_QuitFlag;
  Window *m_Window;

private:
  void HandleKeyPress(int key);
};
