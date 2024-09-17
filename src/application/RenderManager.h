#pragma once

#include "Pane.h"
#include <vector>

class Position;

class RenderManager {
public:
  RenderManager();
  ~RenderManager();

  void Initialize();
  void Render(const std::vector<Pane *> &panes, Pane *activePane,
              Position caretPosition);
  void Shutdown();

private:
  void DisableFlowControl();
};
