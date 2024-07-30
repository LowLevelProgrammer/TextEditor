#pragma once

#include <ncurses.h>
#include <string>
class Window {
public:
  Window(int h, int w, int y, int x);
  virtual ~Window();

  void Clear();
  void DrawLine(const std::string &content, int y);
  virtual void Draw(const std::string &content);
  virtual void Refresh();

  inline WINDOW *GetWin() { return m_Win; }

private:
  WINDOW *m_Win;
  int m_Height, m_Width, m_StartY, m_StartX;
};
