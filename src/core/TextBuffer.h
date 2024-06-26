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

enum class ActionType { Insert, Delete, Copy, Paste };

struct Action {
  ActionType Type;
  std::string Content;
  Position PositionStart;
  Position PositionEnd;
};

class TextBuffer {
public:
  TextBuffer();
  ~TextBuffer();

  // Can Undo
  void InsertChar(char character);
  // Can Undo
  void InsertLine(std::string text);
  // Can Undo
  Position MoveCaret(Direction direction);
  void Backspace();
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
  bool IsEOF();
  const Position GetEOFPosition() const;
  void Clear();

  inline const std::vector<std::string> &GetLines() const { return m_Lines; }
  inline const Position &GetCaretPosition() const { return m_CaretPosition; }
  inline const std::vector<Action> &GetHistory() const { return m_UndoStack; }
  inline const int GetNumElementsUndoStack() const {
    return m_UndoStack.size();
  }
  inline const int GetNumElementsRedoStack() const {
    return m_RedoStack.size();
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
  std::vector<Action> m_UndoStack;
  std::vector<Action> m_RedoStack;

private:
  std::pair<Position, Position> DetermineEnds();
};
