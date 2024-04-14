#pragma once

#include "FileHandler.h"
#include "Register.h"
#include "TextBuffer.h"
#include <string>

class Editor {
public:
  Editor();
  ~Editor();

  void Run();
  void InsertLine(std::string line);
  void BackSpace();
  void Select(Position startPosition, Position endPosition);
  void Undo();
  // TODO: Complete redo feature
  void Redo();
  void SetCaretPosition(Position position);
  void Copy(int registerNumber);
  void Paste(int registerNumber);
  void OpenFile(std::string filePath);
  void Save();
  void SaveAs(std::string filePath);
  void Display();

private:
  void HandleInput();

private:
  TextBuffer m_TextBuffer;
  // Registers are 0-Indexed
  Register *m_Register;
  FileHandler m_FileHandler;
};
