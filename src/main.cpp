#include "InsertChar.h"
#include "InsertNewline.h"
#include "TextBuffer.h"
#include "TextController.h"
#include <iostream>

int main() {
  TextController textController;
  TextBuffer tb;

  textController.Execute(new InsertChar(tb, 'H', {0, 0}));
  textController.Execute(new InsertChar(tb, 'H', {0, 0}));
  textController.Execute(new InsertChar(tb, 'e', {0, 1}));
  textController.Execute(new InsertChar(tb, 'l', {0, 2}));
  textController.Execute(new InsertChar(tb, 'l', {0, 3}));
  textController.Execute(new InsertChar(tb, 'o', {0, 4}));
  textController.Execute(new InsertChar(tb, ' ', {0, 5}));
  textController.Execute(new InsertChar(tb, 'W', {0, 6}));
  textController.Execute(new InsertChar(tb, 'o', {0, 7}));
  textController.Execute(new InsertChar(tb, 'r', {0, 8}));
  textController.Execute(new InsertChar(tb, 'l', {0, 9}));
  textController.Execute(new InsertChar(tb, 'd', {0, 10}));
  textController.Execute(new InsertNewline(tb, {0, 11}));
  textController.Execute(new InsertChar(tb, 'S', {1, 0}));
  textController.Execute(new InsertChar(tb, 't', {1, 1}));
  textController.Execute(new InsertChar(tb, 'r', {1, 2}));
  textController.Execute(new InsertChar(tb, 'i', {1, 3}));
  textController.Execute(new InsertChar(tb, 'n', {1, 4}));
  textController.Execute(new InsertChar(tb, 'g', {1, 5}));
  textController.Execute(new InsertNewline(tb, {1, 6}));

  std::cout << "Printing: \n";
  std::cout << tb.GetLineAtOffset(3);
  tb.GetLineAtOffset(3);
  // tb.PrintBuffer();
  //
  // std::cout << "After undo:" << std::endl;
  // for (int i = 0; i < 18; i++) {
  //   textController.Undo();
  //   tb.PrintBuffer();
  // }
  //
  // std::cout << "After Redo:" << std::endl;
  // for (int i = 0; i < 5; i++) {
  //   textController.Redo();
  //   tb.PrintBuffer();
  // }
}
