#pragma once

#include "TextBuffer.h"
#include "Transaction.h"

class EraseNewline : public Transaction {
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
