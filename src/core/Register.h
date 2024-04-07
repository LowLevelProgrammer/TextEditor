#pragma once

#include <string>
class Register {
public:
  Register();
  Register(int id);
  ~Register();

  void Insert(std::string content);
  std::string Extract();
  void Clear();

  inline std::string GetBuffer() { return m_Buffer; }

private:
  int m_Id;
  std::string m_Buffer;
};
