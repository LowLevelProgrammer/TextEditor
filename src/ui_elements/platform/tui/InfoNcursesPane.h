#pragma once

#ifdef __linux__

#include "Editor.h"
#include "NcursesPane.h"

class InfoNcursesPane : public NcursesPane {
public:
  InfoNcursesPane(Editor &editor, int height, int width, int y, int x);
  ~InfoNcursesPane();

  void Render(IRenderer *renderer) override;
  void OnEvent(Event &event) override;
  Position GetCaretPosition() const override;

private:
  Editor &m_Editor;
};

#endif
