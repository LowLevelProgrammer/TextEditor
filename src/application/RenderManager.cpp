#include "RenderManager.h"

#include <ncurses.h>
#include <termios.h>
#include <unistd.h>

RenderManager::RenderManager() {}

RenderManager::~RenderManager() { Shutdown(); }

void RenderManager::Initialize() {
  initscr();
  start_color();
  // cbreak();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  // nodelay(stdscr, TRUE);
  DisableFlowControl();
}

void RenderManager::Render(const std::vector<std::string> &textBuffer,
                           const Position &caretPosition) {
  clear();
  RenderTextBuffer(textBuffer);
  RenderCaret(caretPosition);
  refresh();
}

void RenderManager::Shutdown() { endwin(); }

void RenderManager::RenderTextBuffer(
    const std::vector<std::string> &textBuffer) {
  for (std::size_t i = 0; i < textBuffer.size(); i++) {
    mvprintw(i, 0, "%s", textBuffer[i].c_str());
  }
}

void RenderManager::RenderCaret(const Position &caretPosition) {
  move(caretPosition.Line - 1, caretPosition.Column - 1);
}

void RenderManager::DisableFlowControl() {
  struct termios tty;
  tcgetattr(STDIN_FILENO, &tty);

  tty.c_iflag &= ~(IXON | IXOFF); // Disable XON/XOFF flow control

  tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}
