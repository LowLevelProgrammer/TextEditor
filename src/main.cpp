#include <iostream>
#include <string>

#include "TextBuffer.h"
#include "utilities.h"

int main() {
  TextBuffer tb;

  InsertLine(tb, "Hello, World!");
  tb.InsertChar('\n');
  InsertLine(tb, "I'm  Akash");
  InsertLine(tb, "Random string");
  tb.InsertChar('\n');
  tb.InsertChar('\n');
  InsertLine(tb, "This is another test string");
  InsertLineWithoutNewlineCharacter(tb, "Yet another line");

  std::cout << "Original Text:-" << std::endl;
  PrintLines(tb.GetLines());

  std::cout << "------------------------\n";
  const Position &caret = tb.GetCaretPosition();

  tb.Undo();
  tb.Undo();
  tb.Undo();
  tb.Undo();
  tb.Undo();
  tb.Undo();
  tb.Undo();
  tb.Undo();
  tb.Undo();
  tb.Undo();
  tb.Undo();
  tb.Undo();
  tb.Undo();
  tb.Undo();
  tb.Undo();
  std::cout << "After Undo:-" << std::endl;
  PrintLines(tb.GetLines());

  std::cout << "------------------------\n";
  tb.Redo();
  std::cout << "After Redo:-" << std::endl;
  PrintLines(tb.GetLines());
  std::cout << "------------------------\n";
  std::cout << "Num elements in undo stack: " << tb.GetNumElementsUndoStack()
            << std::endl;
  std::cout << "Num elements in redo stack: " << tb.GetNumElementsRedoStack()
            << std::endl;

  return 0;
}
