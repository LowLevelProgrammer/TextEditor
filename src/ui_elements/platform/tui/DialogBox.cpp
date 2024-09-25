#include "DialogBox.h"

#include "Event.h"
#include "KeyboardEvent.h"
#include "TextBuffer.h"
#include <ncurses.h>

static int height = 10;
static int width = 38;

DialogBox::DialogBox()
    : NcursesPane(height, width, LINES / 2 - height / 2, COLS / 2 - width / 2) {
  m_CaretPosition = {4, 3};
}

DialogBox::DialogBox(int height, int width, int y, int x)
    : NcursesPane(height, width, y, x) {}

DialogBox::~DialogBox() {}

void DialogBox::Render(IRenderer *renderer) {
  // werase(m_Window);
  //
  // box(m_Window, 0, 0);
  // mvwprintw(m_Window, 2, 2, "Enter the file path to open:");
  // auto [y, x] = m_CaretPosition;
  // mvwprintw(m_Window, 4, 3, "%s", m_Text.c_str());
  //
  // wrefresh(m_Window);
}

Position DialogBox::GetCaretPosition() const { return m_CaretPosition; }

void DialogBox::OnEvent(Event &event) {
  if (event.GetType() == EventType::KeyPressed) {
    KeyEvent &keyEvent = static_cast<KeyEvent &>(event);
    int key = keyEvent.GetKey();

    switch (key) {
    case KEY_BACKSPACE:
      m_Text.pop_back();
      m_CaretPosition.Column -= 1;
      event.handled = true;
      break;
    default:
      m_Text.push_back(key);
      m_CaretPosition.Column += 1;
      event.handled = true;
      break;
    }
  }
}
