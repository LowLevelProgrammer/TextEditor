#pragma once

#include "Pane.h"
#include <vector>
class PaneManager {
public:
  PaneManager();
  ~PaneManager();

  void AddPane(Pane *pane);
  void RemovePane(Pane *pane);

  void SetActivePane(Pane *pane) { m_ActivePane = pane; }

  const Pane *GetActivePane() const { return m_ActivePane; }
  const std::vector<Pane *> &GetPanes() const { return m_Panes; }

private:
  std::vector<Pane *> m_Panes;
  Pane *m_ActivePane;
};
