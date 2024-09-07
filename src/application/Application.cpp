#include "Application.h"

#include "BoxedWindow.h"
#include "MainWindow.h"
#include "utilities.h"

Application::Application() : m_IsRunning(true) {
  m_TUI.Init();
  m_MainWindow = new MainWindow(m_Editor);

  int rows, cols;
  getmaxyx(stdscr, rows, cols);

  m_SecondaryWindow = new BoxedWindow(rows, cols / 2, 0, cols / 2);
}

Application::~Application() { m_TUI.CleanUp(); }

void Application::ProcessInput() { m_MainWindow->ProcessInput(); }

void Application::Clear() {
  m_MainWindow->Clear();
  // m_SecondaryWindow->Clear();
}

void Application::Draw() {
  // m_SecondaryWindow->Draw(GetUndoStackString(m_Editor.GetUndoStack()));
  m_MainWindow->Draw();
}

void Application::Refresh() {
  // m_SecondaryWindow->Refresh();
  m_MainWindow->Refresh();
  // m_MainWindow->RefreshCursor();
}

void Application::Run() {

  while (m_IsRunning) {
    ProcessInput();
    Clear();
    Draw();
    Refresh();

    if (m_MainWindow->ShouldQuit()) {
      m_IsRunning = false;
    }
  }
}
