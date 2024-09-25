#pragma once

#include "IPane.h"
class IRenderer;

class IWindow {
public:
  virtual ~IWindow() = default;

  virtual void AddPane(IPane *pane) = 0;
  virtual void RemovePane(IPane *pane) = 0;
  virtual void Render(IRenderer *renderer) = 0;
  virtual int ReceiveInput() = 0;
  virtual void SetFocus(IPane *pane) = 0;
  virtual void Shutdown() = 0;

  virtual int GetWidth() const = 0;
  virtual int GetHeight() const = 0;
};
