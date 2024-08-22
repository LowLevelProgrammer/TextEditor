#include "EraseNewline.h"

#include <iostream>
#include <sstream>

EraseNewline::EraseNewline(TextBuffer &textBuffer, Offset offset)
    : m_TextBuffer(textBuffer), m_Offset(offset) {
  m_CommandType = CommandType::EraseNewline;
}
EraseNewline::~EraseNewline() {}

std::string EraseNewline::TransactionDetails() {
  std::stringstream ss;
  ss << "Remove char '\\n' at offset { " << m_Offset.Y << ", " << m_Offset.X
     << " }" << std::endl;
  return ss.str();
}

void EraseNewline::Execute() {
  m_TextBuffer.EraseNewline(m_Offset);
  // std::cout << TransactionDetails();
}

void EraseNewline::Undo() {
  m_TextBuffer.InsertNewline(m_Offset);
  // std::cout << "Undid: " << TransactionDetails();
}

void EraseNewline::Redo() {
  m_TextBuffer.EraseNewline(m_Offset);
  // std::cout << "Redid: " << TransactionDetails();
}
