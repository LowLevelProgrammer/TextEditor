#pragma once

#include <string>
enum class CommandType { InsertChar, InsertNewline, EraseChar, EraseNewline };

class Command {
public:
  inline virtual ~Command() {}

  virtual std::string TransactionDetails() = 0;
  virtual void Execute() = 0;
  virtual void Undo() = 0;
  virtual void Redo() = 0;

  virtual const char GetCommandCharacter() const = 0;

  inline CommandType GetCommandType() const { return m_CommandType; }

protected:
  CommandType m_CommandType;
};
