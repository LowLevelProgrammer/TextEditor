#include "Application.h"

#include "KeyboardEvent.h"

#ifdef __linux__

#include "EditorNcursesPane.h"
#include "InfoNcursesPane.h"
#include "NcursesRenderer.h"
#include "NcursesWindow.h"

#endif

#define KEY_ESCAPE 27
#define ctrl(x) (x & 0x1F)

Application::Application() : m_IsRunning(true) {}

Application::~Application() {}

void Application::Initialize() {
#ifdef __linux__

  m_Renderer = new NcursesRenderer();
  m_Window = new NcursesWindow();

  m_EditorPane = new EditorNcursesPane(m_Editor, m_Window->GetHeight() - 3,
                                       m_Window->GetWidth(), 0, 0);

  IPane *infoPane = new InfoNcursesPane(m_Editor, 3, m_Window->GetWidth(),
                                        m_Window->GetHeight() - 3, 0);

#endif

  m_EventDispatcher.RegisterListener(this);
  m_EventDispatcher.RegisterListener(m_EditorPane);

  m_Window->AddPane(m_EditorPane);
  m_Window->SetFocus(m_EditorPane);

  m_Window->AddPane(infoPane);
}

void Application::Run() {
  while (m_IsRunning) {
    m_Window->Render(m_Renderer);

    PollEvents();
  }
}

void Application::Shutdown() { m_Window->Shutdown(); }

void Application::OnEvent(Event &event) {
  if (event.GetType() == EventType::KeyPressed) {
    KeyEvent &keyEvent = static_cast<KeyEvent &>(event);
    int key = keyEvent.GetKey();

    switch (key) {
    case KEY_ESCAPE:
      m_IsRunning = false;
      break;
    case ctrl('o'):
      break;
    }
  }
}

void Application::PollEvents() {
  int key = m_Window->ReceiveInput();
  KeyEvent event(key);
  m_EventDispatcher.Dispatch(event);
}
