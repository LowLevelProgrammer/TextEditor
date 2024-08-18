#include "Editor.h"
#include "EraseChar.h"
#include "EraseNewline.h"
#include "InsertChar.h"
#include "InsertNewline.h"
#include "TextBuffer.h"

#include <string>
#include <sys/types.h>

Editor::Editor() : m_TextBuffer(), m_FileHandler() {
  m_Register = new Register[10];

  for (int i = 0; i < 10; i++) {
    m_Register[i] = Register(i);
  }
}

Editor::~Editor() { delete[] (m_Register); }

void Editor::InsertChar(char character) {
  Position caretPosition = m_TextBuffer.GetCaretPosition();
  Offset caretOffset = {caretPosition.Line - 1, caretPosition.Column - 1};

  switch (character) {
  case '\n':
    m_TextController.Execute(new InsertNewline(m_TextBuffer, caretOffset));
    m_TextBuffer.SetCaretPosition({caretPosition.Line + 1, 1});
    break;
  default:
    m_TextController.Execute(
        new ::InsertChar(m_TextBuffer, character, caretOffset));
    m_TextBuffer.SetCaretPosition(
        {caretPosition.Line, caretPosition.Column + 1});
    break;
  }
}

void Editor::BackSpace() {
  Position caretPosition = m_TextBuffer.GetCaretPosition();

  if (m_TextBuffer.IsSOF(caretPosition))
    return;

  if (m_TextBuffer.IsStartOfLine(caretPosition)) {
    int currentLineYOffset = caretPosition.Line - 1;
    int prevLineYOffset = currentLineYOffset - 1;
    int prevLineSize = m_TextBuffer.GetLineSizeAtOffset(prevLineYOffset);

    Offset newlineCharOffset = {prevLineYOffset, prevLineSize};

    m_TextController.Execute(new EraseNewline(m_TextBuffer, newlineCharOffset));
    m_TextBuffer.SetCaretPosition({caretPosition.Line - 1, prevLineSize + 1});

  } else {
    Offset charToRemoveOffset = {caretPosition.Line - 1,
                                 caretPosition.Column - 2};
    m_TextController.Execute(new EraseChar(m_TextBuffer, charToRemoveOffset));
    m_TextBuffer.SetCaretPosition(
        {caretPosition.Line, caretPosition.Column - 1});
  }
}

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
