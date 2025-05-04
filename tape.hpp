#ifndef TAPE_HPP
#define TAPE_HPP

#include "i_tape.hpp"
#include <vector>
#include <fstream>

class Tape;

class Config
{
  friend class Tape;
public:
  Config(int moveDelay, int rewindDelay, int writeDelay, int readDelay);

private:
  int moveDelay_;
  int rewindDelay_;
  int writeDelay_;
  int readDelay_;
};

Config readConfig(const std::string& fileName);

class Tape: public details::ITape
{
public:
  Tape(const std::string& fileName, const Config& config);
  Tape(Tape&& other);
  ~Tape() = default;

  Tape& operator=(Tape&& other);

  void shiftLeft() override;
  void shiftRight() override;
  void rewind() override;

  void write(int element) override;
  int read() const override;

  bool isEnd() const override;

private:
  mutable std::fstream tape_;
  size_t currentPos_;
  Config config_;
};

#endif