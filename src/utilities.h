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

inline std::string GetActionTypeString(ActionType actionType) {
  switch (actionType) {
  case ActionType::Copy:
    return "Copy";
  case ActionType::Paste:
    return "Paste";
  case ActionType::Insert:
    return "Insert";
  case ActionType::Delete:
    return "Delete";
  default:
    return "";
  }
}

inline std::string GetPrintableString(std::string content) {
  std::string str;
  for (auto ch : content) {
    if (ch == '\n')
      str.append("\\n");
    else if (ch == ' ')
      str.append("_");
    else
      str.push_back(ch);
  }
  return str;
}

inline void PrintHistory(const std::vector<Action> &history) {
  for (const auto &ele : history) {
    std::string printableString = GetPrintableString(ele.Content);
    std::cout << GetActionTypeString(ele.Type) << " \"" << printableString
              << "\" { " << ele.PositionStart.Line << ", "
              << ele.PositionStart.Column << " }, { " << ele.PositionEnd.Line
              << ", " << ele.PositionEnd.Column << " }" << std::endl;
  }
}

inline void PrintCaretPosition(const Position &position) {
  std::cout << "Caret Position: { " << position.Line << ", " << position.Column
            << " }" << std::endl;
}
