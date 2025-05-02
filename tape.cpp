#include "tape.hpp"

Tape::Tape(size_t size, int moveDelay, int rewindDelay, int writeDelay, int readDelay):
  tape_(size, 0),
  iter_(tape_.begin()),
  moveDelay_(moveDelay),
  rewindDelay_(rewindDelay),
  writeDelay_(writeDelay),
  readDelay_(readDelay)
{}