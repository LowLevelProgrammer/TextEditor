#pragma once

#include "Editor.h"
class TUI {
public:
  TUI(Editor &editor);
  ~TUI();

  void Init();
  void ProcessInput();
  void Clear();
  void Draw();
  void Refresh();
  bool ShouldQuit() { return m_QuitFlag; }
  void CleanUp();

private:
  Editor &m_Editor;
  bool m_QuitFlag;

private:
  void HandleKeyPress(int key);
  void DisableFlowControl();
};
