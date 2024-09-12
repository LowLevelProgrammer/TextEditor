#include "PaneManager.h"

#include <algorithm>

PaneManager::PaneManager() {}

PaneManager::~PaneManager() {}

void PaneManager::AddPane(Pane *pane) { m_Panes.push_back(pane); }

void PaneManager::RemovePane(Pane *pane) {
  auto it = std::find(m_Panes.begin(), m_Panes.end(), pane);
  if (it != m_Panes.end()) {
    m_Panes.erase(it);
  }
}
