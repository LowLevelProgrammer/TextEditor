#include "Application.h"

Application::Application() : m_TUI(m_Editor), m_IsRunning(true) {}

Application::~Application() {}

void Application::Run() {
  m_TUI.Init();

  while (m_IsRunning) {
    m_TUI.ProcessInput();
    m_TUI.Update();
    m_TUI.Render();

    if (m_TUI.ShouldQuit()) {
      m_IsRunning = false;
    }
  }
}
