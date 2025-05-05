#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <filesystem>
#include <random>
#include "../src/functions.hpp"
#include "../src/tape_sorter.hpp"

TEST(SorterTest, SortUnique)
{
  clearDirectory("tmp");
  Config testConfig = Config(0, 0, 0, 0);
  const std::string inputFile = "tmp/input_test.txt";
  const std::string outputFile = "tmp/output_test.txt";

  std::vector< int > testData = { 42, 17, 89, 5, 73, 31, 96, 12, 58, 24 };
  Tape inputTape(inputFile, testConfig);
  for (size_t i = 0; i != testData.size(); ++i)
  {
    inputTape.write(testData[i]);
    inputTape.shiftRight();
  }
  Tape outputTape(outputFile, testConfig);
  TapeSorter testSorter(testConfig, 50);
  testSorter(inputTape, outputTape);

  std::vector< int > result;
  while (!outputTape.isEnd())
  {
    result.push_back(outputTape.read());
    outputTape.shiftRight();
  }
  std::sort(testData.begin(), testData.end());

  EXPECT_EQ(testData, result);
}

TEST(SorterTest, SortNotUnique)
{
  clearDirectory("tmp");
  Config testConfig = Config(0, 0, 0, 0);
  const std::string inputFile = "tmp/input_test.txt";
  const std::string outputFile = "tmp/output_test.txt";

  std::vector< int > testData = { 42, 17, 42, 5, 73, 31, 5, 12, 58, 24 };
  Tape inputTape(inputFile, testConfig);
  for (size_t i = 0; i != testData.size(); ++i)
  {
    inputTape.write(testData[i]);
    inputTape.shiftRight();
  }
  Tape outputTape(outputFile, testConfig);
  TapeSorter testSorter(testConfig, 50);
  testSorter(inputTape, outputTape);

  std::vector< int > result;
  while (!outputTape.isEnd())
  {
    result.push_back(outputTape.read());
    outputTape.shiftRight();
  }
  std::sort(testData.begin(), testData.end());

  EXPECT_EQ(testData, result);
}

TEST(SorterTest, SortRandom)
{
  clearDirectory("tmp");
  Config testConfig = Config(0, 0, 0, 0);
  const std::string inputFile = "tmp/input_test.txt";
  const std::string outputFile = "tmp/output_test.txt";

  std::random_device random;
  std::mt19937 gen(random());
  std::uniform_int_distribution<> dist(-10000, 10000);
  std::vector< int > testData(1000);
  std::generate(testData.begin(), testData.end(), [&]() { return dist(gen); });

  Tape inputTape(inputFile, testConfig);
  for (size_t i = 0; i != testData.size(); ++i)
  {
    inputTape.write(testData[i]);
    inputTape.shiftRight();
  }
  Tape outputTape(outputFile, testConfig);
  TapeSorter testSorter(testConfig, 50);
  testSorter(inputTape, outputTape);

  std::vector< int > result;
  while (!outputTape.isEnd())
  {
    result.push_back(outputTape.read());
    outputTape.shiftRight();
  }
  std::sort(testData.begin(), testData.end());

  EXPECT_EQ(testData, result);
}
