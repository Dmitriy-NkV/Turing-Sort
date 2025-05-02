#ifndef TAPE_HPP
#define TAPE_HPP

#include "i_tape.hpp"
#include <vector>

class Tape: public ITape
{
public:
  Tape(size_t size);
  ~Tape() = default;

  void shiftLeft() override;
  void shiftRight() override;
  void rewind() override;

  void write(int element) override;
  int read() const override;

  bool isEnd() const override;
  size_t size() const override;

private:
  std::vector< int > tape_;
  std::vector< int >::iterator iter_;
};

#endif