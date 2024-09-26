#include "NcursesWindow.h"

#ifdef __linux__

#include "Globals.h"
#include "NcursesRenderer.h"

#include <algorithm>
#include <cassert>
#include <ncurses.h>

NcursesWindow::NcursesWindow() : m_Width(COLS), m_Height(LINES) {
  keypad(stdscr, TRUE);
}

NcursesWindow::~NcursesWindow() {}

void NcursesWindow::AddPane(IPane *pane) { m_Panes.push_back(pane); }

void NcursesWindow::RemovePane(IPane *pane) {
  auto it = std::find(m_Panes.begin(), m_Panes.end(), pane);

  if (it != m_Panes.end()) {
    m_Panes.erase(it);
  }
}

void NcursesWindow::Render(IRenderer *renderer) {
  for (IPane *pane : m_Panes) {
    pane->Render(renderer);
  }

  auto [y, x] = m_FocusedPane->GetCaretPosition();

  renderer->MoveCaret(m_FocusedPane->GetContext(), x, y);
}

int NcursesWindow::ReceiveInput() {
  NcursesRenderContext *ncContext =
      dynamic_cast<NcursesRenderContext *>(m_FocusedPane->GetContext());

  assert(ncContext != nullptr && ncContext->window != nullptr);

  int key = wgetch(ncContext->window);

  return key;
}

void NcursesWindow::SetFocus(IPane *pane) { m_FocusedPane = pane; }

void NcursesWindow::Shutdown() { endwin(); }

#endif
