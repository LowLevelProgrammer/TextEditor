#pragma once

#define ASSERT_WITHIIN_BOUNDS(offset, lines)                                   \
  assert(offset.Y < lines.size() && offset.Y >= 0 &&                           \
         offset.X < lines[offset.Y].size() && offset.X >= 0)

#define ASSERT_WITHIN_OR_EDGE_BOUNDS(offset, lines)                            \
  assert(offset.Y < lines.size() && offset.Y >= 0 &&                           \
         offset.X <= lines[offset.Y].size() && offset.X >= 0)

#define ASSERT_WITHIN_LINE_BOUNDS(lineOffset, lines)                           \
  assert(lineOffset >= 0 && lineOffset < m_Lines.size() &&                     \
         "Invalid line offset");
