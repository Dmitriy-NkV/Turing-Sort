#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <filesystem>
#include "../src/tape.hpp"

class MockTape 
{
public:
  MOCK_METHOD(void, read, (), ());
};

TEST(TapeTest, Initialization)
{
  Config testConfig = Config(0, 0, 0, 0);
  const std::string testFile = "tmp/test_tape.txt";

  if (std::filesystem::exists(testFile))
  {
    std::filesystem::remove(testFile);
  }

  Tape tape(testFile, testConfig);
  EXPECT_TRUE(std::filesystem::exists(testFile));

  if (std::filesystem::exists(testFile))
  {
    std::filesystem::remove(testFile);
  }
}

TEST(TapeTest, WriteAndRead)
{
  Config testConfig = Config(0, 0, 0, 0);
  const std::string testFile = "tmp/test_tape.txt";

  Tape tape(testFile, testConfig);
  tape.write(100);
  EXPECT_EQ(tape.read(), 100);

  if (std::filesystem::exists(testFile))
  {
    std::filesystem::remove(testFile);
  }
}

TEST(TapeTest, Shift)
{
  Config testConfig = Config(0, 0, 0, 0);
  const std::string testFile = "tmp/test_tape.txt";

  Tape tape(testFile, testConfig);
  tape.write(100);
  tape.shiftRight();
  tape.write(200);
  tape.shiftRight();
  tape.write(300);

  EXPECT_EQ(tape.read(), 300);
  tape.shiftLeft();
  EXPECT_EQ(tape.read(), 200);
  tape.shiftLeft();
  EXPECT_EQ(tape.read(), 100);

  if (std::filesystem::exists(testFile))
  {
    std::filesystem::remove(testFile);
  }
}

TEST(TapeTest, Rewind)
{
  Config testConfig = Config(0, 0, 0, 0);
  const std::string testFile = "tmp/test_tape.txt";

  Tape tape(testFile, testConfig);
  tape.write(100);
  tape.shiftRight();
  tape.write(200);
  tape.shiftRight();
  tape.write(300);
  tape.rewind();

  EXPECT_EQ(tape.read(), 100);
  tape.shiftRight();
  EXPECT_EQ(tape.read(), 200);
  tape.shiftRight();
  EXPECT_EQ(tape.read(), 300);

  if (std::filesystem::exists(testFile))
  {
    std::filesystem::remove(testFile);
  }
}

TEST(TapeTest, Rewrite)
{
  Config testConfig = Config(0, 0, 0, 0);
  const std::string testFile = "tmp/test_tape.txt";

  Tape tape(testFile, testConfig);
  tape.write(100);
  tape.shiftRight();
  tape.write(200);
  tape.shiftRight();
  tape.write(300);
  tape.shiftLeft();
  tape.write(500);
  tape.rewind();

  EXPECT_EQ(tape.read(), 100);
  tape.shiftRight();
  EXPECT_EQ(tape.read(), 500);
  tape.shiftRight();
  EXPECT_EQ(tape.read(), 300);

  if (std::filesystem::exists(testFile))
  {
    std::filesystem::remove(testFile);
  }
}

TEST(TapeTest, EndCheck)
{
  Config testConfig = Config(0, 0, 0, 0);
  const std::string testFile = "tmp/test_tape.txt";

  Tape tape(testFile, testConfig);
  tape.write(100);
  tape.shiftRight();
  tape.write(100);
  tape.shiftRight();
  tape.write(100);
  tape.rewind();

  MockTape tape1;
  EXPECT_CALL(tape1, read())
    .Times(3);

  while (!tape.isEnd())
  {
    tape1.read();
    tape.shiftRight();
  }

  if (std::filesystem::exists(testFile))
  {
    std::filesystem::remove(testFile);
  }
}

TEST(TapeTest, OutOfRangeRead)
{
  Config testConfig = Config(0, 0, 0, 0);
  const std::string testFile = "tmp/test_tape.txt";
  Tape tape(testFile, testConfig);

  EXPECT_THROW({
    tape.read();
  }, std::out_of_range);

  if (std::filesystem::exists(testFile))
  {
    std::filesystem::remove(testFile);
  }
}

TEST(TapeTest, OutOfRangeShift)
{
  Config testConfig = Config(0, 0, 0, 0);
  const std::string testFile = "tmp/test_tape.txt";
  Tape tape(testFile, testConfig);

  EXPECT_THROW({
    tape.shiftLeft();
  }, std::out_of_range);

  if (std::filesystem::exists(testFile))
  {
    std::filesystem::remove(testFile);
  }
}
