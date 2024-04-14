#pragma once

#include "Register.h"
#include <string>
#include <vector>

struct Position {
  int Line;
  int Column;
};

class TextBuffer {
public:
  TextBuffer();
  ~TextBuffer();

  void InsertLine(std::string text);
  void Backspace();
  void Undo();
  void Redo();
  void PrintBuffer();
  void Select(Position start, Position end);
  void SetCaretPosition(Position position);
  std::string GetSelectedText();
  bool SelectionActive();
  void InsertBuffer(Register reg);
  void DeleteSelection();

  inline std::vector<std::string> GetHistory() { return m_History; }
  std::vector<std::string> GetLines() { return m_Lines; }
  const std::vector<std::string> &GetLines() const { return m_Lines; }

private:
  std::vector<std::string> m_Lines;
  std::vector<std::string> m_History;
  // Position always refers to the 1-Based indexing of text in the editor
  Position m_CaretPosition;
  Position m_SelectionStartPosition;
  bool m_IsSelected;

private:
  std::pair<Position, Position> DetermineEnds();
};
