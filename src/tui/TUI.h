#pragma once

#include "Editor.h"
class TUI {
public:
  TUI(Editor &editor);
  ~TUI();

  void Init();
  void ProcessInput();
  void Update();
  void Render();
  bool ShouldQuit() { return m_QuitFlag; }

private:
  Editor &m_Editor;
  bool m_QuitFlag;

private:
  void HandleKeyPress(int key);
};
