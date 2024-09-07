#pragma once

#include "Command.h"
#include "TextBuffer.h"

class EraseNewline : public Command {
public:
  EraseNewline(TextBuffer &textBuffer, Offset offset);

  std::string TransactionDetails() override;
  void Execute() override;
  void Undo() override;
  void Redo() override;

  inline const char GetCommandCharacter() const override { return '\n'; }

private:
  TextBuffer &m_TextBuffer;
  Offset m_Offset;
};
