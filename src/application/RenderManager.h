#pragma once

#include "Pane.h"
#include <vector>

class RenderManager {
public:
  RenderManager();
  ~RenderManager();

  void Initialize();
  void Render(const std::vector<Pane *> &panes, const Pane *activePane);
  void Shutdown();

private:
  void DisableFlowControl();
};
