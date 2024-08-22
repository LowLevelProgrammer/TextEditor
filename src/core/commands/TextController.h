#pragma once

#include "Command.h"
#include <vector>

class TextController {
public:
  TextController();
  ~TextController();

  void Execute(Command *transaction);
  void Undo();
  void Redo();

  bool CanUndo() const;
  CommandType GetRecentTransactionType() const;

private:
  std::vector<Command *> m_UndoStack;
  std::vector<Command *> m_RedoStack;
};
