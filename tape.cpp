#include "tape.hpp"
#include <thread>
#include <chrono>

Tape::Tape(size_t size, int moveDelay, int rewindDelay, int writeDelay, int readDelay):
  tape_(size, 0),
  iter_(tape_.begin()),
  moveDelay_(moveDelay),
  rewindDelay_(rewindDelay),
  writeDelay_(writeDelay),
  readDelay_(readDelay)
{}

void Tape::shiftLeft()
{
  std::this_thread::sleep_for(std::chrono::milliseconds(moveDelay_));
  --iter_;
}

void Tape::shiftRight()
{
  std::this_thread::sleep_for(std::chrono::milliseconds(moveDelay_));
  ++iter_;
}

void Tape::rewind()
{
  std::this_thread::sleep_for(std::chrono::milliseconds(rewindDelay_));
  iter_ = tape_.begin();
}

void Tape::write(int element)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(writeDelay_));
  *iter_ = element;
}

int Tape::read() const
{
  std::this_thread::sleep_for(std::chrono::milliseconds(readDelay_));
  return *iter_;
}

bool Tape::isEnd() const
{
  return iter_ == tape_.end();
}

size_t Tape::size() const
{
  return tape_.size();
}