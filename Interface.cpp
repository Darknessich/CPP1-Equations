#include "Interface.h"
#include <array>
#include <cmath>

enum class rootsFlag {
  NO_ROOTS,
  ONE_ROOT,
  TWO_ROOTS,
  INF_ROOTS
};

bool InputPoly(std::istream& _in, std::array<double, 3>& _poly) {
  _in >> _poly.at(0) >> _poly.at(1) >> _poly.at(2);
  
  if (_in.fail())
    return false;

  return true;
}

rootsFlag Solve(std::array<double, 3> _poly, std::array<double, 2>& _roots) {
  rootsFlag result;

  if (_poly.at(0) == 0.0 && _poly.at(1) == 0.0) {
    result = (_poly.at(2) == 0.0) ? rootsFlag::INF_ROOTS : rootsFlag::NO_ROOTS;
  }
  else if (_poly.at(0) == 0.0) {
    result = rootsFlag::ONE_ROOT;
    _roots.at(0) = - _poly.at(2) / _poly.at(1);
  }
  else {
    double b = _poly.at(1) / (2.0 * _poly.at(0));
    double c = b * b - _poly.at(2) / _poly.at(0);

    if (c > 0.0) {
      result = rootsFlag::TWO_ROOTS;
      _roots.at(0) = -b - std::sqrt(c);
      _roots.at(1) = -b + std::sqrt(c);
    }
    else if (c == 0.0) {
      result = rootsFlag::ONE_ROOT;
      _roots.at(0) = -b;
    }
    else {
      result = rootsFlag::NO_ROOTS;
    }
  }

  return result;
}

void Interface(std::istream& _in, std::ostream& _out) {
  std::array<double, 3> poly = {0};
  std::array<double, 2> roots = {0};

  if (InputPoly(_in, poly)) {
    switch (Solve(poly, roots))
    {
    case rootsFlag::NO_ROOTS:
      _out << "Equations has no solutions.";
      break;
    case rootsFlag::ONE_ROOT:
      _out << "Equations has one root:\n\tx = " << roots.at(0);
      break;
    case rootsFlag::TWO_ROOTS:
      _out << "Equations has two root:\n\tx1 = " << roots.at(0) 
        << "\n\tx2 = " << roots.at(1);
      break;
    case rootsFlag::INF_ROOTS:
      _out << "Equations has infinitely many solutions.";
      break;
    default: // Unreal
      _out << "Unexpected behavior...";
      break;
    }
  }
  else {
    _out << "Input error";
  }
}
