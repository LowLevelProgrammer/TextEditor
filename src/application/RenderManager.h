#pragma once

#include "TextBuffer.h"
#include <string>
#include <vector>
class RenderManager {
public:
  RenderManager();
  ~RenderManager();

  void Initialize();
  void Render(const std::vector<std::string> &textBuffer,
              const Position &caretPosition);
  void Shutdown();

private:
  void RenderTextBuffer(const std::vector<std::string> &textBuffer);
  void RenderCaret(const Position &caretPosition);

  void DisableFlowControl();
};
