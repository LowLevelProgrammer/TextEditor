#include "BoxedWindow.h"
#include "Window.h"
#include <ncurses.h>

BoxedWindow::BoxedWindow(int h, int w, int y, int x) : Window(h, w, y, x) {}

BoxedWindow::~BoxedWindow() {}

void BoxedWindow::Draw(const std::string &content) {
  box(GetWin(), 0, 0);
  mvwprintw(GetWin(), 1, 1, "%s", content.c_str());
}
