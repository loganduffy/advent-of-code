#include <algorithm>
#include <cstdint>
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>


// Takes file input and returns a vector of strings
std::vector<std::string> readFile (const std::string& filename)
{
  std::ifstream file(filename);
  std::vector<std::string> idRanges;

  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string fileContent = buffer.str();

  std::istringstream rangeStream(fileContent);
  std::string range;

  while (std::getline(rangeStream, range, ','))
  {
    if (!range.empty())
    {
      range.erase(range.find_last_not_of(" \t\n\r\f\v") + 1);
      range.erase(0, range.find_first_not_of(" \t\n\r\f\v"));
      idRanges.push_back(range);
    }
  }
  return idRanges;
}


uint64_t invalidIDs(uint64_t L, uint64_t R)
{
  uint64_t sum = 0;

  for (int halfLength = 1; halfLength <= 9; halfLength++)
  {
    uint64_t minHalf = 1;
    for (int i = 1; i < halfLength; i++) minHalf *= 10;

    uint64_t maxHalf = minHalf * 10 - 1;

    for (uint64_t firstHalf = minHalf; firstHalf <= maxHalf; firstHalf++)
    {

      std::string firstStr = std::to_string(firstHalf);
      std::string invalidStr = firstStr + firstStr;
      uint64_t invalidID;


      try
      {
        invalidID = std::stoul(invalidStr);
      }
      catch (...)
      {
        break;
      }

      if (invalidID < L) continue;
      if (invalidID > R) break;

      sum += invalidID;

    }
  }

  return sum;
}

int main()
{
  std::vector<std::string> idRanges = readFile("../puzzleranges.txt");
  uint64_t totalSum = 0;

  for (const auto& rangeStr : idRanges)
  {
    size_t dashPosition = rangeStr.find('-');
    uint64_t start = std::stoul(rangeStr.substr(0, dashPosition));
    uint64_t end = std::stoul(rangeStr.substr(dashPosition + 1));
    uint64_t rangeSum = invalidIDs(start, end);
    totalSum += rangeSum;
  }

  std::cout << totalSum << std::endl;

  return 0;
}

