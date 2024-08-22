#pragma once

#include "Command.h"
#include "TextBuffer.h"

class InsertChar : public Command {
public:
  InsertChar(TextBuffer &textBuffer, char data, Offset offset);

  std::string TransactionDetails();
  void Execute() override;
  void Undo() override;
  void Redo() override;

protected:
  TextBuffer &m_TextBuffer;
  char m_Character;
  Offset m_Offset;
};
