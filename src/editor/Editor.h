#pragma once

#include "FileHandler.h"
#include "Register.h"
#include "TextBuffer.h"
#include <string>
#include <vector>

class Editor {
public:
  Editor();
  ~Editor();

  void InsertChar(char character);
  void InsertLine(std::string line);
  void BackSpace();
  void Select(Position startPosition, Position endPosition);
  void Undo();
  void Redo();
  void SetCaretPosition(Position position);
  void Copy(int registerNumber);
  void Paste(int registerNumber);
  void OpenFile(std::string filePath);
  void Save();
  void SaveAs(std::string filePath);
  void Display();
  void MoveCaret(Direction direction);
  bool IsFileOpen();
  std::string GetFilePath();

  inline const Position &GetCaretPosition() const {
    return m_TextBuffer.GetCaretPosition();
  }

  inline const std::vector<std::string> &GetTextBuffer() const {
    return m_TextBuffer.GetLines();
  }

  inline const std::vector<Transaction> &GetUndoStack() const {
    return m_TextBuffer.GetUndoStack();
  }

private:
  void HandleInput();

private:
  TextBuffer m_TextBuffer;
  // Registers are 0-Indexed
  Register *m_Register;
  FileHandler m_FileHandler;
};
