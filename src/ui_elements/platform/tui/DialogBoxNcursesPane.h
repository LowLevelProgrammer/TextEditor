#pragma once

#ifdef __linux__

#include "Event.h"
#include "IPane.h"
#include "NcursesPane.h"
#include "TextBuffer.h"
#include <string>

class DialogBoxNcursesPane : public NcursesPane {
public:
  DialogBoxNcursesPane();
  DialogBoxNcursesPane(int height, int width, int y, int x);
  ~DialogBoxNcursesPane();

  void Render(IRenderer *renderer) override;
  Position GetCaretPosition() const override;
  void OnEvent(Event &event) override;

private:
  std::string m_Text;
  Position m_CaretPosition;
};

#endif
