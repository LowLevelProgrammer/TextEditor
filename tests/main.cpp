#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>

#include "InsertChar.h"
#include "InsertNewline.h"
#include "TextBuffer.h"
#include "TextController.h"

TEST(TextControllerTest, InsertCharCommandTest) {
  TextBuffer tb;
  TextController textController;

  textController.Execute(new InsertChar(tb, 'H', {0, 0}));
  textController.Execute(new InsertChar(tb, 'e', {0, 1}));
  textController.Execute(new InsertChar(tb, 'l', {0, 2}));
  textController.Execute(new InsertChar(tb, 'l', {0, 3}));
  textController.Execute(new InsertChar(tb, 'o', {0, 4}));
  textController.Execute(new InsertChar(tb, ' ', {0, 5}));
  textController.Execute(new InsertChar(tb, 'W', {0, 6}));
  textController.Execute(new InsertChar(tb, 'o', {0, 7}));
  textController.Execute(new InsertChar(tb, 'r', {0, 8}));
  textController.Execute(new InsertChar(tb, 'l', {0, 9}));
  textController.Execute(new InsertChar(tb, 'd', {0, 10}));

  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello World");
  EXPECT_EQ(tb.GetCharAtOffset({0, 10}), 'd');
  EXPECT_DEATH(tb.GetCharAtOffset({0, 11}), "");
  EXPECT_DEATH(tb.GetCharAtOffset({1, 0}), "");
}

TEST(TextControllerTest, InsertCharAndNewLineCommandTest) {
  TextBuffer tb;
  TextController textController;

  textController.Execute(new InsertChar(tb, 'H', {0, 0}));
  textController.Execute(new InsertChar(tb, 'e', {0, 1}));
  textController.Execute(new InsertChar(tb, 'l', {0, 2}));
  textController.Execute(new InsertChar(tb, 'l', {0, 3}));
  textController.Execute(new InsertChar(tb, 'o', {0, 4}));
  textController.Execute(new InsertChar(tb, ' ', {0, 5}));
  textController.Execute(new InsertChar(tb, 'W', {0, 6}));
  textController.Execute(new InsertChar(tb, 'o', {0, 7}));
  textController.Execute(new InsertChar(tb, 'r', {0, 8}));
  textController.Execute(new InsertChar(tb, 'l', {0, 9}));
  textController.Execute(new InsertChar(tb, 'd', {0, 10}));
  textController.Execute(new InsertNewline(tb, {0, 11}));
  textController.Execute(new InsertChar(tb, 'S', {1, 0}));
  textController.Execute(new InsertChar(tb, 't', {1, 1}));
  textController.Execute(new InsertChar(tb, 'r', {1, 2}));
  textController.Execute(new InsertChar(tb, 'i', {1, 3}));
  textController.Execute(new InsertChar(tb, 'n', {1, 4}));
  textController.Execute(new InsertChar(tb, 'g', {1, 5}));
  textController.Execute(new InsertNewline(tb, {1, 6}));
  textController.Execute(new InsertChar(tb, 'I', {2, 0}));

  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello World");
  EXPECT_EQ(tb.GetLineAtOffset(1), "String");
  EXPECT_EQ(tb.GetLineAtOffset(2), "I");
  EXPECT_DEATH(tb.GetLineAtOffset(3), "Assertion.*failed");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
