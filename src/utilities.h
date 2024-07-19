#pragma once

#include "TextBuffer.h"
#include <iostream>
#include <string>
#include <vector>

inline void PrintLines(const std::vector<std::string> &vec) {
  std::cout << std::endl;
  for (const auto &line : vec) {
    std::cout << line << std::endl;
  }
}

inline void InsertLine(TextBuffer &tb, const std::string &line) {
  for (const auto &ch : line) {
    tb.InsertChar(ch);
  }
  tb.InsertChar('\n');
}

inline void InsertLineWithoutNewlineCharacter(TextBuffer &tb,
                                              const std::string &line) {
  for (const auto &ch : line) {
    tb.InsertChar(ch);
  }
}

inline std::string GetPrintableString(char character) {
  if (character == '\n')
    return "\\n";
  else
    return std::string(1, character);
}

inline std::string GetOperationTypeString(OperationType type) {
  switch (type) {
  case OperationType::InsertChar:
    return "Add";
  case OperationType::RemoveChar:
    return "Remove";
  case OperationType::InsertNewLine:
    return "Newline";
  }
  std::cerr << "Invalid operation type" << std::endl;
  exit(-1);
}

inline void PrintTransaction(Transaction transaction) {
  int numOperations = transaction.Operations.size();
  std::cout << "Transaction Size: " << numOperations << std::endl;

  for (Operation operation : transaction.Operations) {
    std::cout << "{ " << GetOperationTypeString(operation.Type) << ", '"
              << GetPrintableString(operation.Character) << "', "
              << operation.YOffset << ", " << operation.XOffset << " }";
  }
  std::cout << std::endl;
}

inline void PrintUndoStack(const std::vector<Transaction> &undoStack) {
  std::cout << "Undo Stack:-" << std::endl;
  for (Transaction trnxn : undoStack) {
    PrintTransaction(trnxn);
  }
}

inline void PrintCaretPosition(const Position &position) {
  std::cout << "Caret Position: { " << position.Line << ", " << position.Column
            << " }" << std::endl;
}
