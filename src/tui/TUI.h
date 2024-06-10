#pragma once

#include "Editor.h"
class TUI {
public:
  TUI(Editor &editor);
  ~TUI();

  void Init();
  void ProcessInput();
  void Render();
  bool ShouldQuit() { return m_QuitFlag; }
  void CleanUp();

private:
  Editor &m_Editor;
  bool m_QuitFlag;

private:
  void HandleKeyPress(int key);
};
