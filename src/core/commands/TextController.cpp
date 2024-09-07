#include "TextController.h"
#include "Command.h"
#include "custom_assert.h"
#include <cassert>

TextController::TextController() {}
TextController::~TextController() {}

void TextController::Execute(Command *command) {
  command->Execute();
  m_RedoStack.clear();
  m_UndoStack.push_back(command);
}

void TextController::Undo() {

  // Will activate only if two undo commands are issued consecutively
  if (!m_UndoStack.empty() && m_UndoStack.back() == nullptr) {
    m_UndoStack.pop_back();
  }

  // Will undo till a breakpoint char like space or newline is found
  while (!m_UndoStack.empty() && m_UndoStack.back() != nullptr) {
    Command *cmd = m_UndoStack.back();
    m_UndoStack.pop_back();

    cmd->Undo();
  }
}

void TextController::Redo() {}

bool TextController::ShouldAddCheckpoint() {
  // Check for if the last element in the undostack is a breakpoint i.e. nullptr
  // Otherwise the program will crash when inserting a letter after issuing undo
  // in the following check at GetRecentCommandType function
  // Also for this case no need to add a breakpoint
  if (!m_UndoStack.empty() && m_UndoStack.back() == nullptr) {
    return false;
  }

  // Check if the char before inserting a letter is either space or newline
  if (!m_UndoStack.empty() &&
      (GetRecentCommandType() == CommandType::EraseChar ||
       GetRecentCommandType() == CommandType::EraseNewline)) {
    return true;
  }
  return false;
}

void TextController::AddCheckpoint() {
  // This check avoids double consecutive checkpoint for the case when a
  // breakpoint char is added after an undo command
  if (!m_UndoStack.empty() && m_UndoStack.back() != nullptr)
    m_UndoStack.push_back(nullptr);
}

bool TextController::CanUndo() const { return !m_UndoStack.empty(); }

CommandType TextController::GetRecentCommandType() const {
  assert(!m_UndoStack.empty());
  return m_UndoStack.back()->GetCommandType();
}

std::size_t TextController::GetUndoStackSize() const {
  ASSERT_NOT_EMPTY(m_UndoStack);
  return m_UndoStack.size();
}

bool TextController::IsUndoStackEmpty() const { return m_UndoStack.empty(); }
