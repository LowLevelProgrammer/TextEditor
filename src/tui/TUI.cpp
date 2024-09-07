#include "TUI.h"

#include <ncurses.h>
#include <termios.h>
#include <unistd.h>

void TUI::Init() {
  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  noecho();
  DisableFlowControl();
}

void TUI::DisableFlowControl() {
  struct termios tty;
  tcgetattr(STDIN_FILENO, &tty);

  tty.c_iflag &= ~(IXON | IXOFF); // Disable XON/XOFF flow control

  tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void TUI::CleanUp() { endwin(); }
