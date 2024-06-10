#pragma once

#include "TextBuffer.h"
#include <fstream>
#include <string>
class FileHandler {
public:
  FileHandler();
  ~FileHandler();

  TextBuffer Open(std::string filePath);
  void SaveAs(const TextBuffer &textBuffer, std::string filePath);
  void SetFilePath(std::string filePath);
  bool IsOpen();
  bool IsFileExist(std::string filePath);
  void CloseFile();

  inline std::string GetFilePath() { return m_FilePath; }

private:
  // File path includes file name
  std::string m_FilePath;
  std::fstream m_FileStream;

private:
  void OpenFileForReading(std::string filePath);
  void OpenFileForWriting(std::string filePath);
  TextBuffer ReadFromFile();
  void WriteToFile(const TextBuffer &textBuffer);
};
