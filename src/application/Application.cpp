#include "Application.h"
#include <ncurses.h>

Application::Application() : m_TUI(m_Editor), m_IsRunning(true) {}

Application::~Application() {}

void Application::ProcessInput() { m_TUI.ProcessInput(); }

void Application::Clear() { m_TUI.Clear(); }

void Application::Draw() {
  // Window content
  wclear(win);
  box(win, 0, 0);
  mvwprintw(win, 1, 1, "%s", "Updated content");

  m_TUI.Draw();
}

void Application::Refresh() {
  m_TUI.Refresh();
  wrefresh(win);
  m_TUI.RefreshCursor();
}

void Application::Run() {
  m_TUI.Init();

  int rows, cols;
  getmaxyx(stdscr, rows, cols);
  win = newwin(rows, cols / 2, 0, cols / 2);
  wclear(win);
  box(win, 0, 0);
  mvwprintw(win, 1, 1, "%s", "Right Half window");
  wrefresh(win);

  while (m_IsRunning) {
    ProcessInput();
    Clear();
    Draw();
    Refresh();

    if (m_TUI.ShouldQuit()) {
      m_IsRunning = false;
    }
  }

  m_TUI.CleanUp();
}
