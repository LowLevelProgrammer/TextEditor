#include "EditorPane.h"

#include "Editor.h"
#include <ncurses.h>
#include <string>
#include <vector>

EditorPane::EditorPane(Editor &editor, int height, int width, int y, int x)
    : Pane(height, width, y, x), m_Editor(editor) {}

EditorPane::~EditorPane() {}

void EditorPane::Render() {
  werase(m_Window);

  box(m_Window, 0, 0);

  const std::vector<std::string> &lines = m_Editor.GetTextBuffer();
  for (size_t i = 0; i < lines.size(); i++) {
    mvwprintw(m_Window, i + 1, 1, "%s", lines[i].c_str());
  }
  const Position &caretPostion = m_Editor.GetCaretPosition();
  wmove(m_Window, caretPostion.Line, caretPostion.Column);

  wrefresh(m_Window);
}
