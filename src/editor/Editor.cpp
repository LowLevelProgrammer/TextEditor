#include "Editor.h"
#include "Register.h"

#include <iostream>
#include <string>

Editor::Editor() {
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

  m_TextBuffer.Delete();
  m_TextBuffer.Delete();
  m_TextBuffer.Delete();
  std::cout << "Text in the buffer\n";

  Display();
}

void Editor::Copy(int registerNumber) {
  if (m_TextBuffer.SelectionActive()) {
    m_Register[registerNumber].Insert(m_TextBuffer.GetSelectedText());
  }
}

void Editor::Paste(int registerNumber) {
  if (m_TextBuffer.SelectionActive()) {

  } else {
  }
}

void Editor::Display() { m_TextBuffer.PrintBuffer(); }
