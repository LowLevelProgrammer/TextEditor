#pragma once

#include "TextBuffer.h"
#include "Transaction.h"

class InsertNewline : public Transaction {
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
