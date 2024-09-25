#pragma once

#include <string>

class RenderContext {
public:
  virtual ~RenderContext() = default;
};

class IRenderer {
public:
  virtual ~IRenderer() = default;

  virtual void DrawText(RenderContext *context, int x, int y,
                        const std::string &text) = 0;
  virtual void DrawBox(RenderContext *context, int x, int y, int width,
                       int height) = 0;
  virtual void Clear(RenderContext *context) = 0;
  virtual void Refresh(RenderContext *context) = 0;
  virtual void MoveCaret(RenderContext *context, int x, int y) = 0;
};
