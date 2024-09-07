#pragma once

#include "Command.h"
#include "TextBuffer.h"

class InsertChar : public Command {
public:
  InsertChar(TextBuffer &textBuffer, char data, Offset offset);

  std::string TransactionDetails() override;
  void Execute() override;
  void Undo() override;
  void Redo() override;

  inline const char GetCommandCharacter() const override { return m_Character; }

protected:
  TextBuffer &m_TextBuffer;
  char m_Character;
  Offset m_Offset;
};
