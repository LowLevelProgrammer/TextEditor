#pragma once

#include <vector>
enum class EventType { None = 0, KeyPressed };

class Event {
public:
  virtual ~Event() = default;

  virtual EventType GetType() const = 0;

  bool handled = false;
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
    // for (auto *listener : m_Listener) {
    //   listener->OnEvent(event);
    // }

    // Iterate from last listener (top most layer) to the first
    for (auto it = m_Listener.rbegin(); it != m_Listener.rend(); it++) {
      (*it)->OnEvent(event);
      if (event.handled)
        break;
    }
  }

private:
  std::vector<EventListener *> m_Listener;
};
