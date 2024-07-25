#include "TUI.h"

#include <ncurses.h>
#include <optional>
#include <string>
#include <termios.h>
#include <unistd.h>

#define ctrl(x) (x & 0x1F)
#define KEY_ESCAPE 27

TUI::TUI(Editor &editor) : m_Editor(editor), m_QuitFlag(false) {}

TUI::~TUI() { endwin(); }

void TUI::Init() {
  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  noecho();
  DisableFlowControl();
}
void TUI::ProcessInput() {
  int ch = getch();
  HandleKeyPress(ch);
}

void TUI::Clear() { clear(); }

void TUI::Draw() {
  const std::vector<std::string> &textBuffer = m_Editor.GetTextBuffer();

  for (int i = 0; i < textBuffer.size(); i++) {
    mvprintw(i, 0, "%s", textBuffer[i].c_str());
  }
  auto [y, x] = m_Editor.GetCaretPosition();
  move(y - 1, x - 1);
}

void TUI::Refresh() { refresh(); }

std::optional<std::string> GetStringInput(int startY, int startX) {
  std::string input;
  int ch;
  move(startY, startX);

  while ((ch = getch()) != '\n') {
    switch (ch) {
    case KEY_ESCAPE:
      return {};
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
  case KEY_ESCAPE:
    m_QuitFlag = true;
    break;
  case ctrl('r'): {
    if (!m_Editor.IsFileOpen()) {
      int x, y;
      getmaxyx(stdscr, y, x);
      mvprintw(y - 1, 0, "Enter filename to save: ");
      std::optional<std::string> fileName = GetStringInput(y - 1, 23);
      if (fileName.has_value())
        m_Editor.SaveAs(fileName.value());
      else
        break;
    }
    m_Editor.SaveAs(m_Editor.GetFilePath());
  } break;
  case ctrl('s'): {
    int x, y;
    getmaxyx(stdscr, y, x);
    mvprintw(y - 1, 0, "Enter filename to save: ");
    std::optional<std::string> fileName = GetStringInput(y - 1, 23);
    if (fileName.has_value())
      m_Editor.SaveAs(fileName.value());
    else
      break;
  } break;
  case ctrl('o'): {
    int x, y;
    getmaxyx(stdscr, y, x);
    mvprintw(y - 1, 0, "Enter the file to open: ");
    std::optional<std::string> fileName = GetStringInput(y - 1, 24);
    if (fileName.has_value())
      m_Editor.OpenFile(fileName.value());
    else
      break;
  } break;
  case ctrl('u'):
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

void TUI::DisableFlowControl() {
  struct termios tty;
  tcgetattr(STDIN_FILENO, &tty);

  tty.c_iflag &= ~(IXON | IXOFF); // Disable XON/XOFF flow control

  tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}
