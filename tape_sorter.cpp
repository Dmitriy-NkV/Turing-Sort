#include "tape_sorter.hpp"
#include <algorithm>
#include "tape.hpp"

#include <iostream>

TapeSorter::TapeSorter(const Config& config, size_t ram):
  config_(config),
  ram_(ram)
{}

void TapeSorter::operator()(Tape& inputTape, Tape& outputTape) const
{
  std::vector< Tape > tempTapes;
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
    std::string fileName = "temp" + std::to_string(currentTapeNum) + ".txt";
    tempTapes.emplace_back(fileName, config_);

    Tape& tempTape = tempTapes[currentTapeNum];
    for (auto i = data.cbegin(); i != data.cend(); ++i)
    {
      tempTape.write(*i);
      tempTape.shiftRight();
    }
  }
}