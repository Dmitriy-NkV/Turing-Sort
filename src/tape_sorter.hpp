#ifndef TAPE_SORTER_HPP
#define TAPE_SORTER_HPP

#include <vector>
#include "tape.hpp"

class TapeSorter
{
public:
  TapeSorter(const Config& config, size_t ram);
  ~TapeSorter() = default;

  void operator()(Tape& inputTape, Tape& outputTape) const;

private:
  bool findMin(const std::vector< Tape >& tempTapes, int& minNum, size_t& minIndex) const;
  Config config_;
  size_t ram_;
};

#endif