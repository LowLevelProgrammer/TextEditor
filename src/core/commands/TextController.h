#pragma once

#include "Transaction.h"
#include <vector>

class TextController {
public:
  TextController();
  ~TextController();

  void Execute(Transaction *transaction);
  void Undo();
  void Redo();

  bool CanUndo() const;
  TransactionType GetRecentTransactionType() const;

private:
  std::vector<Transaction *> m_UndoStack;
  std::vector<Transaction *> m_RedoStack;
};
