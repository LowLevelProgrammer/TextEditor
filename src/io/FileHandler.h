#pragma once

#include "TextBuffer.h"
#include <fstream>
#include <string>
class FileHandler {
public:
  FileHandler();
  ~FileHandler();

  void CreateFile(std::string filePath);
  void OpenFile(std::string filePath);
  TextBuffer ReadFromFile();
  void WriteToFile(const TextBuffer &textBuffer);
  void CloseFile();

  void SetFilePath(std::string filePath);
  inline bool GetIsOpen() { return m_IsOpen; }

private:
  // File path includes file name
  std::string m_FilePath;
  std::fstream m_FileStream;
  bool m_IsOpen = false;
};
