#include <gtest/gtest.h>

#include "Command.h"
#include "Editor.h"

class EditorTest : public ::testing::Test {
protected:
  Editor editor;

  void SetUp() override {
    editor.InsertChar('H');
    editor.InsertChar('e');
    editor.InsertChar('l');
    editor.InsertChar('l');
    editor.InsertChar('o');
  }

  void TearDown() override {}
};

TEST_F(EditorTest, UndoUntilLastSpace) {
  editor.InsertChar(' ');
  editor.InsertChar('W');
  editor.InsertChar('o');
  editor.InsertChar('r');
  editor.InsertChar('l');
  editor.InsertChar('d');
  editor.Undo();

  EXPECT_EQ(editor.GetText(), "Hello");
}

TEST_F(EditorTest, UndoUntilLastNewline) {
  editor.InsertChar('\n');
  editor.InsertChar('W');
  editor.InsertChar('o');
  editor.InsertChar('r');
  editor.InsertChar('l');
  editor.InsertChar('d');
  editor.Undo();

  EXPECT_EQ(editor.GetText(), "Hello");
}

TEST_F(EditorTest, UndoSingleCharacterErasure) {
  editor.BackSpace();
  editor.Undo();

  EXPECT_EQ(editor.GetText(), "Hello");
}

TEST_F(EditorTest, UndoPreservesTheBreakpoint) {
  editor.InsertChar('\n');
  editor.InsertChar('W');
  editor.InsertChar('o');
  editor.InsertChar('r');
  editor.InsertChar('l');
  editor.InsertChar('d');
  /*  Breakpoint here
   *      |
   *      v
   * Hello
   * World
   */
  editor.Undo();
  /* After undo:
   * TB =
   * Breakpoint here
   *      |
   *      v
   * Hello
   */

  editor.InsertChar('A');
  editor.InsertChar('k');
  editor.InsertChar('a');
  editor.InsertChar('s');
  editor.InsertChar('h');
  /* After undo:
   * TB =
   * Breakpoint here
   *      |
   *      v
   * HelloAkash
   */

  editor.Undo();

  /* After undo it should be:
   * Breakpoint here
   *      |
   *      v
   * Hello
   *
   * It(text buffer) shouldn't be empty i.e. undoing shouldn't erase the
   * breakpoint and group up the recently typed word with the word typed before
   * undo
   *
   * i.e. No breakpoint present between the two word
   * TB = HelloAkash
   */

  EXPECT_EQ(editor.GetText(), "Hello");

  editor.Undo();
  EXPECT_EQ(editor.GetText(), "");
}

TEST_F(EditorTest, InsertsShouldntGroupWithLastRemoveCommand) {
  editor.BackSpace();
  editor.BackSpace();
  editor.BackSpace();
  editor.BackSpace();
  editor.BackSpace();
  /*
   * TB:
   * ""
   */
  editor.InsertChar('A');
  editor.InsertChar('k');
  editor.InsertChar('a');
  editor.InsertChar('s');
  editor.InsertChar('h');
  /*
   * TB:
   * Akash
   */

  editor.Undo();
  /*
   * Undo should revert the insertion of the word "Akash"
   * After undo it should be like this:
   * TB:
   * ""
   * It shouldn't group up with the last erasure of the letter 'H'
   * And it should not be like this:
   * TB:
   * H
   *
   * i.e. the undo stack should be like this:
   *  │Break point
   *  │Remove char 'H' at offset { 0, 0 }
   *  │Break point   <== This Breakpoint is required
   *  │Add char 'A' at offset { 0, 0 }
   *  │Add char 'k' at offset { 0, 1 }
   *  │Add char 'a' at offset { 0, 2 }
   *  │Add char 's' at offset { 0, 3 }
   *  │Add char 'h' at offset { 0, 4 }
   *
   *  And not like this:
   *  │Break point
   *  │Remove char 'H' at offset { 0, 0 }   /________ Breakpoint not present
   *  │Add char 'A' at offset { 0, 0 }      \
   *  │Add char 'k' at offset { 0, 1 }
   *  │Add char 'a' at offset { 0, 2 }
   *  │Add char 's' at offset { 0, 3 }
   *  │Add char 'h' at offset { 0, 4 }
   */

  EXPECT_EQ(editor.GetText(), "");
}

TEST_F(EditorTest,
       InsertionAfterUndoShouldntCreateTwoBreakpointsAtTheSamePlace) {

  editor.InsertChar(' ');
  editor.Undo();

  editor.InsertChar(' ');

  auto undoStack = editor.GetUndoStack();
  Command *lastCmd = undoStack[undoStack.size() - 1];
  Command *secondLastCmd = undoStack[undoStack.size() - 2];

  EXPECT_EQ(lastCmd->GetCommandType(), CommandType::InsertChar);
  EXPECT_EQ(lastCmd->GetCommandCharacter(), ' ');
  EXPECT_EQ(secondLastCmd, nullptr);

  editor.Undo();
  editor.Undo();

  EXPECT_EQ(editor.GetText(), "");
}
