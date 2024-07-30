#include "Window.h"
#include <ncurses.h>

Window::Window(int h, int w, int y, int x) : m_Height(h), m_Width(w), m_StartY(y), m_StartX(x) {
  m_Win = newwin(m_Height, m_Width, m_StartY, m_StartX);
  keypad(m_Win, TRUE);
}

Window::~Window() {}

void Window::Clear() {
  wclear(m_Win);
}

void Window::DrawLine(const std::string &content, int y) {
  mvwprintw(m_Win, y, 0, "%s", content.c_str());
}

void Window::Draw(const std::string &content) {
  mvwprintw(m_Win, 1, 1, "%s", content.c_str());
}

void Window::Refresh() { wrefresh(m_Win); }
