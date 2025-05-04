#include <iostream>
#include <filesystem>
#include "src/tape.hpp"
#include "src/tape_sorter.hpp"

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "Error: Wrong arguments" << '\n';
    return 1;
  }
  else if (!std::filesystem::exists(argv[1]))
  {
    std::cerr << "Error: Incorrect input file" << '\n';
    return 1;
  }
  else if (!std::filesystem::exists(argv[3]))
  {
    std::cerr << "Error: Incorrect config file" << '\n';
  }

  try
  {
    Config config = readConfig(argv[3]);
    Tape inputTape(argv[1], config);
    Tape outputTape(argv[2], config);

    TapeSorter sorter(config, 20);
    sorter(inputTape, outputTape);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }

  return 0;
}