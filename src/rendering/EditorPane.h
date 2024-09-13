#pragma once

#include "Editor.h"
#include "Pane.h"

class EditorPane : public Pane {
public:
  EditorPane(Editor &editor, int height, int width, int y, int x);
  ~EditorPane();

  void Render(bool isActive) override;

private:
  Editor &m_Editor;
};
