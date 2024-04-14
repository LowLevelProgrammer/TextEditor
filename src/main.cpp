#include <iostream>
#include <string>

#include "Editor.h"

int main() {
  Editor editor;
  // editor.Run();

  editor.InsertLine("Hello, World!");
  editor.InsertLine("I'm Akash");
  editor.InsertLine("Random string");
  editor.InsertLine("This is another test string");
  editor.InsertLine("Yet another line");

  editor.Display();

  std::cout << "------------------------\n";

  editor.Select({2, 6}, {3, 9});
  // tb.Select({2, 6}, {3, 9});
  editor.BackSpace();
  // tb.Backspace();

  // Register reg(1);
  // reg.Insert(tb.GetSelectedText());
  // std::cout << reg.GetBuffer();

  std::cout << "\n------------------------\n";

  // tb.SetCaretPosition(4, 4);

  // tb.InsertBuffer(reg);

  editor.Display();
  // tb.PrintBuffer();
  // std::cout << reg.GetBuffer();

  return 0;
}
