#pragma once
#include "TextBuffer.h"
#include "Transaction.h"
#include <string>

class InsertChar : public Transaction {
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
