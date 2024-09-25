#include "NcursesPane.h"
#include "NcursesRenderer.h"

#include <ncurses.h>

NcursesPane::NcursesPane(int height, int width, int y, int x)
    : IPane(height, width, y, x) {
  m_Context = new NcursesRenderContext(height, width, y, x);
}

NcursesPane::~NcursesPane() {}
