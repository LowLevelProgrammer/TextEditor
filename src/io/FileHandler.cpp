#include "FileHandler.h"
#include <filesystem>
#include <iostream>
#include <string>

FileHandler::FileHandler(std::string filePath) : m_FilePath(filePath) {}

FileHandler::~FileHandler() {}

bool FileHandler::CreateFile(std::string fileName) {
  std::filesystem::path filePath(m_FilePath + fileName);
  // TODO: Add feature to overwrite file if user chooses so
  if (std::filesystem::exists(filePath)) {
    std::cerr << "Error: File already exists" << std::endl;
    m_IsOpen = false;
    return m_IsOpen;
  }
  m_FileStream.open(m_FilePath + fileName, std::ios::out);
  if (!m_FileStream.is_open()) {
    std::cerr << "Error: Creating the file" << std::endl;
    m_IsOpen = false;
  } else
    m_IsOpen = true;
  return m_IsOpen;
}

bool FileHandler::OpenFile(std::string fileName) {
  std::filesystem::path filePath(m_FilePath + fileName);
  if (!std::filesystem::exists(filePath)) {
    std::cerr << "Error: File doesn't exist" << std::endl;
  }

  m_FileStream.open(filePath);

  if (!m_FileStream.is_open()) {
    std::cerr << "Error: Could not open the file" << std::endl;
    m_IsOpen = false;
  }
  m_IsOpen = true;

  return m_IsOpen;
}

std::vector<std::string> FileHandler::ReadFromFile() {
  std::vector<std::string> lines;
  if (m_IsOpen) {
    std::string line;
    while (std::getline(m_FileStream, line)) {
      lines.push_back(line);
    }
  } else {
    std::cerr << "Error: No file is opened" << std::endl;
  }
  return lines;
}

void FileHandler::WriteToFile(const TextBuffer &textBuffer) {
  const std::vector<std::string> &lines = textBuffer.GetLines();
  if (m_IsOpen) {
    for (int i = 0; i < lines.size(); i++) {
      m_FileStream << lines[i] << '\n';
    }
  } else
    std::cerr << "Error: No file is opened" << std::endl;
}

bool FileHandler::CloseFile() {
  m_FileStream.close();
  if (m_FileStream.fail()) {
    std::cerr << "Error: Closing the file" << std::endl;
    return false;
  }
  return true;
}
