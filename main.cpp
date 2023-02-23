#include <fstream>
#include <iostream>
#include "Interface.h"

int main(int argc, char* argv[]) {
  switch (argc)
  {
  case 1:
	Interface();
	break;
  case 2: 
  {
	std::ifstream input(argv[1]);
	if (input.is_open()) 
	  Interface(input);
	else 
	  std::cout << "file" << argv[1] << "could not be opened" << std::endl;
	break;
  }
  case 3:
  {
	std::ifstream input(argv[1]);
	std::ofstream output(argv[2], std::ios::out | std::ios::ate);
	
	if (input.is_open() && output.is_open()) {
	  Interface(input, output);
	}
	else {
	  if (!input.is_open())
		std::cout << "file" << argv[1] << "could not be opened" << std::endl;
	  if (!output.is_open())
		std::cout << "file" << argv[2] << "could not be opened" << std::endl;
	}
	break;
  }
  default:
	std::cout << "So manny arguments" << std::endl;
	break;
  }
}