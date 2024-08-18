#pragma once

enum class TransactionType {
  InsertChar,
  InsertNewline,
  EraseChar,
  EraseNewline
};

class Transaction {
public:
  inline virtual ~Transaction() {}

  virtual void Execute() = 0;
  virtual void Undo() = 0;
  virtual void Redo() = 0;

  inline TransactionType GetTransactionType() const {
    return m_TransactionType;
  }

protected:
  TransactionType m_TransactionType;
};
