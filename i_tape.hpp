#ifndef I_TAPE_HPP
#define I_TAPE_HPP

#include <cstddef>

class ITape
{
public:
  virtual ~ITape() = default;

  virtual void shiftLeft() = 0;
  virtual void shiftRight() = 0;
  virtual void rewind() = 0;

  virtual void write(int element) = 0;
  virtual int read() const = 0;

  virtual bool isEnd() const = 0;
  virtual size_t size() const = 0;
};

#endif