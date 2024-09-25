#include "InfoNcursesPane.h"

#include <ncurses.h>
#include <sstream>

InfoNcursesPane ::InfoNcursesPane(Editor &editor, int height, int width, int y,
                                  int x)
    : NcursesPane(height, width, y, x), m_Editor(editor) {}

InfoNcursesPane ::~InfoNcursesPane() {}

void InfoNcursesPane::Render(IRenderer *renderer) {

  renderer->Clear(m_Context);

  renderer->DrawBox(m_Context, 0, 0, m_Width, m_Height);
  auto [y, x] = m_Editor.GetCaretPosition();
  int startX = COLS * 3 / 4;
  std::stringstream ss;
  ss << "Line " << y << ", Column " << x;
  renderer->DrawText(m_Context, startX, 1, ss.str());

  renderer->Refresh(m_Context);
}

void InfoNcursesPane::OnEvent(Event &event) {}

Position InfoNcursesPane::GetCaretPosition() const { return {-1, -1}; }
