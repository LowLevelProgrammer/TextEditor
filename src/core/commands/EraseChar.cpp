#include "EraseChar.h"

#include <iostream>
#include <sstream>

EraseChar::EraseChar(TextBuffer &textBuffer, Offset offset)
    : m_TextBuffer(textBuffer), m_Offset(offset) {
  m_CommandType = CommandType::EraseChar;
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
  Position caretPosition = {m_Offset.Y + 1, m_Offset.X + 1};
  m_TextBuffer.SetCaretPosition(caretPosition);
  // std::cout << TransactionDetails();
}

void EraseChar::Undo() {
  m_TextBuffer.InsertChar(m_RemovedChar, m_Offset);
  Position caretPosition = {m_Offset.Y + 1, m_Offset.X + 2};
  m_TextBuffer.SetCaretPosition(caretPosition);
  // std::cout << "Undid: " << TransactionDetails();
}

void EraseChar::Redo() {
  Execute();
  // std::cout << "Redid: " << TransactionDetails();
}
