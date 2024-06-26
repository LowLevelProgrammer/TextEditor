#include "TUI.h"

#include <cctype>
#include <csignal>
#include <cstdlib>
#include <ncurses.h>
#include <string>
#include <vector>

#define ctrl(x) (x & 0x1F)

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

std::string GetStringInput(int startY, int startX) {
  std::string input;
  int ch;
  move(startY, startX);

  while ((ch = getch()) != '\n') {
    switch (ch) {
    case KEY_BACKSPACE:
    case 127:
      if (!input.empty()) {
        input.pop_back();
        int y, x;
        getyx(stdscr, y, x);
        mvwdelch(stdscr, y, x - 1);
      }
      break;
    default:
      if (isprint(ch)) {
        input.push_back(ch);
        addch(ch);
      }
      break;
    }
    refresh();
  }
  return input;
}

void TUI::HandleKeyPress(int key) {
  switch (key) {
  case ctrl('c'):
  case 27:
    m_QuitFlag = true;
    break;
  case ctrl('r'): {
    if (!m_Editor.IsFileOpen()) {
      int x, y;
      getmaxyx(stdscr, y, x);
      mvprintw(y - 1, 0, "Enter filename to save: ");
      std::string fileName = GetStringInput(y - 1, 23);
      m_Editor.SaveAs(fileName);
    }
    m_Editor.SaveAs(m_Editor.GetFilePath());
  } break;
  case ctrl('s'): {
    int x, y;
    getmaxyx(stdscr, y, x);
    mvprintw(y - 1, 0, "Enter filename to save: ");
    std::string fileName = GetStringInput(y - 1, 23);
    m_Editor.SaveAs(fileName);
  } break;
  case ctrl('o'): {
    int x, y;
    getmaxyx(stdscr, y, x);
    mvprintw(y - 1, 0, "Enter the file to open: ");
    std::string fileName = GetStringInput(y - 1, 24);
    m_Editor.OpenFile(fileName);
  } break;
  case ctrl('z'):
    m_Editor.Undo();
    break;
  case ctrl('y'):
    m_Editor.Redo();
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

void TUI::CleanUp() { endwin(); }
