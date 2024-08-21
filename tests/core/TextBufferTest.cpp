#include "TextBuffer.h"
#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>

class TextBufferTest : public ::testing::Test {
protected:
  TextBuffer tb;

  void SetUp() override {
    tb.InsertChar('H', {0, 0});
    tb.InsertChar('e', {0, 1});
    tb.InsertChar('l', {0, 2});
    tb.InsertChar('l', {0, 3});
    tb.InsertChar('o', {0, 4});
  }
};

TEST_F(TextBufferTest, InsertChar) {
  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello");

  tb.InsertChar(' ', {0, 5});
  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello ");

  tb.InsertChar('W', {0, 6});
  tb.InsertChar('o', {0, 7});
  tb.InsertChar('r', {0, 8});
  tb.InsertChar('l', {0, 9});
  tb.InsertChar('d', {0, 10});

  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello World");
  EXPECT_EQ(tb.GetPrintableTextBuffer(), "Hello World");
}

TEST_F(TextBufferTest, InsertNewline) {
  tb.InsertNewline({0, 5});

  EXPECT_EQ(tb.GetLineCount(), 2);
  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello");
  EXPECT_EQ(tb.GetLineAtOffset(1), "");
  EXPECT_EQ(tb.GetPrintableTextBuffer(), "Hello\n");
}

TEST_F(TextBufferTest, InsertCharAtSecondLine) {
  tb.InsertNewline({0, 5});

  tb.InsertChar('W', {1, 0});
  tb.InsertChar('o', {1, 1});
  tb.InsertChar('r', {1, 2});
  tb.InsertChar('l', {1, 3});
  tb.InsertChar('d', {1, 4});

  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello");
  EXPECT_EQ(tb.GetLineAtOffset(1), "World");
  EXPECT_EQ(tb.GetPrintableTextBuffer(), "Hello\nWorld");
}

TEST_F(TextBufferTest, InsertCharOutOfBounds) {
  ASSERT_DEATH(tb.InsertChar('W', {0, 6}),
               "Offset not within or at the edge of the bounds");
}

TEST_F(TextBufferTest, InsertCharOutOfBounds2) {
  ASSERT_DEATH(tb.InsertChar('W', {1, 0}),
               "Offset not within or at the edge of the bounds");
}

TEST_F(TextBufferTest, InsertNewlineOutOfBounds) {
  ASSERT_DEATH(tb.InsertNewline({0, 6}),
               "Offset not within or at the edge of the bounds");
}

TEST_F(TextBufferTest, InsertNewlineOutOfBounds2) {
  ASSERT_DEATH(tb.InsertNewline({1, 0}),
               "Offset not within or at the edge of the bounds");
}

TEST_F(TextBufferTest, EraseCharTest) {
  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello");

  tb.EraseChar({0, 4});
  EXPECT_EQ(tb.GetLineAtOffset(0), "Hell");
  tb.EraseChar({0, 3});
  tb.EraseChar({0, 2});
  tb.EraseChar({0, 1});
  tb.EraseChar({0, 0});

  EXPECT_EQ(tb.GetLineAtOffset(0), "");
  EXPECT_EQ(tb.GetPrintableTextBuffer(), "");
}

TEST_F(TextBufferTest, EraseCharTest2) {
  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello");

  tb.EraseChar({0, 0});
  EXPECT_EQ(tb.GetLineAtOffset(0), "ello");
  tb.EraseChar({0, 0});
  tb.EraseChar({0, 0});
  tb.EraseChar({0, 0});
  tb.EraseChar({0, 0});

  EXPECT_EQ(tb.GetLineAtOffset(0), "");
  EXPECT_EQ(tb.GetPrintableTextBuffer(), "");

  ASSERT_DEATH(tb.EraseChar({0, 0}), "Offset not within bounds");
}

TEST_F(TextBufferTest, EraseOutOfBounds) {
  EXPECT_DEATH(tb.EraseChar({0, 5}), "Offset not within bounds");
  EXPECT_DEATH(tb.EraseChar({0, -1}), "Offset not within bounds");
}
