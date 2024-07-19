#include "TextBuffer.h"
#include "utilities.h"

int main() {
  TextBuffer tb;
  InsertLine(tb, "Hello, World!");
  InsertLineWithoutNewlineCharacter(tb, "I'm Akash");

  PrintUndoStack(tb.GetUndoStack());
}
