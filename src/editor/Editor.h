#pragma once

#include "Register.h"
#include "TextBuffer.h"

class Editor {
public:
  Editor();
  ~Editor();

  void Run();
  void Copy(int registerNumber);
  void Paste(int registerNumber);

private:
  void Display();
  void HandleInput();

private:
  TextBuffer m_TextBuffer;
  // Registers are 0-Indexed
  Register *m_Register;
};
