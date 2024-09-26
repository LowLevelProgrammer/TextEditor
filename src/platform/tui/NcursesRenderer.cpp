#include "NcursesRenderer.h"

#ifdef __linux__

#include <cassert>
#include <ncurses.h>
#include <termios.h>
#include <unistd.h>

NcursesRenderer::NcursesRenderer() {
  initscr();
  start_color();
  cbreak();
  noecho();
  // nodelay(stdscr, TRUE);
  DisableFlowControl();
}

NcursesRenderer::~NcursesRenderer() {}

void NcursesRenderer::DrawText(RenderContext *context, int x, int y,
                               const std::string &text) {
  NcursesRenderContext *ncContext =
      dynamic_cast<NcursesRenderContext *>(context);
  assert(ncContext != nullptr && ncContext->window != nullptr);

  mvwprintw(ncContext->window, y, x, "%s", text.c_str());
}

void NcursesRenderer::DrawBox(RenderContext *context, int x, int y, int width,
                              int height) {
  NcursesRenderContext *ncContext =
      dynamic_cast<NcursesRenderContext *>(context);
  assert(ncContext != nullptr && ncContext->window != nullptr);
  box(ncContext->window, 0, 0);
}

void NcursesRenderer::Clear(RenderContext *context) {
  NcursesRenderContext *ncContext =
      dynamic_cast<NcursesRenderContext *>(context);
  assert(ncContext != nullptr && ncContext->window != nullptr);
  werase(ncContext->window);
}

void NcursesRenderer::Refresh(RenderContext *context) {
  NcursesRenderContext *ncContext =
      dynamic_cast<NcursesRenderContext *>(context);
  assert(ncContext != nullptr && ncContext->window != nullptr);

  wrefresh(ncContext->window);
}

void NcursesRenderer::MoveCaret(RenderContext *context, int x, int y) {
  NcursesRenderContext *ncContext =
      dynamic_cast<NcursesRenderContext *>(context);
  assert(ncContext != nullptr && ncContext->window != nullptr);

  wmove(ncContext->window, y, x);
}

void NcursesRenderer::DisableFlowControl() {
  struct termios tty;
  tcgetattr(STDIN_FILENO, &tty);

  tty.c_iflag &= ~(IXON | IXOFF); // Disable XON/XOFF flow control

  tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

#endif
