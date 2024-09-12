#pragma once

#include <vector>
enum class EventType { None = 0, KeyPressed };

class Event {
public:
  virtual ~Event() = default;

  virtual EventType GetType() const = 0;
};

class EventListener {
public:
  virtual ~EventListener() = default;

  virtual void OnEvent(Event &event) = 0;
};

class EventDispatcher {
public:
  void RegisterListener(EventListener *listener) {
    m_Listener.push_back(listener);
  }

  void Dispatch(Event &event) {
    for (auto *listener : m_Listener) {
      listener->OnEvent(event);
    }
  }

private:
  std::vector<EventListener *> m_Listener;
};
