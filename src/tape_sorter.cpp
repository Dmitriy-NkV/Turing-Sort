#include "tape_sorter.hpp"
#include <limits>
#include <algorithm>

TapeSorter::TapeSorter(const Config& config, size_t ram):
  config_(config),
  ram_(ram)
{}

void TapeSorter::operator()(Tape& inputTape, Tape& outputTape) const
{
  std::vector< Tape > tempTapes;

  inputTape.rewind();
  while (!inputTape.isEnd())
  {
    std::vector< int > data;
    while (!inputTape.isEnd() && data.size() != ram_)
    {
      data.push_back(inputTape.read());
      inputTape.shiftRight();
    }
    std::sort(data.begin(), data.end());

    size_t currentTapeNum = tempTapes.size();
    std::string fileName = "tmp/temp" + std::to_string(currentTapeNum) + ".txt";
    tempTapes.emplace_back(fileName, config_);

    Tape& tempTape = tempTapes[currentTapeNum];
    for (auto i = data.cbegin(); i != data.cend(); ++i)
    {
      tempTape.write(*i);
      tempTape.shiftRight();
    }
    tempTape.rewind();
  }

  bool isEmpty = false;
  while (!isEmpty)
  {
    int minNum = std::numeric_limits< int >::max();
    size_t minIndex = 0;
    isEmpty = findMin(tempTapes, minNum, minIndex);

    if (!isEmpty)
    {
      tempTapes[minIndex].shiftRight();
      outputTape.write(minNum);
      outputTape.shiftRight();
    }
  }
  outputTape.rewind();
}

bool TapeSorter::findMin(const std::vector< Tape >& tempTapes, int& minNum, size_t& minIndex) const
{
  bool isEmpty = true;
  for (size_t i = 0; i != tempTapes.size(); ++i)
  {
    if (!tempTapes[i].isEnd() && tempTapes[i].read() <= minNum)
    {
      minNum = tempTapes[i].read();
      minIndex = i;
      isEmpty = false;
    }
  }
  return isEmpty;
}
