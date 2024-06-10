#include "FileHandler.h"
#include "TextBuffer.h"
#include <filesystem>
#include <iostream>
#include <string>

FileHandler::FileHandler() {}

FileHandler::~FileHandler() {}

void FileHandler::OpenFileForReading(std::string filePath) {

  if (IsFileExist(filePath)) {
    m_FilePath = filePath;
    m_FileStream.open(m_FilePath, std::ios::in);
  } else {
    std::cerr << "Error: File path does not exist" << std::endl;
  }
}

// To be used during saving
void FileHandler::OpenFileForWriting(std::string filePath) {
  m_FilePath = filePath;
  m_FileStream.open(m_FilePath, std::ios::out | std::ios::trunc);
}

TextBuffer FileHandler::ReadFromFile() {
  TextBuffer tb;
  // TODO: Find a better way to handle new text buffers instead of manually
  // having to call the clear function to remove the initial empty line
  tb.Clear();
  if (m_FilePath.empty()) {
    std::cerr << "Error: No file is opened" << std::endl;
  } else {
    std::string line;
    while (std::getline(m_FileStream, line)) {
      tb.InsertLine(line);
    }
  }
  tb.SetCaretPosition(tb.GetEOFPosition());
  return tb;
}

void FileHandler::WriteToFile(const TextBuffer &textBuffer) {
  const std::vector<std::string> &lines = textBuffer.GetLines();
  for (int i = 0; i < lines.size(); i++) {
    m_FileStream << lines[i];
    if (i != lines.size() - 1) {
      m_FileStream << '\n';
    }
  }
  m_FileStream.flush();
}

TextBuffer FileHandler::Open(std::string filePath) {
  OpenFileForReading(filePath);
  // TODO: Optimize copying this text buffer
  TextBuffer tb = ReadFromFile();
  CloseFile();
  return tb;
}

void FileHandler::SaveAs(const TextBuffer &textBuffer, std::string filePath) {
  OpenFileForWriting(filePath);
  WriteToFile(textBuffer);
  CloseFile();
}

bool FileHandler::IsOpen() { return !m_FilePath.empty(); }

bool FileHandler::IsFileExist(std::string filePath) {
  std::filesystem::path path(filePath);
  if (std::filesystem::exists(filePath)) {
    return true;
  } else {
    return false;
  }
}

void FileHandler::CloseFile() {
  if (m_FileStream.is_open()) {
    m_FileStream.close();
  } else {
    std::cerr << "Error: No file to close" << std::endl;
  }
}
