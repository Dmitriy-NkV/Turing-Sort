#ifndef TAPE_SORTER_HPP
#define TAPE_SORTER_HPP

#include "tape.hpp"

class TapeSorter
{
public:
  TapeSorter(const Config& config, size_t ram);
  ~TapeSorter() = default;

  void operator()(Tape& inputTape, Tape& outputTape) const;

private:
  Config config_;
  size_t ram_;
};

#endif