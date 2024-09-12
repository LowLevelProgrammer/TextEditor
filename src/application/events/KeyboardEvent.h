#pragma once

#include "Event.h"

class KeyEvent : public Event {
public:
  explicit KeyEvent(int key) : m_Key(key) {}

  EventType GetType() const override { return EventType::KeyPressed; }

  int GetKey() const { return m_Key; }

private:
  int m_Key;
};
