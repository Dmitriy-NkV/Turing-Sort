#include <iostream>
#include <filesystem>
#include "src/tape.hpp"
#include "src/functions.hpp"
#include "src/tape_sorter.hpp"

int main(int argc, char* argv[])
{
  size_t ramSize = 50;
  if (argc != 4 && argc != 5)
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
    return 1;
  }
  else if (argc == 5)
  {
    try
    {
      ramSize = std::stoull(argv[4]);
    }
    catch (const std::exception& e)
    {
      std::cerr << "Error: Wrong ram parameter" << '\n';
      return 1;
    }
  }

  try
  {
    clearDirectory("tmp");
    Config config = readConfig(argv[3]);
    Tape inputTape(argv[1], config);
    Tape outputTape(argv[2], config, true);

    TapeSorter sorter(config, ramSize);
    sorter(inputTape, outputTape);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }

  return 0;
}
