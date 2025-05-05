#include "functions.hpp"
#include <vector>
#include <filesystem>

Config readConfig(const std::string& fileName)
{
  constexpr size_t REQUIRED_PARAMS = 4;
  std::ifstream input(fileName);
  if (!input)
  {
    throw std::runtime_error("Error: Cannot open config gile");
  }

  std::vector< int > config;
  int delay = 0;
  while (input >> delay)
  {
    if (delay < 0)
    {
      throw std::logic_error("Error: Delay must be non-negative");
    }
    config.push_back(delay);
  }
  if (config.size() != REQUIRED_PARAMS)
  {
    throw std::logic_error("Error: Incorrect config parameters");
  }

  return Config(config[0], config[1], config[2], config[3]);
}

void clearDirectory(const std::string& path)
{
  if (std::filesystem::exists(path))
  {
    for (const auto& entry: std::filesystem::directory_iterator(path))
    {
      std::filesystem::remove_all(entry.path());
    }
  }
  else
  {
    throw std::logic_error("Error: Directory does not exists");
  }
}
