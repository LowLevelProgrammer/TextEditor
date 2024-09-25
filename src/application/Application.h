#pragma once

#include "Editor.h"
#include "Event.h"
#include "IWindow.h"

class Application : public EventListener {
public:
  Application();
  ~Application();

  void Initialize();
  void Run();
  void Shutdown();

private:
  void PollEvents();
  void OnEvent(Event &event) override;

private:
  Editor m_Editor;
  IRenderer *m_Renderer;
  IWindow *m_Window;
  EventDispatcher m_EventDispatcher;
  IPane *m_EditorPane;

  bool m_IsRunning;
};
