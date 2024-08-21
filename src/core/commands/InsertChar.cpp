#include "InsertChar.h"

#include <iostream>
#include <sstream>

InsertChar::InsertChar(TextBuffer &textBuffer, char data, Offset offset)
    : m_TextBuffer(textBuffer), m_Character(data), m_Offset(offset) {
  m_TransactionType = TransactionType::InsertChar;
}

std::string InsertChar::TransactionDetails() {
  std::stringstream ss;
  ss << "Add char '" << m_Character << "' at offset { " << m_Offset.Y << ", "
     << m_Offset.X << " }" << std::endl;
  ;
  return ss.str();
}

void InsertChar::Execute() {
  m_TextBuffer.InsertChar(m_Character, m_Offset);
  // std::cout << TransactionDetails();
}

void InsertChar::Undo() {
  m_TextBuffer.EraseChar(m_Offset);
  // std::cout << "Undid: " << TransactionDetails();
}

void InsertChar::Redo() {
  m_TextBuffer.InsertChar(m_Character, m_Offset);
  // std::cout << "Redid: " << TransactionDetails();
}
