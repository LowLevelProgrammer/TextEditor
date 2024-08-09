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

struct Offset {
  int Y;
  int X;
};

enum class OperationType { InsertChar, RemoveChar, InsertNewLine };

class TextBuffer {
public:
  TextBuffer();
  ~TextBuffer();

  void InsertChar(char character, Offset offset);
  void InsertNewline(Offset offset);
  void EraseChar(Offset offset);
  void EraseNewline(Offset offset);
  void InsertLine(std::string line);
  Position MoveCaret(Direction direction);
  void PrintBuffer();
  void Select(Position start, Position end);
  // TODO: Check for file limits
  void SetCaretPosition(Position position);
  std::string GetSelectedText();
  bool SelectionActive();
  void InsertBuffer(Register reg);
  void DeleteSelection();

  bool IsStartOfLine(int yOffset, int xOffset);
  bool IsSOF(int yOffset, int xOffset);
  bool IsEOF();
  void Clear();
  const Position GetEOFPosition() const;

  const std::string &GetLineAtOffset(int lineOffset);
  char GetCharAtOffset(Offset offset);

  inline const std::vector<std::string> &GetLines() const { return m_Lines; }
  inline const Position &GetCaretPosition() const { return m_CaretPosition; }

private:
  std::vector<std::string> m_Lines;
  // Position always refers to the 1-Based indexing of text in the editor
  Position m_CaretPosition;
  Position m_SelectionStartPosition;
  bool m_IsSelected;
  // TODO: Check file bounds before any caret position setting operation
  // everywhere
  Position m_FileEnd;

private:
  std::pair<Position, Position> DetermineEnds();
};
