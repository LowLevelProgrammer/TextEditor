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
}

TEST_F(TextBufferTest, InsertOutOfBounds) {
  ASSERT_DEATH(tb.InsertChar('W', {0, 6}), "Assertion.*failed");
}

TEST_F(TextBufferTest, EraseCharTest) {
  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello");

  tb.EraseChar({0, 4});
  tb.EraseChar({0, 3});
  tb.EraseChar({0, 2});
  tb.EraseChar({0, 1});
  tb.EraseChar({0, 0});

  EXPECT_EQ(tb.GetLineAtOffset(0), "");
}

TEST_F(TextBufferTest, EraseCharTest2) {
  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello");

  tb.EraseChar({0, 0});
  tb.EraseChar({0, 0});
  tb.EraseChar({0, 0});
  tb.EraseChar({0, 0});
  tb.EraseChar({0, 0});

  EXPECT_EQ(tb.GetLineAtOffset(0), "");
  ASSERT_DEATH(tb.EraseChar({0, 0}), "Assertion.*failed");
}

TEST_F(TextBufferTest, EraseOutOfBounds) {
  ASSERT_DEATH(tb.EraseChar({0, 5}), "Assertion.*failed");
}
