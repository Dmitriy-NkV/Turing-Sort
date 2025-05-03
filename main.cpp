#include <iostream>
#include <fstream>
#include <vector>
#include "tape.hpp"

Config readConfig(const std::string& fileName)
{
  std::ifstream input(fileName);
  std::vector< int > config;
  int delay = 0;
  while (input >> delay)
  {
    config.push_back(delay);
  }
  return Config(config[0], config[1], config[2], config[3]);
}

int main(int argc, char* argv[])
{
  if (argc < 3)
  {
    std::cerr << "Error: Not enough arguments\n";
    return 1;
  }

  Config config = readConfig(argv[3]);

  Tape inputTape(argv[1], config);
  Tape outputTape(argv[2], config);
}