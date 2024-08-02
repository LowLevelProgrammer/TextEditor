#include "TextBuffer.h"

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

void TextBuffer::AddCharAtCaret(char character) {
  int yOffset = m_CaretPosition.Line - 1;
  int xOffset = m_CaretPosition.Column - 1;

  AddCharAtOffset(character, yOffset, xOffset);
}

void TextBuffer::AddCharAtOffset(char character, int yOffset, int xOffset) {

  Operation op;
  op.YOffset = yOffset;
  op.XOffset = xOffset;
  op.Character = character;

  // If first of 'space' or 'newline' char of consecutive sequence of such
  // chars
  // then end the current transaction and start a new one
  if (!m_InTransaction || (character == ' ' && m_LastCharacter != ' ') ||
      (character == '\n' && m_LastCharacter != '\n')) {
    // If already in transaction then it has entered the condition because
    // its
    // either a first "space" or a "newline" char
    // In which case have to stop the current transaction
    if (m_InTransaction) {
      StopTransaction();
    }
    StartTransaction();
  }

  switch (character) {
  case '\n': {
    // String to move to the new line
    // |
    // L__ Empty string incase caret is at EOL
    // L__ Else rest of the string is moved to the new line
    // std::string stringToMove = m_Lines[yOffset].substr(xOffset);
    // m_Lines.insert(m_Lines.begin() + yOffset + 1, stringToMove);
    //
    // // Remove the string from the current line
    // m_Lines[yOffset].erase(xOffset);
    //

    AddNewlineCharAtOffset(yOffset, xOffset);
    m_CaretPosition.Line++;
    m_CaretPosition.Column = 1;

    // Record the Operation
    op.Type = OperationType::InsertNewLine;
  } break;
  case ' ':
    // m_Lines[yOffset].insert(m_Lines[yOffset].begin() + xOffset, ' ');
    AddPrintableCharAtOffset(' ', yOffset, xOffset);
    m_CaretPosition.Column++;

    op.Type = OperationType::InsertChar;
    break;
  default:
    // m_Lines[yOffset].insert(m_Lines[yOffset].begin() + xOffset, character);
    AddPrintableCharAtOffset(character, yOffset, xOffset);
    m_CaretPosition.Column++;
    op.Type = OperationType::InsertChar;
    break;
  }

  AddOperation(op);

  CommitTransaction();

  // Update last character
  m_LastCharacter = character;
}

void TextBuffer::AddNewlineCharAtOffset(int yOffset, int xOffset) {

  int currentLineSize = m_Lines[yOffset].size();
  int maxYOffset = m_Lines.size() - 1;

  if (xOffset > currentLineSize || xOffset < 0 || yOffset > maxYOffset ||
      yOffset < 0) {
    std::cerr << "Invalid offset to insert newline character" << std::endl;
    exit(-1);
  }

  std::string stringToMove = m_Lines[yOffset].substr(xOffset);
  m_Lines[yOffset].erase(xOffset);
  int nextLineYOffset = yOffset + 1;
  m_Lines.insert(m_Lines.begin() + nextLineYOffset, stringToMove);
}

void TextBuffer::AddPrintableCharAtOffset(char character, int yOffset,
                                          int xOffset) {
  int currentLineSize = m_Lines[yOffset].size();
  int maxYOffset = m_Lines.size() - 1;

  // Bounds checking
  if (xOffset > currentLineSize || xOffset < 0 || yOffset > maxYOffset ||
      yOffset < 0) {
    std::cerr << "Invalid offset to insert printable character" << std::endl;
    exit(-1);
  }

  InsertChar(character, yOffset, xOffset);
}

// Wrapper for std::insert function
// No bounds checking
void TextBuffer::InsertChar(char character, int yOffset, int xOffset) {
  m_Lines[yOffset].insert(m_Lines[yOffset].begin() + xOffset, character);
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

void TextBuffer::RemoveCharAtCaret() {
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
  if (!m_UndoStack.empty()) {
    Transaction trnxn = m_UndoStack.back();
    m_RedoStack.push_back(trnxn);
    m_UndoStack.pop_back();
    StopTransaction();
    m_LastCharacter = '\0';

    for (auto it = trnxn.Operations.rbegin(); it != trnxn.Operations.rend();
         it++) {
      Operation op = *it;
      int yOffset = op.YOffset;
      int xOffset = op.XOffset;
      switch (op.Type) {
      case OperationType::InsertChar:
        RemoveCharAtOffset(yOffset, xOffset);
        SetCaretPosition({yOffset + 1, xOffset + 1});
        break;
      case OperationType::RemoveChar:
        break;
      case OperationType::InsertNewLine:
        RemoveNewlineCharAtOffset(yOffset);
        SetCaretPosition({yOffset + 1, xOffset + 1});
        break;
      }
    }
  }
}

void TextBuffer::Redo() {
  if (!m_RedoStack.empty()) {
    Transaction trnxn = m_RedoStack.back();
    m_RedoStack.pop_back();
    StopTransaction();
    m_LastCharacter = '\0';

    for (auto it = trnxn.Operations.begin(); it != trnxn.Operations.end();
         it++) {
      Operation op = *it;
      int yOffset = op.YOffset;
      int xOffset = op.XOffset;
      switch (op.Type) {
      case OperationType::InsertChar:
        AddCharAtOffset(op.Character, yOffset, xOffset);
        SetCaretPosition({yOffset + 1, xOffset + 2});
        break;
      case OperationType::RemoveChar:
        break;
      case OperationType::InsertNewLine:
        AddNewlineCharAtOffset(yOffset, xOffset);
        SetCaretPosition({yOffset + 2, xOffset + 2});
        break;
      }
    }
  }
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

void TextBuffer::RemoveNewlineCharAtOffset(int yOffset) {
  // In this case have to move the (yOffset + 1)th line to yOffset
  int nextLineYOffset = yOffset + 1;
  int maxYOffset = m_Lines.size() - 1;

  // Bounds checking
  // To consider: Can change to yOffset > maxYOffset - 1 as if maxYOffset has
  // newline char then it is not the last line offset
  if (yOffset < 0 || yOffset > maxYOffset) {
    std::cerr << "Invalid offset to delete newline character from" << std::endl;
  }

  std::string stringToMove = m_Lines[nextLineYOffset];
  m_Lines.erase(m_Lines.begin() + nextLineYOffset);
  m_Lines[yOffset].append(stringToMove);
}

void TextBuffer::RemoveCharAtOffset(int yOffset, int xOffset) {
  int currentLineMaxXOffset = m_Lines[yOffset].size() - 1;
  int maxYOffset = m_Lines.size() - 1;

  // Bounds checking
  if (xOffset > currentLineMaxXOffset || xOffset < 0 || yOffset > maxYOffset ||
      yOffset < 0) {
    std::cerr << "Invalid offset to delete character from" << std::endl;
    exit(-1);
  }

  EraseChar(yOffset, xOffset);
}

// Just a wrapper around the string::erase fucntion
// Ensure the the offsets are within bounds before calling this function
// As this function won't do bounds checking
void TextBuffer::EraseChar(int yOffset, int xOffset) {
  m_Lines[yOffset].erase(m_Lines[yOffset].begin() + xOffset);
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

void TextBuffer::StartTransaction() {
  m_InTransaction = true;
  m_UndoStack.push_back({});
}

void TextBuffer::StopTransaction() {
  if (m_InTransaction && !m_CurrentTransaction.Empty()) {
    m_InTransaction = false;
    m_CurrentTransaction.Clear();
  } else {
    std::cerr << "Error: Invalid time to stop transaction" << std::endl;
  }
}

void TextBuffer::CommitTransaction() {
  if (m_UndoStack.empty()) {
    std::cerr << "Error in undo system: Commit when undo stack is empty"
              << std::endl;
    exit(-1);
  }
  Transaction &mostRecentTransaction = m_UndoStack.back();
  mostRecentTransaction = m_CurrentTransaction;
}

void TextBuffer::AddOperation(const Operation &operation) {
  m_CurrentTransaction.Operations.push_back(operation);
}
