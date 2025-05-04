#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include "tape.hpp"
#include "tape_sorter.hpp"

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