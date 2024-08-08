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

private:
  std::vector<Transaction *> m_UndoStack;
  std::vector<Transaction *> m_RedoStack;
};
