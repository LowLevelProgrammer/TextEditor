#include "Editor.h"

#include <string>

Editor::Editor() : m_TextBuffer(), m_FileHandler() {
  m_Register = new Register[10];

  for (int i = 0; i < 10; i++) {
    m_Register[i] = Register(i);
  }
}

Editor::~Editor() { delete[] (m_Register); }

void Editor::InsertChar(char character) {}

void Editor::BackSpace() {}
void Editor::Select(Position startPosition, Position endPosition) {
  m_TextBuffer.Select(startPosition, endPosition);
}
void Editor::Undo() {}
void Editor::Redo() {}
void Editor::SetCaretPosition(Position position) {
  m_TextBuffer.SetCaretPosition(position);
}

void Editor::Copy(int registerNumber) {
  if (m_TextBuffer.SelectionActive()) {
    m_Register[registerNumber].Insert(m_TextBuffer.GetSelectedText());
  }
}

void Editor::Paste(int registerNumber) {
  if (m_TextBuffer.SelectionActive())
    m_TextBuffer.DeleteSelection();

  m_TextBuffer.InsertBuffer(m_Register[registerNumber]);
}

void Editor::OpenFile(std::string filePath) {
  m_TextBuffer = m_FileHandler.Open(filePath);
}
void Editor::Save() {
  // if (!m_FileHandler.GetIsOpen())
  //   std::cerr << "Error: No file to save to" << std::endl;
  // m_FileHandler.WriteToFile(m_TextBuffer);
}
void Editor::SaveAs(std::string filePath) {
  m_FileHandler.SaveAs(m_TextBuffer, filePath);
}
/* Private Functions */
void Editor::Display() { m_TextBuffer.PrintBuffer(); }

void Editor::MoveCaret(Direction direction) {
  m_TextBuffer.MoveCaret(direction);
}

bool Editor::IsFileOpen() { return m_FileHandler.IsOpen(); }

std::string Editor::GetFilePath() { return m_FileHandler.GetFilePath(); }
