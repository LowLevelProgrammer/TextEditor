#pragma once

#include "TextBuffer.h"
#include "Transaction.h"
class EraseChar : public Transaction {
public:
  EraseChar(TextBuffer& textBuffer, Offset offset);

  std::string TransactionDetails();
  void Execute() override;
  void Undo() override;
  void Redo() override;

protected:
  TextBuffer& m_TextBuffer;
  char m_RemovedChar;
  Offset m_Offset;
};

