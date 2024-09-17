#include "Application.h"

#include "EditorPane.h"
#include "InfoPane.h"
#include "KeyboardEvent.h"

#define KEY_ESCAPE 27

Application::Application()
    : m_IsRunning(true), m_InputManager(&m_EventDispatcher) {}

Application::~Application() {}

void Application::Initialize() {
  m_RenderManager.Initialize();

  m_EventDispatcher.RegisterListener(this);
  m_EventDispatcher.RegisterListener(&m_Editor);

  Pane *editorPane = new EditorPane(m_Editor, LINES - 3, COLS, 0, 0);
  m_PaneManager.AddPane(editorPane);
  m_PaneManager.SetActivePane(editorPane);

  Pane *infoPane = new InfoPane(m_Editor, 3, COLS, LINES - 3, 0);
  m_PaneManager.AddPane(infoPane);
}

void Application::Run() {
  while (m_IsRunning) {
    m_RenderManager.Render(m_PaneManager.GetPanes(),
                           m_PaneManager.GetActivePane(),
                           m_Editor.GetCaretPosition());

    PollEvents();
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

void Application::PollEvents() {
  m_InputManager.GetInput(m_PaneManager.GetActivePane()->GetWindow());
}
