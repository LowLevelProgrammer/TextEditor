#pragma once

#include "Event.h"
#include "IPane.h"
#include "NcursesPane.h"
#include "TextBuffer.h"
#include <string>

class DialogBox : public NcursesPane {
public:
  DialogBox();
  DialogBox(int height, int width, int y, int x);
  ~DialogBox();

  void Render(IRenderer *renderer) override;
  Position GetCaretPosition() const override;
  void OnEvent(Event &event) override;

private:
  std::string m_Text;
  Position m_CaretPosition;
};
