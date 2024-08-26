#include "InsertNewline.h"

#include <iostream>
#include <sstream>

InsertNewline::InsertNewline(TextBuffer &textBuffer, Offset offset)
    : m_TextBuffer(textBuffer), m_Offset(offset) {
  m_CommandType = CommandType::InsertNewline;
}

std::string InsertNewline::TransactionDetails() {
  std::stringstream ss;
  ss << "Add char '\\n' at offset { " << m_Offset.Y << ", " << m_Offset.X
     << " }" << std::endl;
  return ss.str();
}
void InsertNewline::Execute() {
  m_TextBuffer.InsertNewline(m_Offset);
  Position caretPositon = {m_Offset.Y + 2, 1};
  m_TextBuffer.SetCaretPosition(caretPositon);
  // std::cout << TransactionDetails();
}

void InsertNewline::Undo() {
  m_TextBuffer.EraseNewline(m_Offset);
  Position caretPosition = {m_Offset.Y + 1, m_Offset.X + 1};
  m_TextBuffer.SetCaretPosition(caretPosition);
  // std::cout << "Undid: " << TransactionDetails();
}

void InsertNewline::Redo() {
  Execute();
  // std::cout << "Redid: " << TransactionDetails();
}
