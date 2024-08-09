#ifndef CUSTOM_ASSERT_H
#define CUSTOM_ASSERT_H

#include <cassert>
#include <string>

inline const std::string SENTINEL_STRING = "<invalid_sentinel>";

#ifdef TESTING
#define ASSERT_OR_RETURN(condition)                                            \
  if (!(condition)) {                                                          \
    return SENTINEL_STRING;                                                    \
  }
#else
#define ASSERT_OR_RETURN(condition)                                            \
  assert(condition);

#endif // TESTING

#endif // !CUSTOM_ASSERT_H
