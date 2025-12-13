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
      idRanges.push_back(range);
    }
  }
  return idRanges;
}

int main()
{
  std::vector<std::string> idRanges = readFile("../puzzleranges.txt");

  for (size_t i = 0; i < idRanges.size(); i++)
  {
       std::cout << idRanges[i] << std::endl;
  }

  return 0; 
}
