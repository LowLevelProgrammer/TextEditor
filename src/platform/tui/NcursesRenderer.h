#pragma once

#ifdef __linux__

#include "IRenderer.h"
#include <ncurses.h>

class NcursesRenderContext : public RenderContext {
public:
  NcursesRenderContext(int height, int width, int y, int x) {
    window = newwin(height, width, y, x);
  }

  ~NcursesRenderContext() { delwin(window); }

  WINDOW *window;
};

class NcursesRenderer : public IRenderer {
public:
  NcursesRenderer();
  ~NcursesRenderer();

  void DrawText(RenderContext *context, int x, int y,
                const std::string &text) override;
  void DrawBox(RenderContext *context, int x, int y, int width,
               int height) override;
  void Clear(RenderContext *context) override;
  void Refresh(RenderContext *context) override;
  void MoveCaret(RenderContext *context, int x, int y) override;

private:
  void DisableFlowControl();
};

#endif
