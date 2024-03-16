#include "TextBuffer.h"
#include "utilities.h"
#include <string>

int main() {
  // Editor editor;
  // editor.Run();

  TextBuffer tb;
  tb.InsertLine("Hello, World!");
  tb.InsertLine("I'm Akash");
  tb.InsertLine("Random string");
  tb.InsertLine("I don't know");

  tb.Select({1, 4}, {3, 8});
  tb.DeleteSelection();

  tb.PrintBuffer();

  return 0;
}
