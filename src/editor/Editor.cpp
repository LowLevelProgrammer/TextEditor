#include "Editor.h"

#include <iostream>
#include <string>

Editor::Editor() : m_TextBuffer(), m_FileHandler() {
  m_Register = new Register[10];

  for (int i = 0; i < 10; i++) {
    m_Register[i] = Register(i);
  }
}

Editor::~Editor() { delete[] (m_Register); }

void Editor::Run() {
  std::string line;
  while (true) {
    std::getline(std::cin, line);
    if (line.empty())
      break;
    m_TextBuffer.InsertLine(line);
  }

  m_TextBuffer.Backspace();
  m_TextBuffer.Backspace();
  m_TextBuffer.Backspace();
  std::cout << "Text in the buffer\n";

  Display();
}

void Editor::InsertLine(std::string line) { m_TextBuffer.InsertLine(line); }

void Editor::BackSpace() { m_TextBuffer.Backspace(); }
void Editor::Select(Position startPosition, Position endPosition) {
  m_TextBuffer.Select(startPosition, endPosition);
}
void Editor::Undo() { m_TextBuffer.Undo(); }
void Editor::Redo() { m_TextBuffer.Redo(); }
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
  m_FileHandler.OpenFile(filePath);
  m_TextBuffer = m_FileHandler.ReadFromFile();
}
void Editor::Save() {
  if (!m_FileHandler.GetIsOpen())
    std::cerr << "Error: No file to save to" << std::endl;
  m_FileHandler.WriteToFile(m_TextBuffer);
}
void Editor::SaveAs(std::string filePath) {
  m_FileHandler.CreateFile(filePath);
  m_FileHandler.WriteToFile(m_TextBuffer);
}
/* Private Functions */
void Editor::Display() { m_TextBuffer.PrintBuffer(); }
