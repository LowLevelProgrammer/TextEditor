#include "RenderManager.h"
#include "TextBuffer.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <ncurses.h>
#include <termios.h>
#include <unistd.h>

RenderManager::RenderManager() {}

RenderManager::~RenderManager() { Shutdown(); }

void RenderManager::Initialize() {
  initscr();
  start_color();
  cbreak();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  // nodelay(stdscr, TRUE);
  DisableFlowControl();
}

void RenderManager::Render(const std::vector<Pane *> &panes, Pane *activePane,
                           Position caretPosition) {
  for (auto &pane : panes) {
    pane->Render();
  }

  auto [y, x] = caretPosition;

  wmove(activePane->GetWindow(), y, x);
}

void RenderManager::Shutdown() { endwin(); }

void RenderManager::DisableFlowControl() {
  struct termios tty;
  tcgetattr(STDIN_FILENO, &tty);

  tty.c_iflag &= ~(IXON | IXOFF); // Disable XON/XOFF flow control

  tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}
