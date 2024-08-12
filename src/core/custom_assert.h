#pragma once

#define ASSERT_WITHIIN_BOUNDS(offset, lines)                                   \
  assert(offset.Y < lines.size() && offset.Y >= 0 &&                           \
         offset.X < lines[offset.Y].size() && offset.X >= 0)

#define ASSERT_INSERT_BOUNDS(offset, lines)                                    \
  assert(offset.Y < lines.size() && offset.Y >= 0 &&                           \
         offset.X <= lines[offset.Y].size() && offset.X >= 0)
