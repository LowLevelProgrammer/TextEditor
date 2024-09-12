#pragma once

#include <ncurses.h>

class Pane {
public:
  Pane(int height, int width, int y, int x);
  ~Pane();

  virtual void Render() = 0;

  WINDOW *GetWindow() const { return m_Window; }

protected:
  WINDOW *m_Window;
  int m_Height, m_Width;
  int m_StartY, m_StartX;
};
