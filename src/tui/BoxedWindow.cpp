#include "BoxedWindow.h"

#include "Window.h"
#include <ncurses.h>
#include <sstream>
#include <string>
#include <vector>

BoxedWindow::BoxedWindow(int h, int w, int y, int x) : Window(h, w, y, x) {}

BoxedWindow::~BoxedWindow() {}

std::vector<std::string> SplitString(std::string str){
  std::vector<std::string> lines;
  std::string line;

  std::stringstream ss(str);

  while (std::getline(ss, line, '\n')) {
    lines.push_back(line);
  }
  return lines;
}

void BoxedWindow::Draw(const std::string &content) {
  box(m_Win, 0, 0);

  int maxWidth = m_Width - 2;
  std::vector<std::string> lines = SplitString(content);

  int y = 1;
  
  for (int i = 0; i < lines.size(); i++) {

    int lineSize = lines[i].size();

    for(int l = 0; l < lines[i].size(); l += maxWidth){
      std::string str = lines[i].substr(l, maxWidth);
      mvwprintw(m_Win, y++, 1, "%s", str.c_str());
    }
  }
}
