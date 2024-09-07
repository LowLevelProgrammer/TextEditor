#pragma once

#include "Command.h"
#include "TextBuffer.h"

class EraseChar : public Command {
public:
  EraseChar(TextBuffer &textBuffer, Offset offset);

  std::string TransactionDetails() override;
  void Execute() override;
  void Undo() override;
  void Redo() override;

  inline const char GetCommandCharacter() const override {
    return m_RemovedChar;
  }

protected:
  TextBuffer &m_TextBuffer;
  char m_RemovedChar;
  Offset m_Offset;
};
