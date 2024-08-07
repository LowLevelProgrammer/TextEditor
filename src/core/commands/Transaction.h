#pragma once

class Transaction {
public:
  inline virtual ~Transaction() {}

  virtual void Execute() = 0;
  virtual void Undo() = 0;
  virtual void Redo() = 0;
};
