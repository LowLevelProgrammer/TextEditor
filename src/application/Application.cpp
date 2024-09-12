#include "Application.h"

#include "Event.h"
#include "KeyboardEvent.h"
#include <ncurses.h>

#define KEY_ESCAPE 27

Application::Application()
    : m_IsRunning(true), m_InputManager(&m_EventDispatcher) {}

Application::~Application() {}

void Application::Initialize() {
  m_RenderManager.Initialize();

  m_EventDispatcher.RegisterListener(this);
  m_EventDispatcher.RegisterListener(&m_Editor);
}

void Application::Run() {
  while (m_IsRunning) {
    m_InputManager.GetInput();

    Render();
  }
}

void Application::Shutdown() {}

void Application::OnEvent(Event &event) {
  if (event.GetType() == EventType::KeyPressed) {
    KeyEvent &keyEvent = static_cast<KeyEvent &>(event);
    int key = keyEvent.GetKey();

    if (key == KEY_ESCAPE) {
      m_IsRunning = false;
    }
  }
}

void Application::Render() {
  m_RenderManager.Render(m_Editor.GetTextBuffer(), m_Editor.GetCaretPosition());
}
