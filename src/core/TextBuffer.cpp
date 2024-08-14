#include "TextBuffer.h"
#include "custom_assert.h"

#include <algorithm>
#include <assert.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

TextBuffer::TextBuffer()
    : m_CaretPosition({1, 1}), m_SelectionStartPosition({-1, -1}),
      m_IsSelected(false) {
  m_Lines.clear();
  m_Lines.push_back({});
}
TextBuffer::~TextBuffer() {}

// Wrapper for std::insert function
void TextBuffer::InsertChar(char character, Offset offset) {
  ASSERT_WITHIN_OR_EDGE_BOUNDS(offset, m_Lines);
  m_Lines[offset.Y].insert(m_Lines[offset.Y].begin() + offset.X, character);
}

void TextBuffer::InsertNewline(Offset offset) {
  ASSERT_WITHIN_OR_EDGE_BOUNDS(offset, m_Lines);
  std::string stringToMove = m_Lines[offset.Y].substr(offset.X);
  m_Lines[offset.Y].erase(offset.X);

  int nextLineYOffset = offset.Y + 1;
  m_Lines.insert(m_Lines.begin() + nextLineYOffset, stringToMove);
}

// Wrapper around the string::erase function
void TextBuffer::EraseChar(Offset offset) {
  ASSERT_WITHIIN_BOUNDS(offset, m_Lines);
  m_Lines[offset.Y].erase(m_Lines[offset.Y].begin() + offset.X);
}

void TextBuffer::EraseNewline(Offset offset) {
  ASSERT_WITHIN_OR_EDGE_BOUNDS(offset, m_Lines);
  m_Lines[offset.Y] += m_Lines[offset.Y + 1];
  m_Lines.erase(m_Lines.begin() + offset.Y + 1);
}

void TextBuffer::InsertLine(std::string line) {}

// TODO: Refactor with cleaner IsEOF and IsEOL functions
Position TextBuffer::MoveCaret(Direction direction) {
  int yPos = m_CaretPosition.Line - 1;
  int xPos = m_CaretPosition.Column - 1;
  Position updatedCarentPosition;
  switch (direction) {
  case Direction::Up:
    // If at the fist line then bring the caret to the beginning of the document
    if (yPos == 0) {
      m_CaretPosition.Column = 1;
    }
    // Else move the caret to the previous line
    else {
      m_CaretPosition.Line--;
      int yPrevLinePos = yPos - 1;
      int prevLineSize = m_Lines[yPrevLinePos].size();
      // Check if the previous line is smaller than caret's current position
      if (m_CaretPosition.Column > prevLineSize + 1) {
        m_CaretPosition.Column = prevLineSize + 1;
      }
      // Else the column position remains as it is
    }
    break;
  case Direction::Down:
    // If at last line of the document then bring caret to the eof
    if (yPos == m_Lines.size() - 1) {
      int currentLineSize = m_Lines[yPos].size();
      m_CaretPosition.Column = currentLineSize + 1;
    }
    // Else move the caret to the next line
    else {
      m_CaretPosition.Line++;
      int yNextLinePos = yPos + 1;
      int nextLineSize = m_Lines[yNextLinePos].size();
      // Check if the next line is smaller than caret's current position
      if (m_CaretPosition.Column > nextLineSize + 1) {
        m_CaretPosition.Column = nextLineSize + 1;
      }
      // Else the column position remains as it is
    }
    break;
  case Direction::Left:
    // If at the beginning of a line that is not the first line
    if (m_CaretPosition.Column == 1 && yPos != 0) {
      int yPrevLinePos = yPos - 1;
      int prevLineSize = m_Lines[yPrevLinePos].size();
      m_CaretPosition.Line--;
      // Add 1 because the caret is at the right of the last character
      m_CaretPosition.Column = prevLineSize + 1;
    }
    // Else if not at the beginning of line (this condition now only applies for
    // the first line)
    else if (m_CaretPosition.Column != 1) {
      m_CaretPosition.Column--;
    }
    break;
  case Direction::Right:
    int currentLineSize = m_Lines[yPos].size();
    // If at the end of a line that is the not the last line
    if (m_CaretPosition.Column == m_Lines[yPos].size() + 1 && !IsEOF()) {
      m_CaretPosition.Line++;
      m_CaretPosition.Column = 1;
    } else if (IsEOF()) {
      break;
    } else {
      m_CaretPosition.Column++;
    }
    break;
  }
  // Variable just to be explicit about what is being returned
  updatedCarentPosition = {m_CaretPosition.Line, m_CaretPosition.Column};

  return updatedCarentPosition;
}

void TextBuffer::PrintBuffer() {
  for (auto line : m_Lines) {
    std::cout << line << std::endl;
  }
}

void TextBuffer::Select(Position start, Position end) {
  m_SelectionStartPosition = start;
  m_CaretPosition = end;
  m_IsSelected = true;
}

void TextBuffer::SetCaretPosition(Position position) {
  m_CaretPosition = {position.Line, position.Column};
  m_IsSelected = false;
}

std::string TextBuffer::GetSelectedText() {
  if (!m_IsSelected) {
    return NULL;
  }
  auto [start, end] = DetermineEnds();

  std::string buffer;

  // TODO: Find a cleaner way to do this
  int currentLine = start.Line;
  int offset = start.Column;
  while (currentLine <= end.Line) {
    // Breaking condition
    if (currentLine == end.Line && offset >= end.Column) {
      break;
    }
    // Compensate for 1 based indexing
    if (offset > m_Lines[currentLine - 1].size()) {
      offset = 1;
      currentLine++;
      buffer.push_back('\n');
    }
    buffer.push_back(m_Lines[currentLine - 1][offset - 1]);
    offset++;
  }

  return buffer;
}

bool TextBuffer::SelectionActive() { return m_IsSelected; }

// TODO: Store history to add undo feature
void TextBuffer::DeleteSelection() {
  auto [start, end] = DetermineEnds();
  // If selection is within the same line then simply delete
  if (start.Line == end.Line) {
    int countOfELementsToRemove = end.Line - start.Line + 1;
    m_Lines[start.Line - 1].erase(start.Column - 1, countOfELementsToRemove);
  } else {
    //
    // There's a better way to do this but right now I just want to be explicit
    //

    // Deleting the ending part of selection start
    m_Lines[start.Line - 1].erase(start.Column - 1);

    // Deleting lines in between start and end line
    int numLinesToDelete = end.Line - start.Line - 1;
    for (int i = 0; i < numLinesToDelete; i++) {
      // Deleting the lines after start line
      // The -1 and 1 cancels out hence only start.line
      m_Lines.erase(m_Lines.begin() + start.Line);
    }
    // Deleting the lines in between changes selection end
    int newEndLine = start.Line + 1;
    // Deleting the starting part of selection end
    int numCharsToDisplace = end.Column;
    m_Lines[newEndLine - 1].erase(0, numCharsToDisplace);
    // Append remaining line of the selection end to the selection start offset
    m_Lines[start.Line - 1].append(m_Lines[newEndLine - 1]);
    // Erease the duplicated remaining line at selection end
    m_Lines.erase(m_Lines.begin() + newEndLine - 1);
  }
  m_IsSelected = false;
  m_CaretPosition = start;
}

std::pair<Position, Position> TextBuffer::DetermineEnds() {
  Position start, end;
  if (m_CaretPosition.Line > m_SelectionStartPosition.Line) {
    start = m_SelectionStartPosition;
    end = m_CaretPosition;
  } else if (m_CaretPosition.Line == m_SelectionStartPosition.Line) {
    if (m_CaretPosition.Column >= m_SelectionStartPosition.Column) {
      start = m_SelectionStartPosition;
      end = m_CaretPosition;
    } else {
      start = m_CaretPosition;
      end = m_SelectionStartPosition;
    }
  } else {
    start = m_CaretPosition;
    end = m_SelectionStartPosition;
  }
  return {start, end};
}

void TextBuffer::InsertBuffer(Register reg) {
  // TODO: Optimize
  std::vector<std::string> buffer;
  std::string content = reg.Extract();
  int begin = 0, end = -1;

  for (int i = 0; i < content.size(); i++) {
    if (content[i] == '\n' || i == content.size() - 1) {
      end = i;
      buffer.push_back(content.substr(begin, end));
      begin = i + 1;
    }
  }

  auto [line, offset] = m_CaretPosition;

  // If there are multiple lines in the buffer i.e there's a newline character
  // Need to split the line at the position where caret is present
  if (buffer.size() > 1 ||
      (buffer.size() == 1 &&
       std::find(buffer.begin(), buffer.end(), "\n") != buffer.end())) {
    std::string temp = m_Lines[line - 1].substr(offset - 1);
    m_Lines[line - 1].erase(offset - 1);
    if (temp != "")
      m_Lines.insert(m_Lines.begin() + line, temp);
  }

  if (buffer[0] != "\n") {
    m_Lines[line - 1].append(buffer[0]);
  }

  // Dont iterate through the last element because it needs to be appended
  for (int i = 1; i < buffer.size() - 1; i++) {
    m_Lines.insert(m_Lines.begin() + line, buffer[i]);
    line++;
  }

  m_Lines[line].insert(0, buffer[buffer.size() - 1]);
}

bool TextBuffer::IsStartOfLine(Position position) {
  return position.Column == 1;
}

bool TextBuffer::IsSOF(Position position) {
  return (position.Line == 1 && position.Column == 1);
}

bool TextBuffer::IsEOF() {
  int yPos = m_Lines.size() - 1;
  return (m_CaretPosition.Line == m_Lines.size() &&
          m_CaretPosition.Column == m_Lines[yPos].size() + 1);
}

const Position TextBuffer::GetEOFPosition() const {
  int yPosLastLine = m_Lines.size() - 1;
  int lastLineSize = m_Lines[yPosLastLine].size();

  return {yPosLastLine + 1, lastLineSize + 1};
}

void TextBuffer::Clear() { m_Lines.clear(); }

const std::string &TextBuffer::GetLineAtOffset(int lineOffset) {
  ASSERT_WITHIN_LINE_BOUNDS(lineOffset, m_Lines);
  return m_Lines[lineOffset];
}

int TextBuffer::GetLineSizeAtOffset(int lineOffset) {
  ASSERT_WITHIN_LINE_BOUNDS(lineOffset, m_Lines);
  return m_Lines[lineOffset].size();
}

const char &TextBuffer::GetCharAtOffset(Offset offset) {
  ASSERT_WITHIIN_BOUNDS(offset, m_Lines);
  return m_Lines[offset.Y][offset.X];
}

std::string TextBuffer::GetPrintableTextBuffer() {
  std::string tb;
  for (int i = 0; i < m_Lines.size(); i++) {
    tb += m_Lines[i];
    if (i < m_Lines.size() - 1)
      tb += '\n';
  }
  return tb;
}
