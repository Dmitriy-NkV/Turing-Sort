#include "functions.hpp"
#include <vector>
#include <filesystem>

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

void clearDirectory(const std::string& path)
{
  for (const auto& entry: std::filesystem::directory_iterator(path))
  {
    std::filesystem::remove_all(entry.path());
  }
}
