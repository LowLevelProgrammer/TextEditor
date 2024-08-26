#pragma once

#include "Command.h"
#include <vector>

class TextController {
public:
  TextController();
  ~TextController();

  void Execute(Command *command);
  void Undo();
  void Redo();
  bool ShouldAddCheckpoint();
  void AddCheckpoint();

  bool CanUndo() const;
  CommandType GetRecentCommandType() const;

private:
  std::vector<Command *> m_UndoStack;
  std::vector<Command *> m_RedoStack;
};
