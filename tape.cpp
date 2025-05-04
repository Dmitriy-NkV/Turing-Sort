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

Config readConfig(const std::string& fileName)
{
  std::ifstream input(fileName);
  std::vector< int > config;

  int delay = 0;
  while (input >> delay)
  {
    config.push_back(delay);
  }
  if (config.size() != 4)
  {
    throw std::logic_error("Error: Incorrect config parameters");
  }

  return Config(config[0], config[1], config[2], config[3]);
}

Tape::Tape(const std::string& fileName, const Config& config):
  tape_(fileName, std::ios::out | std::ios::app),
  currentPos_(0),
  config_(config)
{
  tape_.close();
  tape_.open(fileName, std::ios::in | std::ios::out);
}

Tape::Tape(Tape&& other):
  tape_(std::move(other.tape_)),
  currentPos_(other.currentPos_),
  config_(other.config_)
{
  other.currentPos_ = 0;
}

Tape& Tape::operator=(Tape&& other)
{
  if (&other != this)
  {
    tape_ = std::move(other.tape_);
    currentPos_ = other.currentPos_;
    config_ = other.config_;
    other.currentPos_ = 0;
  }
  return *this;
}

void Tape::shiftLeft()
{
  if (currentPos_ == 0)
  {
    throw std::out_of_range("Error: Out of range");
  }

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
    << std::setw(2) << (element & 0xFF) << ' '
    << std::setw(2) << ((element >> 8) & 0xFF) << ' '
    << std::setw(2) << ((element >> 16) & 0xFF) << ' '
    << std::setw(2) << ((element >> 24) & 0xFF) << '\n';
}

int Tape::read() const
{
  if (isEnd())
  {
    throw std::out_of_range("Error: Reading out of range");
  }

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
  tape_.seekg(currentPos_);
  return tape_.peek() == std::ifstream::traits_type::eof();
}