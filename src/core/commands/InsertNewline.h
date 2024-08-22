#pragma once

#include "Command.h"
#include "TextBuffer.h"

class InsertNewline : public Command {
public:
  InsertNewline(TextBuffer &textBuffer, Offset offset);

  std::string TransactionDetails();
  void Execute() override;
  void Undo() override;
  void Redo() override;

private:
  TextBuffer &m_TextBuffer;
  Offset m_Offset;
};
