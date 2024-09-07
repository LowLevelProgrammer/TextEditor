#pragma once

#define ASSERT_WITHIN_BOUNDS(offset, lines)                                    \
  assert(offset.Y < lines.size() && offset.Y >= 0 &&                           \
         offset.X < lines[offset.Y].size() && offset.X >= 0 &&                 \
         "Offset not within bounds")

#define ASSERT_WITHIN_OR_EDGE_BOUNDS(offset, lines)                            \
  assert(offset.Y < lines.size() && offset.Y >= 0 &&                           \
         offset.X <= lines[offset.Y].size() && offset.X >= 0 &&                \
         "Offset not within or at the edge of the bounds")

#define ASSERT_WITHIN_LINE_BOUNDS(lineOffset, lines)                           \
  assert(lineOffset >= 0 && lineOffset < m_Lines.size() &&                     \
         "Line offset not within bounds");

#define ASSERT_NOT_EMPTY(vector)                                               \
  assert(!vector.empty() && "Vector should not be empty")
