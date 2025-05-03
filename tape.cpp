#include "tape.hpp"
#include <thread>
#include <chrono>
#include <iomanip>
#include <iostream>

Config::Config(int moveDelay, int rewindDelay, int writeDelay, int readDelay):
  moveDelay_(moveDelay),
  rewindDelay_(rewindDelay),
  writeDelay_(writeDelay),
  readDelay_(readDelay)
{}

Tape::Tape(const std::string& fileName, const Config& config):
  tape_(fileName, std::ios::in | std::ios::out),
  currentPos_(0),
  config_(config)
{}

void Tape::shiftLeft()
{
  std::this_thread::sleep_for(std::chrono::milliseconds(config_.moveDelay_));
  currentPos_ -= 12;
}

void Tape::shiftRight()
{
  std::this_thread::sleep_for(std::chrono::milliseconds(config_.moveDelay_));
  currentPos_ += 12;
}

void Tape::rewind()
{
  std::this_thread::sleep_for(std::chrono::milliseconds(config_.rewindDelay_));
  currentPos_ = 0;
  tape_.seekg(currentPos_);
}

void Tape::write(int element)
{
  tape_.seekg(currentPos_);
  std::this_thread::sleep_for(std::chrono::milliseconds(config_.writeDelay_));
  tape_ << std::hex << std::setfill('0') 
    << std::setw(2) << (element & 0xFF) << " "
    << std::setw(2) << ((element >> 8) & 0xFF) << " "
    << std::setw(2) << ((element >> 16) & 0xFF) << " "
    << std::setw(2) << ((element >> 24) & 0xFF) << "\n";
}

int Tape::read() const
{
  tape_.seekg(currentPos_);
  std::this_thread::sleep_for(std::chrono::milliseconds(config_.readDelay_));
  int byte0 = 0;
  int byte1 = 0;
  int byte2 = 0;
  int byte3 = 0;

  tape_ >> std::hex >> byte0 >> byte1 >> byte2 >> byte3;
  return byte0 | (byte1 << 8) | (byte2 << 16) | (byte3 << 24);
}

bool Tape::isEnd() const
{
  return tape_.eof();
}