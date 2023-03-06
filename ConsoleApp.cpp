#include <fstream>
#include <iostream>
#include <string>
#include "ConsoleApp.h"
#include "Quadratic.h"

void Menu(std::string _iname, std::string _oname) {
  std::cout << std::endl;
  std::cout << "1. Change input filename (now : ";
  std::cout << (_iname.empty() ? "std::cin)" : ("\"" + _iname + "\")")) << std::endl;
  std::cout << "2. Change output filename (now : ";
  std::cout << (_oname.empty() ? "std::cout)" : ("\"" + _oname + "\")")) << std::endl;
  std::cout << "3. Solve a quadratic equation" << std::endl;
  std::cout << "0. Exit" << std::endl;
  std::cout << std::endl;
}

void ChangeInput(std::ifstream& _input, std::string& _iname) {
  std::cout << "Enter file name : ";
  std::cin >> _iname;

  _input.close();
  _input.open(_iname);
  if (_input.is_open()) {
    std::cout << "file \"" << _iname << "\" has been opened" << std::endl;
  }
  else {
    std::cout << "file \"" << _iname << "\" could not be opened" << std::endl;
    _iname = "";
  }
}

void ChangeOutput(std::ofstream& _output, std::string& _oname) {
  std::cout << "Enter file name : ";
  std::cin >> _oname;

  _output.close();
  _output.open(_oname, std::ios::app);
  if (_output.is_open()) {
    std::cout << "file \"" << _oname << "\" has been opened" << std::endl;
  }
  else {
    std::cout << "file \"" << _oname << "\" could not be opened" << std::endl;
    _oname = "";
  }
}

void Equations(std::ifstream& _input, std::ofstream& _output, std::string& _iname, std::string& _oname) {
  if (_iname.empty() && _oname.empty())
    QuadraticEquations();
  else if (_oname.empty())
    QuadraticEquations(_input);
  else if (_iname.empty())
    QuadraticEquations(std::cin, _output);
  else
    QuadraticEquations(_input, _output);
}

void Choice(int _flag, std::ifstream& _input, std::ofstream& _output, std::string& _iname, std::string& _oname) {
  switch (_flag) {
  case 0:
    std::cout << "Exit..." << std::endl;
    break;
  case 1:
    ChangeInput(_input, _iname);
    break;
  case 2:
    ChangeOutput(_output, _oname);
    break;
  case 3:
    Equations(_input, _output, _iname, _oname);
    break;
  default:
    std::cout << "No such item" << std::endl;
    break;
  }
}

void ConsoleApplication() {
  std::ifstream input;
  std::ofstream output;
  std::string iname = "";
  std::string oname = "";

  int flag = 1;
  while (flag) {
    Menu(iname, oname);
    std::cout << "Choose an item: ";
    std::cin >> flag;
    Choice(flag, input, output, iname, oname);
  }
}