#pragma once

#include "Editor.h"
#include "Window.h"
class TUI {
public:
  TUI(Editor &editor);
  ~TUI();

  void Init();
  void ProcessInput();
  void Clear();
  void Draw();
  void Refresh();
  void RefreshCursor();
  bool ShouldQuit() { return m_QuitFlag; }
  void CleanUp();

private:
  Editor &m_Editor;
  bool m_QuitFlag;
  Window* m_Window;

private:
  void HandleKeyPress(int key);
  void DisableFlowControl();
};
