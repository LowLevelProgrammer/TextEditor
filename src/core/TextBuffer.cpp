#include "TextBuffer.h"
#include <iostream>
#include <string>

TextBuffer::TextBuffer()
    : m_CaretPosition({0, 0}), m_SelectionStartPosition({-1, -1}),
      m_IsSelected(false) {
  m_Lines.clear();
}
TextBuffer::~TextBuffer() {}

void TextBuffer::InsertLine(std::string text) {
  m_Lines.push_back(text + '\n');
  m_CaretPosition.Line++;
  m_CaretPosition.Column = text.size();
}

void TextBuffer::Delete() {
  if (m_IsSelected) {

  } else {
    m_Lines[m_CaretPosition.Line - 1].erase(
        m_Lines[m_CaretPosition.Line - 1].begin() + m_CaretPosition.Column - 1);
    m_CaretPosition.Column--;
  }
}

void TextBuffer::Undo() {
  if (m_Lines.size() > 0) {
    std::string toUndo = m_Lines[m_Lines.size() - 1];
    m_History.emplace_back(toUndo);
    m_Lines.pop_back();
  }
}

void TextBuffer::Redo() {
  if (m_History.size() > 0) {
    std::string toRedo = m_History[m_History.size() - 1];
    m_Lines.push_back(toRedo);
    m_History.pop_back();
  }
}

void TextBuffer::PrintBuffer() {
  for (auto line : m_Lines) {
    std::cout << line;
  }
}

void TextBuffer::Select(Position start, Position end) {
  m_SelectionStartPosition = start;
  m_CaretPosition = end;
  m_IsSelected = true;
}

void TextBuffer::SetCaretPosition(int line, int column) {
  m_CaretPosition = {line, column};
  m_IsSelected = false;
}

std::string TextBuffer::GetSelectedText() {
  if (!m_IsSelected) {
    return NULL;
  }
  auto [start, end] = DetermineEnds();

  std::string buffer;

  int currentLine = start.Line;
  int offset = start.Column;
  while (currentLine <= end.Line) {
    // Breaking condition
    if (currentLine == end.Line && offset > end.Column) {
      break;
    }
    // Compensate of 1 based indexing
    if (offset > m_Lines[currentLine - 1].size()) {
      offset = 1;
      currentLine++;
    }
    buffer.push_back(m_Lines[currentLine - 1][offset - 1]);
    offset++;
  }

  return buffer;
}

bool TextBuffer::SelectionActive() { return m_IsSelected; }

void TextBuffer::DeleteSelection() {
  auto [start, end] = DetermineEnds();
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
    // Deleting the starting part of selecting end
    int numCharsToDisplace = end.Column;
    m_Lines[newEndLine - 1].erase(0, numCharsToDisplace);
    // Append remaining line of the selection end to the selection start offset
    m_Lines[start.Line - 1].append(m_Lines[newEndLine - 1]);
    // Erease the duplicated remaining line at selection end
    m_Lines.erase(m_Lines.begin() + newEndLine - 1);
  }
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
