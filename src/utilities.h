#pragma once

#include "Command.h"
#include "TextBuffer.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

inline void PrintLines(const std::vector<std::string> &vec) {
  std::cout << std::endl;
  for (const auto &line : vec) {
    std::cout << line << std::endl;
  }
}

inline void InsertLine(TextBuffer &tb, const std::string &line) {
  // for (const auto &ch : line) {
  //   tb.AddCharAtCaret(ch);
  // }
  // tb.AddCharAtCaret('\n');
}

inline void InsertLineWithoutNewlineCharacter(TextBuffer &tb,
                                              const std::string &line) {
  // for (const auto &ch : line) {
  //   tb.AddCharAtCaret(ch);
  // }
}

inline std::string GetPrintableString(char character) {
  if (character == '\n')
    return "\\n";
  else
    return std::string(1, character);
}

inline std::string GetCommandTypeString(OperationType type) {
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

// inline std::string GetTransactionString(Transaction transaction) {
//   int numOperations = transaction.Operations.size();
//   std::stringstream ss;
//   ss << "Transaction Size: " << numOperations << std::endl;
//
//   for (Operation operation : transaction.Operations) {
//     ss << "{ " << GetOperationTypeString(operation.Type) << ", '"
//        << GetPrintableString(operation.Character) << "', " <<
//        operation.YOffset
//        << ", " << operation.XOffset << " }";
//   }
//   ss << std::endl;
//   return ss.str();
// }
//
// inline void PrintTransaction(Transaction transaction) {
//   int numOperations = transaction.Operations.size();
//   std::cout << "Transaction Size: " << numOperations << std::endl;
//
//   for (Operation operation : transaction.Operations) {
//     std::cout << "{ " << GetOperationTypeString(operation.Type) << ", '"
//               << GetPrintableString(operation.Character) << "', "
//               << operation.YOffset << ", " << operation.XOffset << " }";
//   }
//   std::cout << std::endl;
// }

// inline std::string
// GetUndoStackString(const std::vector<Transaction> &undoStack) {
//   std::stringstream ss;
//   ss << "Undo Stack:-" << std::endl;
//   for (Transaction trnxn : undoStack) {
//     ss << GetTransactionString(trnxn);
//   }
//   return ss.str();
// }

inline std::string GetUndoStackString(const std::vector<Command *> &undoStack) {
  std::stringstream ss;
  ss << "Undo Stack:-" << std::endl;
  for (Command *cmd : undoStack) {
    if (cmd == nullptr) {
      ss << "Break point" << std::endl;
      continue;
    }
    ss << cmd->TransactionDetails();
  }
  return ss.str();
}

inline void PrintCaretPosition(const Position &position) {
  std::cout << "Caret Position: { " << position.Line << ", " << position.Column
            << " }" << std::endl;
}
