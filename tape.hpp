#ifndef TAPE_HPP
#define TAPE_HPP

#include <vector>

class Tape
{
public:
  Tape(size_t size);
  virtual ~Tape() = default;

  virtual void shiftLeft() = 0;
  virtual void shiftRight() = 0;
  virtual int read() const = 0;
  virtual void write(int element) = 0;
  virtual void rewind() = 0;
  virtual bool isEnd() const = 0;

private:
  std::vector< int > tape_;
  std::vector< int >::iterator iter_;
};

#endif