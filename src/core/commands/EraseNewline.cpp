#include "EraseNewline.h"

#include <iostream>
#include <sstream>

EraseNewline::EraseNewline(TextBuffer &textBuffer, Offset offset)
    : m_TextBuffer(textBuffer), m_Offset(offset) {
  m_CommandType = CommandType::EraseNewline;
}

std::string EraseNewline::TransactionDetails() {
  std::stringstream ss;
  ss << "Remove char '\\n' at offset { " << m_Offset.Y << ", " << m_Offset.X
     << " }" << std::endl;
  return ss.str();
}

void EraseNewline::Execute() {
  m_TextBuffer.EraseNewline(m_Offset);
  Position caretPosition = {m_Offset.Y + 1, m_Offset.X + 1};
  m_TextBuffer.SetCaretPosition(caretPosition);
  // std::cout << TransactionDetails();
}

void EraseNewline::Undo() {
  m_TextBuffer.InsertNewline(m_Offset);
  Position caretPositon = {m_Offset.Y + 2, 1};
  m_TextBuffer.SetCaretPosition(caretPositon);
  // std::cout << "Undid: " << TransactionDetails();
}

void EraseNewline::Redo() {
  Execute();
  // std::cout << "Redid: " << TransactionDetails();
}
