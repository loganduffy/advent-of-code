
#include <cinttypes>
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
// Brute force approach because I don't know how to think
int rotationSolver(const std::vector<std::string>& rotations)
{
  int count = 0;
  int dialPoint = 50;

  // For each rotation and their instructions (line)
  for (const std::string& rotation : rotations)
  {
    char direction = rotation[0];
    int distance = std::stoi(rotation.substr(1));

    for (int step = 0; step < distance; step++)
    {
      if (direction == 'R')
      {
        dialPoint = (dialPoint + 1) % 100;
      }
      else 
      {
        dialPoint = (dialPoint - 1) % 100;

        if (dialPoint < 0)
        {
          dialPoint += 100;
        }
      }
      if (dialPoint == 0)
      {
        count++;
      }
    }
  }

  return count;

}


int main() 
{
  std::vector<std::string> rotations = readFile("../puzzle.txt");
  int result = rotationSolver(rotations);

  std::cout << "Final Count: " << result << '\n';

  return 0;
}
