#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>


// Takes file input and returns a vector of strings
std::vector<std::string> readFile (const std::string& filename)
{
  std::ifstream file(filename);
  std::vector<std::string> lines;
  std::string line;

  // While there is still a valid line to read
  while (std::getline(file, line))
  {
    if (!line.empty())
    {
      lines.push_back(line);
    }
  }
  return lines;
}


// Function processes each rotation and returns how many times the dial hits 0 or 100
int rotationSolver(const std::vector<std::string>& rotations)
{
  int count = 0;
  int dialPoint = 50;

  // For each rotation and their instructions (line)
  for (const std::string& rotation : rotations)
  {
    char direction = rotation[0];
    int distance = std::stoi(rotation.substr(1));

    // Debug line to properly check if the file is being read correctly
    std::cout << "Direction: " << direction << " Distance: " << distance << '\n';

    if (direction == 'R')
    {
      // Modular arithmetic works here no matter if it's a 3 digit rotation or 2
      dialPoint = dialPoint + distance;
      dialPoint %= 100;
    }
    else if (direction == 'L')
    {
      dialPoint = dialPoint - distance;

      // If the direction is a 3 digit value it'll go through multiple rotations
      if (dialPoint < 0)
      {
        dialPoint %= 100;
      }
    }

    if (dialPoint == 0 || dialPoint == 100)
    {
      count++;
    }

  }

  return count;

}

int main() 
{
  std::vector<std::string> rotations = readFile("puzzle.txt");
  int result = rotationSolver(rotations);

  std::cout << "Final Count: " << result << '\n';

  return 0;
}
