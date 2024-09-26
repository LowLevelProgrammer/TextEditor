#pragma once

#ifdef __linux__

#include "Editor.h"
#include "NcursesPane.h"
#include "TextBuffer.h"

class EditorNcursesPane : public NcursesPane {
public:
  EditorNcursesPane(Editor &editor, int height, int width, int y, int x);
  ~EditorNcursesPane();

  void Render(IRenderer *renderer) override;
  void OnEvent(Event &event) override;
  Position GetCaretPosition() const override;

private:
  Editor &m_Editor;
  Position m_CaretPosition;
};

#endif
