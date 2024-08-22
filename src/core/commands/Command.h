#pragma once

enum class CommandType { InsertChar, InsertNewline, EraseChar, EraseNewline };

class Command {
public:
  inline virtual ~Command() {}

  virtual void Execute() = 0;
  virtual void Undo() = 0;
  virtual void Redo() = 0;

  inline CommandType GetCommandType() const { return m_CommandType; }

protected:
  CommandType m_CommandType;
};
