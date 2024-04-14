#include "FileHandler.h"
#include "TextBuffer.h"
#include <filesystem>
#include <iostream>
#include <string>

FileHandler::FileHandler() : m_IsOpen(false) {}

FileHandler::~FileHandler() {}

void FileHandler::CreateFile(std::string p_FilePath) {
  m_FilePath = p_FilePath;
  // Check if the file already exists
  std::filesystem::path filePath(m_FilePath);
  if (std::filesystem::exists(filePath)) {
    std::cerr << "Error: File already exists" << std::endl;
    m_IsOpen = false;
    return;
  }
  // TODO: Add feature to overwrite file if user chooses so
  m_FileStream.open(m_FilePath, std::ios::out);
  if (!m_FileStream.is_open()) {
    std::cerr << "Error: Creating the file" << std::endl;
    m_IsOpen = false;
  } else
    m_IsOpen = true;
}

void FileHandler::OpenFile(std::string p_FilePath) {
  // Check if file exists
  std::filesystem::path filePath(m_FilePath);
  if (!std::filesystem::exists(filePath)) {
    std::cerr << "Error: File doesn't exist" << std::endl;
  }

  m_FileStream.open(filePath);

  if (!m_FileStream.is_open()) {
    std::cerr << "Error: Could not open the file" << std::endl;
    m_IsOpen = false;
  } else
    m_IsOpen = true;
}

TextBuffer FileHandler::ReadFromFile() {
  std::vector<std::string> lines;
  TextBuffer tb;
  if (m_IsOpen) {
    std::string line;
    while (std::getline(m_FileStream, line)) {
      tb.InsertLine(line);
    }
  } else {
    std::cerr << "Error: No file is opened" << std::endl;
  }
  return tb;
}

void FileHandler::WriteToFile(const TextBuffer &textBuffer) {
  if (m_IsOpen) {
    const std::vector<std::string> &lines = textBuffer.GetLines();
    for (int i = 0; i < lines.size(); i++) {
      m_FileStream << lines[i] << '\n';
    }
  } else
    std::cerr << "Error: No file is opened" << std::endl;
}

void FileHandler::CloseFile() {
  m_FileStream.close();
  if (m_FileStream.fail()) {
    std::cerr << "Error: Closing the file" << std::endl;
  }
}
