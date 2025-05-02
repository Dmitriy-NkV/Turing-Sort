#include <iostream>

int main(int argc, char* argv[])
{
  if (argc < 3)
  {
    std::cerr << "Error: Not enough arguments\n";
    return 1;
  }

  std::string inputFile = argv[1];
  std::string outputFile = argv[2];
  std::string configFile = argv[3];
}