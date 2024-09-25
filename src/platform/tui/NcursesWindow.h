#pragma once

#include "Event.h"
#include "IPane.h"
#include "IWindow.h"
#include <ncurses.h>
#include <vector>

class NcursesWindow : public IWindow {
public:
  NcursesWindow();
  ~NcursesWindow();

  void AddPane(IPane *pane) override;
  void RemovePane(IPane *pane) override;
  void Render(IRenderer *renderer) override;
  int ReceiveInput() override;
  void SetFocus(IPane *pane) override;
  void Shutdown() override;

  int GetWidth() const override { return m_Width; }
  int GetHeight() const override { return m_Height; }

private:
  std::vector<IPane *> m_Panes;
  IPane *m_FocusedPane;
  int m_Height, m_Width;
};
