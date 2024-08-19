#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>

#include "TextController.h"

#include "EraseChar.h"
#include "InsertChar.h"
#include "InsertNewline.h"
#include "TextBuffer.h"
#include "TextController.h"

class TextControllerTest : public ::testing::Test {
protected:
  TextController textController;
  TextBuffer tb;

  void SetUp() override {
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
  }
};

TEST_F(TextControllerTest, InsertCharCommandTest) {
  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello World");
  EXPECT_EQ(tb.GetCharAtOffset({0, 10}), 'd');

  EXPECT_DEATH(tb.GetCharAtOffset({0, 11}), "Offset not within bounds");
  EXPECT_DEATH(tb.GetCharAtOffset({1, 0}), "Offset not within bounds");
}

TEST_F(TextControllerTest, InsertNewLineCommandTest) {
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

TEST_F(TextControllerTest, EraseCharCommandTest) {
  textController.Execute(new EraseChar(tb, {0, 10}));
  textController.Execute(new EraseChar(tb, {0, 9}));
  textController.Execute(new EraseChar(tb, {0, 8}));
  textController.Execute(new EraseChar(tb, {0, 7}));
  textController.Execute(new EraseChar(tb, {0, 6}));
  textController.Execute(new EraseChar(tb, {0, 5}));
  textController.Execute(new EraseChar(tb, {0, 4}));
  textController.Execute(new EraseChar(tb, {0, 3}));
  textController.Execute(new EraseChar(tb, {0, 2}));
  textController.Execute(new EraseChar(tb, {0, 1}));
  textController.Execute(new EraseChar(tb, {0, 0}));

  EXPECT_EQ(tb.GetLineAtOffset(0), "");
  EXPECT_EQ(tb.GetPrintableTextBuffer(), "");
  ASSERT_DEATH(textController.Execute(new EraseChar(tb, {0, -1})),
               "Assertion.*failed");
}

TEST_F(TextControllerTest, EraseCharCommandTest2) {
  textController.Execute(new EraseChar(tb, {0, 0}));
  textController.Execute(new EraseChar(tb, {0, 0}));
  textController.Execute(new EraseChar(tb, {0, 0}));
  textController.Execute(new EraseChar(tb, {0, 0}));
  textController.Execute(new EraseChar(tb, {0, 0}));
  textController.Execute(new EraseChar(tb, {0, 0}));
  textController.Execute(new EraseChar(tb, {0, 0}));
  textController.Execute(new EraseChar(tb, {0, 0}));
  textController.Execute(new EraseChar(tb, {0, 0}));
  textController.Execute(new EraseChar(tb, {0, 0}));
  textController.Execute(new EraseChar(tb, {0, 0}));

  EXPECT_EQ(tb.GetLineAtOffset(0), "");
  EXPECT_EQ(tb.GetPrintableTextBuffer(), "");
  EXPECT_DEATH(tb.GetLineAtOffset(1), "Line offset not within bounds");

  EXPECT_DEATH(textController.Execute(new EraseChar(tb, {0, 0})),
               "Offset not within bounds");
  EXPECT_EQ(tb.GetPrintableTextBuffer(), "");
  EXPECT_DEATH(textController.Execute(new EraseChar(tb, {0, 0})),
               "Offset not within bounds");
  EXPECT_DEATH(textController.Execute(new EraseChar(tb, {0, -1})),
               "Offset not within bounds");
}

TEST_F(TextControllerTest, EraseCharCommandTest3) {
  EXPECT_DEATH(textController.Execute(new EraseChar(tb, {0, -1})),
               "Offset not within bounds");
  EXPECT_DEATH(textController.Execute(new EraseChar(tb, {0, 11})),
               "Offset not within bounds");
}

TEST_F(TextControllerTest, InsertAtSecondLine) {
  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello World");

  textController.Execute(new InsertNewline(tb, {0, 11}));

  textController.Execute(new InsertChar(tb, 'R', {1, 0}));
  textController.Execute(new InsertChar(tb, 'a', {1, 1}));
  textController.Execute(new InsertChar(tb, 'n', {1, 2}));
  textController.Execute(new InsertChar(tb, 'd', {1, 3}));
  textController.Execute(new InsertChar(tb, 'o', {1, 4}));
  textController.Execute(new InsertChar(tb, 'm', {1, 5}));
  textController.Execute(new InsertChar(tb, ' ', {1, 6}));
  textController.Execute(new InsertChar(tb, 'S', {1, 7}));
  textController.Execute(new InsertChar(tb, 't', {1, 8}));
  textController.Execute(new InsertChar(tb, 'r', {1, 9}));
  textController.Execute(new InsertChar(tb, 'i', {1, 10}));
  textController.Execute(new InsertChar(tb, 'n', {1, 11}));
  textController.Execute(new InsertChar(tb, 'g', {1, 12}));

  EXPECT_EQ(tb.GetNumberOfLines(), 2);
  EXPECT_EQ(tb.GetLineAtOffset(1), "Random String");
  EXPECT_EQ(tb.GetPrintableTextBuffer(), "Hello World\nRandom String");
  EXPECT_EQ(tb.GetCharAtOffset({1, 12}), 'g');
  EXPECT_DEATH(tb.GetCharAtOffset({1, 13}), "Offset not within bounds");
  EXPECT_DEATH(tb.GetCharAtOffset({1, -1}), "Offset not within bounds");
  EXPECT_DEATH(tb.GetCharAtOffset({2, 0}), "Offset not within bounds");
  EXPECT_DEATH(tb.GetLineAtOffset(2), "Line offset not within bounds");
}

TEST_F(TextControllerTest, UndoSingleInsertChar) {
  // Initial state should be "Hello World"
  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello World");

  // Undo the last insert ("d")
  textController.Undo();

  // Now the state should be "Hello Worl"
  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello Worl");
}

TEST_F(TextControllerTest, UndoMultipleInsertChars) {
  // Initial state should be "Hello World"
  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello World");

  // Undo the last two inserts ("d" and "l")
  textController.Undo();
  textController.Undo();

  // Now the state should be "Hello Wor"
  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello Wor");
}

TEST_F(TextControllerTest, UndoAfterEraseChar) {
  // Initial state should be "Hello World"
  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello World");

  // Erase the last character ("d")
  textController.Execute(new EraseChar(tb, {0, 10}));

  // Now the state should be "Hello Worl"
  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello Worl");

  // Undo the erase
  textController.Undo();

  // The state should be back to "Hello World"
  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello World");

  // Undo the initial insert
  textController.Undo();

  // The state should be back to "Hello Worl"
  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello Worl");

  // Undo the initial insert
  textController.Undo();

  // The state should be back to "Hello Wor"
  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello Wor");
}

TEST_F(TextControllerTest, UndoMixedOperations) {
  // Initial state should be "Hello World"
  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello World");

  // Erase the last character ("d")
  textController.Execute(new EraseChar(tb, {0, 10}));
  // Insert "!"
  textController.Execute(new InsertChar(tb, '!', {0, 10}));

  // Now the state should be "Hello Worl!"
  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello Worl!");

  // Undo the insert ("!")
  textController.Undo();

  // The state should be back to "Hello Worl"
  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello Worl");

  // Undo the erase ("d")
  textController.Undo();

  // The state should be back to "Hello World"
  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello World");

  // Undo the insert ("d")
  textController.Undo();

  // The state should be back to "Hello Worl"
  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello Worl");

  // Undo the insert ("l")
  textController.Undo();

  // The state should be back to "Hello Wor"
  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello Wor");
}

TEST_F(TextControllerTest, UndoWithNoActions) {
  // Initial state should be "Hello World"
  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello World");

  // Perform a valid undo
  textController.Undo();

  // Now the state should be "Hello Worl"
  EXPECT_EQ(tb.GetLineAtOffset(0), "Hello Worl");

  // Try undoing multiple times
  textController.Undo(); // Undo "l"
  textController.Undo(); // Undo "r"
  textController.Undo(); // Undo "o"
  textController.Undo(); // Undo "W"
  textController.Undo(); // Undo space
  textController.Undo(); // Undo "o"
  textController.Undo(); // Undo "l"
  textController.Undo(); // Undo "l"
  textController.Undo(); // Undo "e"
  textController.Undo(); // Undo "H"
  textController.Undo(); // Should do nothing as the stack is empty

  // The state should be empty since all characters were undone
  EXPECT_EQ(tb.GetLineAtOffset(0), "");
}
