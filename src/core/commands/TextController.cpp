#include "TextController.h"
#include "Command.h"
#include <cassert>

TextController::TextController() {}
TextController::~TextController() {}

void TextController::Execute(Command *transaction) {
  transaction->Execute();
  m_RedoStack.clear();
  m_UndoStack.push_back(transaction);
}

void TextController::Undo() {
  if (m_UndoStack.empty())
    return;

  Command *commandPtr = m_UndoStack.back();

  while (!m_UndoStack.empty() && commandPtr != nullptr) {
    commandPtr->Undo();
    m_UndoStack.pop_back();
    commandPtr = m_UndoStack.back();
  }
  if (!m_UndoStack.empty())
    // Remove the boundary "nullptr"
    m_UndoStack.pop_back();
}

void TextController::Redo() {}

bool TextController::ShouldAddCheckpoint() {
  if (!m_UndoStack.empty() &&
      (GetRecentCommandType() == CommandType::EraseChar ||
       GetRecentCommandType() == CommandType::EraseNewline)) {
    return true;
  }
  return false;
}

void TextController::AddCheckpoint() { m_UndoStack.push_back(nullptr); }

bool TextController::CanUndo() const { return !m_UndoStack.empty(); }

CommandType TextController::GetRecentCommandType() const {
  assert(!m_UndoStack.empty());
  return m_UndoStack.back()->GetCommandType();
}
