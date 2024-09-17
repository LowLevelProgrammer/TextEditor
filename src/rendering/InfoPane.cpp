#include "InfoPane.h"

#include "Pane.h"
#include <ncurses.h>

InfoPane ::InfoPane(Editor &editor, int height, int width, int y, int x)
    : Pane(height, width, y, x), m_Editor(editor) {}

InfoPane ::~InfoPane() {}

void InfoPane::Render() {
  werase(m_Window);

  box(m_Window, 0, 0);
  auto [y, x] = m_Editor.GetCaretPosition();
  int startX = COLS * 3 / 4;
  mvwprintw(m_Window, 1, startX, "Line %d, Column %d", y, x);

  wnoutrefresh(m_Window);
}
