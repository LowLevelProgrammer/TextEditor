#include "TextController.h"
#include "Transaction.h"
#include <cassert>

TextController::TextController() {}
TextController::~TextController() {}

void TextController::Execute(Transaction *transaction) {
  transaction->Execute();
  m_RedoStack.clear();
  m_UndoStack.push_back(transaction);
}

void TextController::Undo() {
  if (m_UndoStack.empty())
    return;

  Transaction *lastTransaction = m_UndoStack.back();
  m_UndoStack.pop_back();
  lastTransaction->Undo();
  m_RedoStack.push_back(lastTransaction);
}

void TextController::Redo() {
  if (m_RedoStack.empty())
    return;

  Transaction *lastTransaction = m_RedoStack.back();
  m_RedoStack.pop_back();
  lastTransaction->Redo();
  m_UndoStack.push_back(lastTransaction);
}

bool TextController::CanUndo() const { return !m_UndoStack.empty(); }

TransactionType TextController::GetRecentTransactionType() const {
  assert(!m_UndoStack.empty());
  return m_UndoStack.back()->GetTransactionType();
}
