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
  InsertLine(tb, "Yet another line");
  tb.InsertChar('w');
  tb.InsertChar('o');
  tb.InsertChar('r');
  tb.InsertChar('d');
  tb.Backspace();

  PrintLines(tb.GetLines());

  std::cout << "------------------------\n";
  const Position &caret = tb.GetCaretPosition();

  // std::cout << caret.Line << " " << caret.Column;
  // tb.SetCaretPosition({6, 3});
  // tb.Backspace();

  // tb.Select({2, 6}, {3, 9});
  // tb.Backspace();

  // Register reg(1);
  // reg.Insert(tb.GetSelectedText());
  // std::cout << reg.GetBuffer();

  // PrintLines(tb.GetLines());
  PrintHistory(tb.GetHistory());
  std::cout << "\n------------------------\n";

  // tb.SetCaretPosition(4, 4);

  // tb.InsertBuffer(reg);

  // editor.Display();
  // tb.PrintBuffer();
  // std::cout << reg.GetBuffer();

  return 0;
}
