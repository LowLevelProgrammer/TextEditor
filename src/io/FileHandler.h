#pragma once

#include "TextBuffer.h"
#include <fstream>
#include <string>
#include <vector>
class FileHandler {
public:
  FileHandler(std::string filePath);
  ~FileHandler();

  bool CreateFile(std::string fileName);
  bool OpenFile(std::string fileName);
  std::vector<std::string> ReadFromFile();
  void WriteToFile(const TextBuffer &textBuffer);
  bool CloseFile();

private:
  std::string m_FilePath;
  std::fstream m_FileStream;
  bool m_IsOpen = false;
};
