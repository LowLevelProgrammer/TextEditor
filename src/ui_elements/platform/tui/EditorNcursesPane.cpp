#include "EditorNcursesPane.h"

#include "Editor.h"
#include "KeyboardEvent.h"
#include <ncurses.h>
#include <string>
#include <vector>

#define ctrl(x) (x & 0x1F)
#define KEY_ESCAPE 27

EditorNcursesPane::EditorNcursesPane(Editor &editor, int height, int width,
                                     int y, int x)
    : NcursesPane(height, width, y, x), m_Editor(editor) {}

EditorNcursesPane::~EditorNcursesPane() {}

void EditorNcursesPane::Render(IRenderer *renderer) {
  // werase(m_Window);
  //
  // box(m_Window, 0, 0);
  //
  // const std::vector<std::string> &lines = m_Editor.GetTextBuffer();
  // for (size_t i = 0; i < lines.size(); i++) {
  //   mvwprintw(m_Window, i + 1, 1, "%s", lines[i].c_str());
  // }
  // wnoutrefresh(m_Window);

  renderer->Clear(m_Context);

  renderer->DrawBox(m_Context, 0, 0, m_Width, m_Height);

  const std::vector<std::string> &lines = m_Editor.GetTextBuffer();
  for (size_t i = 0; i < lines.size(); i++) {
    renderer->DrawText(m_Context, m_StartX + 1, m_StartY + i + 1, lines[i]);
  }

  renderer->Refresh(m_Context);
}

Position EditorNcursesPane::GetCaretPosition() const {
  return m_Editor.GetCaretPosition();
}

void EditorNcursesPane::OnEvent(Event &event) {

  if (event.GetType() == EventType::KeyPressed) {
    KeyEvent &keyEvent = static_cast<KeyEvent &>(event);
    int key = keyEvent.GetKey();

    if (key == KEY_ESCAPE) {
      event.handled = false;
      return;
    }

    switch (key) {
    case ctrl('u'):
      m_Editor.Undo();
      break;
    case ctrl('r'):
      m_Editor.Redo();
      break;
    case KEY_LEFT:
      m_Editor.MoveCaret(Direction::Left);
      break;
    case KEY_RIGHT:
      m_Editor.MoveCaret(Direction::Right);
      break;
    case KEY_UP:
      m_Editor.MoveCaret(Direction::Up);
      break;
    case KEY_DOWN:
      m_Editor.MoveCaret(Direction::Down);
      break;
    case KEY_BACKSPACE:
    case 127:
      m_Editor.BackSpace();
      break;
    default:
      m_Editor.InsertChar(key);
      break;
    }
    event.handled = true;
  }
}
