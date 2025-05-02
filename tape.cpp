#include "tape.hpp"

Tape::Tape(size_t size):
  tape_(size, 0),
  iter_(tape_.begin())
{}