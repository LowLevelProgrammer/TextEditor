#include "EraseChar.h"

#include <iostream>
#include <sstream>

EraseChar::EraseChar(TextBuffer &textBuffer, Offset offset)
    : m_TextBuffer(textBuffer), m_Offset(offset) {
  m_TransactionType = TransactionType::EraseChar;
}

std::string EraseChar::TransactionDetails() {
  std::stringstream ss;
  ss << "Remove char '" << m_RemovedChar << "' at offset { " << m_Offset.Y
     << ", " << m_Offset.X << " }" << std::endl;
  return ss.str();
}

void EraseChar::Execute() {
  m_RemovedChar = m_TextBuffer.GetCharAtOffset(m_Offset);
  m_TextBuffer.EraseChar(m_Offset);
  // std::cout << TransactionDetails();
}

void EraseChar::Undo() {
  m_TextBuffer.InsertChar(m_RemovedChar, m_Offset);
  // std::cout << "Undid: " << TransactionDetails();
}

void EraseChar::Redo() {
  m_TextBuffer.EraseChar(m_Offset);
  // std::cout << "Redid: " << TransactionDetails();
}
