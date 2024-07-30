#include "Application.h"
#include "BoxedWindow.h"

Application::Application() : m_MainWindow(m_Editor), m_IsRunning(true) {
  m_MainWindow.Init();

  int rows, cols;
  getmaxyx(stdscr, rows, cols);

  m_SecondaryWindow = new BoxedWindow(rows, cols / 2, 0, cols / 2);
}

Application::~Application() {}

void Application::ProcessInput() { m_MainWindow.ProcessInput(); }

void Application::Clear() {
  m_MainWindow.Clear();
  m_SecondaryWindow->Clear();
}

void Application::Draw() {
  m_MainWindow.Draw();
  m_SecondaryWindow->Draw("Secondary window content");
}

void Application::Refresh() {
  m_SecondaryWindow->Refresh();
  m_MainWindow.Refresh();
  m_MainWindow.RefreshCursor();
}

void Application::Run() {

  while (m_IsRunning) {
    ProcessInput();
    Clear();
    Draw();
    Refresh();

    if (m_MainWindow.ShouldQuit()) {
      m_IsRunning = false;
    }
  }

  m_MainWindow.CleanUp();
}
