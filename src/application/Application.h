#pragma once

#include "Editor.h"
#include "Event.h"
#include "InputManager.h"
#include "PaneManager.h"
#include "RenderManager.h"

class Application : public EventListener {
public:
  Application();
  ~Application();

  void Initialize();
  void Run();
  void Shutdown();

  void OnEvent(Event &event) override;

private:
  void PollEvents();

private:
  Editor m_Editor;
  RenderManager m_RenderManager;
  EventDispatcher m_EventDispatcher;
  InputManager m_InputManager;
  PaneManager m_PaneManager;

  bool m_IsRunning;
};
