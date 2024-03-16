#include "Register.h"

Register::Register() : m_Id(-1) {}

Register::Register(int id) : m_Id(id) {}

Register::~Register() {}

void Register::Insert(std::string content) { m_Buffer = content; }

std::string Register::Extract() { return m_Buffer; }

void Register::Clear() { m_Buffer.clear(); }
