#pragma once

#include "Register.h"
#include <string>
#include <vector>

enum class Direction { Left, Right, Up, Down };

struct Position {
  int Line;
  int Column;

  bool operator==(const Position &other) const {
    return (this->Line == other.Line && this->Column == other.Column);
  }
};

enum class OperationType { InsertChar, RemoveChar, InsertNewLine };

struct Operation {
  OperationType Type;
  char Character;
  int YOffset;
  int XOffset;
};

struct Transaction {
  std::vector<Operation> Operations;
  void Clear() { Operations.clear(); }
  bool Empty() { return Operations.empty(); }
};

class TextBuffer {
public:
  TextBuffer();
  ~TextBuffer();

  // Can Undo
  void AddCharAtCaret(char character);
  void AddCharAtOffset(char character, int yOffset, int xOffset);
  void AddNewlineCharAtOffset(int yOffset, int xOffset);
  void AddPrintableCharAtOffset(char character, int yOffset, int xOffset);
  void InsertChar(char character, int yOffset, int xOffset);
  void InsertLine(std::string line);
  // Can Undo
  Position MoveCaret(Direction direction);
  void RemoveCharAtCaret();
  void Undo();
  void Redo();
  void PrintBuffer();
  void Select(Position start, Position end);
  // TODO: Check for file limits
  void SetCaretPosition(Position position);
  std::string GetSelectedText();
  bool SelectionActive();
  // Can Undo
  void InsertBuffer(Register reg);
  // Can Undo
  void DeleteSelection();
  void RemoveNewlineCharAtOffset(int yOffset);
  void RemoveCharAtOffset(int yOffset, int xOffset);
  void EraseChar(int yOffset, int xOffset);
  bool IsStartOfLine(int yOffset, int xOffset);
  bool IsSOF(int yOffset, int xOffset);
  bool IsEOF();
  const Position GetEOFPosition() const;
  void Clear();

  inline const std::vector<std::string> &GetLines() const { return m_Lines; }
  inline const Position &GetCaretPosition() const { return m_CaretPosition; }
  inline const Transaction &GetCurrentTransaction() const {
    return m_CurrentTransaction;
  }
  inline const std::vector<Transaction> &GetUndoStack() const {
    return m_UndoStack;
  }

private:
  std::vector<std::string> m_Lines;
  // Position always refers to the 1-Based indexing of text in the editor
  Position m_CaretPosition;
  Position m_SelectionStartPosition;
  bool m_IsSelected;
  // TODO: Check file bounds before any caret position setting operation
  // everywhere
  Position m_FileEnd;
  Transaction m_CurrentTransaction;
  bool m_InTransaction = false;
  std::vector<Transaction> m_UndoStack;
  std::vector<Transaction> m_RedoStack;
  char m_LastCharacter = '\0';

private:
  std::pair<Position, Position> DetermineEnds();
  void StartTransaction();
  void StopTransaction();
  void CommitTransaction();
  void AddOperation(const Operation &operation);
};
