#pragma once

#include "Command.h"
#include "TextBuffer.h"

class EraseNewline : public Command {
public:
  EraseNewline(TextBuffer &textBuffer, Offset offset);
  ~EraseNewline();

  std::string TransactionDetails();
  void Execute() override;
  void Undo() override;
  void Redo() override;

private:
  TextBuffer &m_TextBuffer;
  Offset m_Offset;
};
