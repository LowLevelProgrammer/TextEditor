#pragma once

#include "Event.h"
#include "IRenderer.h"

class Position;

class IPane : public EventListener {
public:
  IPane(int height, int width, int y, int x)
      : m_Height(height), m_Width(width), m_StartY(y), m_StartX(x) {}
  virtual ~IPane() = default;

  virtual void Render(IRenderer *renderer) = 0;
  virtual void OnEvent(Event &event) = 0;

  virtual int GetWidth() const { return m_Width; }
  virtual int GetHeight() const { return m_Height; }
  virtual int GetStartX() const { return m_StartX; }
  virtual int GetStartY() const { return m_StartY; }
  virtual Position GetCaretPosition() const = 0;
  RenderContext *GetContext() const { return m_Context; }

protected:
  int m_Height, m_Width;
  int m_StartY, m_StartX;
  RenderContext *m_Context;
};
