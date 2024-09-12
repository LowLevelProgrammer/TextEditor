#include "Pane.h"
#include <ncurses.h>

Pane::Pane(int height, int width, int y, int x)
    : m_Height(height), m_Width(width), m_StartY(y), m_StartX(x) {
  m_Window = newwin(m_Height, m_Width, m_StartY, m_StartX);
  keypad(m_Window, true);
}

Pane::~Pane() { delwin(m_Window); }
