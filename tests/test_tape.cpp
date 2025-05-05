#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <filesystem>
#include "../src/tape.hpp"
#include "../src/functions.hpp"

TEST(TapeTest, Initialization)
{
  clearDirectory("tmp");
  Config testConfig = Config(0, 0, 0, 0);
  const std::string testFile = "tmp/test_tape.txt";

  Tape testTape(testFile, testConfig);
  EXPECT_TRUE(std::filesystem::exists(testFile)) << "Tape file does not created";
}

TEST(TapeTest, WriteAndRead)
{
  clearDirectory("tmp");
  Config testConfig = Config(0, 0, 0, 0);
  const std::string testFile = "tmp/test_tape.txt";

  Tape testTape(testFile, testConfig);
  testTape.write(100);
  EXPECT_EQ(testTape.read(), 100) << "Actual: " << testTape.read() << ", Expected: " << 100;
}

TEST(TapeTest, Shift)
{
  clearDirectory("tmp");
  Config testConfig = Config(0, 0, 0, 0);
  const std::string testFile = "tmp/test_tape.txt";

  Tape testTape(testFile, testConfig);
  testTape.write(100);
  testTape.shiftRight();
  testTape.write(200);
  testTape.shiftRight();
  testTape.write(300);

  EXPECT_EQ(testTape.read(), 300) << "Actual: " << testTape.read() << ", Expected: " << 300;
  testTape.shiftLeft();
  EXPECT_EQ(testTape.read(), 200) << "Actual: " << testTape.read() << ", Expected: " << 200;
  testTape.shiftLeft();
  EXPECT_EQ(testTape.read(), 100) << "Actual: " << testTape.read() << ", Expected: " << 100;
}

TEST(TapeTest, Rewind)
{
  clearDirectory("tmp");
  Config testConfig = Config(0, 0, 0, 0);
  const std::string testFile = "tmp/test_tape.txt";

  Tape testTape(testFile, testConfig);
  testTape.write(100);
  testTape.shiftRight();
  testTape.write(200);
  testTape.shiftRight();
  testTape.write(300);
  testTape.rewind();

  EXPECT_EQ(testTape.read(), 100) << "Actual: " << testTape.read() << ", Expected: " << 100;
  testTape.shiftRight();
  EXPECT_EQ(testTape.read(), 200) << "Actual: " << testTape.read() << ", Expected: " << 200;
  testTape.shiftRight();
  EXPECT_EQ(testTape.read(), 300) << "Actual: " << testTape.read() << ", Expected: " << 300;
}

TEST(TapeTest, Rewrite)
{
  clearDirectory("tmp");
  Config testConfig = Config(0, 0, 0, 0);
  const std::string testFile = "tmp/test_tape.txt";

  Tape testTape(testFile, testConfig);
  testTape.write(100);
  testTape.shiftRight();
  testTape.write(200);
  testTape.shiftRight();
  testTape.write(300);
  testTape.shiftLeft();
  testTape.write(500);
  testTape.rewind();

  EXPECT_EQ(testTape.read(), 100) << "Actual: " << testTape.read() << ", Expected: " << 100;
  testTape.shiftRight();
  EXPECT_EQ(testTape.read(), 500) << "Actual: " << testTape.read() << ", Expected: " << 500;
  testTape.shiftRight();
  EXPECT_EQ(testTape.read(), 300) << "Actual: " << testTape.read() << ", Expected: " << 300;
}

class MockTape
{
public:
  MOCK_METHOD(void, read, (), ());
};

TEST(TapeTest, EndCheck)
{
  clearDirectory("tmp");
  Config testConfig = Config(0, 0, 0, 0);
  const std::string testFile = "tmp/test_tape.txt";

  Tape testTape(testFile, testConfig);
  testTape.write(100);
  testTape.shiftRight();
  testTape.write(100);
  testTape.shiftRight();
  testTape.write(100);
  testTape.rewind();

  MockTape mockTape;
  EXPECT_CALL(mockTape, read())
    .Times(3);

  while (!testTape.isEnd())
  {
    mockTape.read();
    testTape.shiftRight();
  }
}

TEST(TapeTest, OutOfRangeRead)
{
  clearDirectory("tmp");
  Config testConfig = Config(0, 0, 0, 0);
  const std::string testFile = "tmp/test_tape.txt";

  Tape testTape(testFile, testConfig);
  EXPECT_THROW({ testTape.read(); }, std::out_of_range) << "Expected: std::out_of_range";
}

TEST(TapeTest, OutOfRangeShift)
{
  clearDirectory("tmp");
  Config testConfig = Config(0, 0, 0, 0);
  const std::string testFile = "tmp/test_tape.txt";

  Tape testTape(testFile, testConfig);
  EXPECT_THROW({ testTape.shiftLeft(); }, std::out_of_range) << "Expected: std::out_of_range";
}
