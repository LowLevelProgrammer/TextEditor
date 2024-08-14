#include "InsertNewline.h"

#include <iostream>
#include <sstream>

InsertNewline::InsertNewline(TextBuffer &textBuffer, Offset offset)
    : m_TextBuffer(textBuffer), m_Offset(offset) {}

std::string InsertNewline::TransactionDetails() {
  std::stringstream ss;
  ss << "Add char '\\n' at offset { " << m_Offset.Y << ", " << m_Offset.X
     << " }" << std::endl;
  return ss.str();
}
void InsertNewline::Execute() {
  m_TextBuffer.InsertNewline(m_Offset);
  // std::cout << TransactionDetails();
}

void InsertNewline::Undo() {
  m_TextBuffer.EraseNewline(m_Offset);
  std::cout << "Undid: " << TransactionDetails();
}

void InsertNewline::Redo() {
  m_TextBuffer.InsertNewline(m_Offset);
  std::cout << "Redid: " << TransactionDetails();
}
