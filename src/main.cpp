#include "Register.h"
#include "TextBuffer.h"
#include "utilities.h"
#include <iostream>
#include <string>

int main() {
  // Editor editor;
  // editor.Run();

  TextBuffer tb;
  tb.InsertLine("Hello, World!");
  tb.InsertLine("I'm Akash");
  tb.InsertLine("Random string");
  tb.InsertLine("This is another test string");

  tb.PrintBuffer();

  std::cout << "------------------------\n";

  tb.Select({2, 6}, {3, 9});
  // tb.Backspace();

  Register reg(1);
  reg.Insert(tb.GetSelectedText());
  std::cout << reg.GetBuffer();

  std::cout << "\n------------------------\n";

  tb.SetCaretPosition(4, 4);

  tb.InsertBuffer(reg);

  tb.PrintBuffer();
  // std::cout << reg.GetBuffer();

  return 0;
}
