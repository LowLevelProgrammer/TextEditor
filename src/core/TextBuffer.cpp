#include "TextBuffer.h"
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

TextBuffer::TextBuffer()
    : m_CaretPosition({1, 1}), m_SelectionStartPosition({-1, -1}),
      m_IsSelected(false) {
  m_Lines.clear();
  m_Lines.push_back({});
  m_UndoStack.push_back({.PositionStart = {1, 1}, .PositionEnd = {1, 1}});
}
TextBuffer::~TextBuffer() {}

void TextBuffer::InsertChar(char character) {
  // TODO: Check for valid caret position
  int historyHead = m_UndoStack.size() - 1;
  int contentHead = m_UndoStack[historyHead].Content.size() - 1;
  // If the character is a space
  // If it's the first space then add a new action element in history
  // else append to existing action
  if (character == ' ' &&
      m_UndoStack[historyHead].Content[contentHead] != ' ') {
    // Add new history element
    m_UndoStack.push_back({ActionType::Insert,
                           "",
                           {m_CaretPosition.Line, m_CaretPosition.Column},
                           {m_CaretPosition.Line, m_CaretPosition.Column}});
    historyHead = m_UndoStack.size() - 1;
    contentHead = 1;
  }
  // If a newline character then always add an element to text buffer
  else if (character == '\n') {
    // Add new element to text buffer
    m_Lines.push_back({});

    // If first newline character then add new element history
    // Else if consecutive newline then append to last action
    if (m_UndoStack[historyHead].Content[contentHead] == '\n') {
      // Append in consecutive newline chars
      m_UndoStack[historyHead].Content.push_back('\n');
      m_UndoStack[historyHead].PositionEnd.Column = 1;

      // Update Caret Position
      m_CaretPosition.Line++;
      m_CaretPosition.Column = 1;

    } else {
      // Add new element to history
      m_UndoStack.push_back({ActionType::Insert,
                             "",
                             {m_CaretPosition.Line, m_CaretPosition.Column},
                             {m_CaretPosition.Line, m_CaretPosition.Column}});

      historyHead = m_UndoStack.size() - 1;
      m_CaretPosition.Line++;
      m_CaretPosition.Column = 1;
      // Insert newline character to the element in history
      m_UndoStack[historyHead].Content.push_back('\n');
      // Update end position
      m_UndoStack[historyHead].PositionEnd.Line = m_CaretPosition.Line;
      m_UndoStack[historyHead].PositionEnd.Column = m_CaretPosition.Column;
      // Return because we don't need to add newline char in text buffer
    }
    return;
  }
  // Insert to text buffer
  int currentLine = m_CaretPosition.Line - 1;
  int lineOffset = m_CaretPosition.Column - 1;
  m_Lines[currentLine].insert(lineOffset, 1, character);
  m_CaretPosition.Column++;

  // Add/Update history
  m_UndoStack[historyHead].Content.push_back(character);
  m_UndoStack[historyHead].PositionEnd.Line = m_CaretPosition.Line;
  m_UndoStack[historyHead].PositionEnd.Column = m_CaretPosition.Column;
}

void TextBuffer::InsertLine(std::string text) {
  m_Lines.push_back(text);
  m_CaretPosition.Line++;
  m_CaretPosition.Column = text.size();
}

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

void TextBuffer::Backspace() {
  int xPos = m_CaretPosition.Column - 2;
  int yPos = m_CaretPosition.Line - 1;

  // First check if selection is active
  if (m_IsSelected) {
    // Handles caret position update
    DeleteSelection();
  }
  // Else check if the caret is at the very beginning of the document
  else if (xPos == -1 && yPos == 0) {
    return;
  }
  // Else check if caret is at the very beginning of a line
  else if (xPos == -1) {
    int prevLineYOffset = yPos - 1;
    int prevLineXOffset = m_Lines[prevLineYOffset].size() - 1;

    // Need to simply move to the previous line if there's nothing after the
    // caret
    // Or need to move every line to the previous line if there is
    std::string currentLine = m_Lines[yPos];

    // Copy current line to the previous line
    m_Lines[prevLineYOffset].append(currentLine);
    // Remove current line
    m_Lines.erase(m_Lines.begin() + yPos);

    //
    // Update caret position
    //

    // Add 2 to the x-offset because caret should be on the right side of the
    // char
    SetCaretPosition({prevLineYOffset + 1, prevLineXOffset + 2});
  } else {
    m_Lines[yPos].erase(m_Lines[yPos].begin() + xPos);
    // Update caret position
    m_CaretPosition.Column--;
  }
}

void TextBuffer::Undo() {
  if (m_UndoStack.empty())
    return;
  Action mostRecentAction = m_UndoStack[m_UndoStack.size() - 1];
  int numCharToRemove = mostRecentAction.Content.size();

  Position positionOfCharToRemove = mostRecentAction.PositionEnd;
  // Compensate because the caret is on the right of the character
  positionOfCharToRemove.Column--;
  while (numCharToRemove) {
    // Removes newline "character"
    if (m_Lines[positionOfCharToRemove.Line - 1].size() == 0) {
      m_Lines.erase(m_Lines.begin() + positionOfCharToRemove.Line - 1);
      positionOfCharToRemove.Line--;
      positionOfCharToRemove.Column =
          m_Lines[positionOfCharToRemove.Line - 1].size();
    }
    // Removes any other character
    else {
      m_Lines[positionOfCharToRemove.Line - 1].erase(
          positionOfCharToRemove.Column - 1, 1);
      positionOfCharToRemove.Column--;
    }
    numCharToRemove--;
  }
  // Compensate as caret will be on the right side of the character
  positionOfCharToRemove.Column++;

  assert(positionOfCharToRemove == mostRecentAction.PositionStart);
  m_CaretPosition = positionOfCharToRemove;
  // Insert the last element into the redo stack
  m_RedoStack.push_back(m_UndoStack[m_UndoStack.size() - 1]);
  // Remove most recent action from the undo stack
  m_UndoStack.pop_back();
}

void TextBuffer::Redo() {
  if (m_RedoStack.empty()) {
    return;
  }
  Action mostRecentAction = m_RedoStack.back();

  Position positionCharToInsert = mostRecentAction.PositionStart;
  int numCharToInsert = mostRecentAction.Content.size();
  std::string stringToInsert = mostRecentAction.Content;

  for (int i = 0; i < numCharToInsert; i++) {
    int lineIndex = positionCharToInsert.Line - 1;
    int columnIndex = positionCharToInsert.Column - 1;
    // If it's a newline character then insert an empty line in the text buffer
    if (stringToInsert[i] == '\n') {
      m_Lines.insert(m_Lines.begin() + lineIndex + 1, "");
      positionCharToInsert.Line++;
      positionCharToInsert.Column = 1;
    } else {
      m_Lines[lineIndex].insert(m_Lines[lineIndex].begin() + columnIndex,
                                stringToInsert[i]);
      positionCharToInsert.Column++;
    }
  }
  assert(positionCharToInsert == mostRecentAction.PositionEnd);
  m_CaretPosition = mostRecentAction.PositionEnd;
  m_UndoStack.push_back(m_RedoStack.back());
  m_RedoStack.pop_back();
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
