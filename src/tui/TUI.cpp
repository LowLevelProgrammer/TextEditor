#include "TUI.h"

#include <ncurses.h>
#include <string>
#include <vector>

TUI::TUI(Editor &editor) : m_Editor(editor), m_QuitFlag(false) {}

TUI::~TUI() { endwin(); }

void TUI::Init() {
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
}
void TUI::ProcessInput() {
  int ch = getch();
  HandleKeyPress(ch);
}
void TUI::Render() {
  const std::vector<std::string> &textBuffer = m_Editor.GetTextBuffer();

  clear();
  for (int i = 0; i < textBuffer.size(); i++) {
    mvprintw(i, 0, "%s", textBuffer[i].c_str());
  }
  auto [y, x] = m_Editor.GetCaretPosition();
  move(y - 1, x - 1);
}

void TUI::HandleKeyPress(int key) {
  switch (key) {
  case 27:
    m_QuitFlag = true;
    break;
  case KEY_BACKSPACE:
  case 127:
  case 8:
    m_Editor.BackSpace();
    break;
  case KEY_UP:
    m_Editor.MoveCaret(Direction::Up);
    break;
  case KEY_DOWN:
    m_Editor.MoveCaret(Direction::Down);
    break;
  case KEY_LEFT:
    m_Editor.MoveCaret(Direction::Left);
    break;
  case KEY_RIGHT:
    m_Editor.MoveCaret(Direction::Right);
    break;
  default:
    m_Editor.InsertChar(key);
    break;
  }
}
