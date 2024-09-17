#pragma once

#include "Editor.h"
#include "Pane.h"

class InfoPane : public Pane {
public:
  InfoPane(Editor &editor, int height, int width, int y, int x);
  ~InfoPane();

  void Render() override;

private:
  Editor &m_Editor;
};
