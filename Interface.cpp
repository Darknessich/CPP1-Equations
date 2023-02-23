#include "Interface.h"
#include <array>
#include <cmath>

enum class errType {
  NO_ERR,
  INPUT_ERR
};

enum class rootsFlag {
  NO_ROOTS,
  ONE_ROOT,
  TWO_ROOTS,
  INF_ROOTS
};

errType err = errType::NO_ERR;

typedef struct
{
  rootsFlag flag;
  std::array<double, 2> roots;
} roots_t;

std::array<double, 3> InputPoly(std::istream& _in) {
  std::array<double, 3> poly;
  _in >> poly.at(0) >> poly.at(1) >> poly.at(2);
  
  if (_in.fail())
    err = errType::INPUT_ERR;

  return poly;
}

roots_t Solve(std::array<double, 3> _poly) {
  roots_t result;
  if (_poly.at(0) == 0.0 && _poly.at(1) == 0.0) {
    result.flag = (_poly.at(2) == 0.0) ? rootsFlag::INF_ROOTS : rootsFlag::NO_ROOTS;
  }
  else if (_poly.at(0) == 0.0) {
    result.flag = rootsFlag::ONE_ROOT;
    result.roots.at(0) = - _poly.at(2) / _poly.at(1);
  }
  else {
    double b = _poly.at(1) / (2.0 * _poly.at(0));
    double c = b * b - _poly.at(2) / _poly.at(0);

    if (c > 0.0) {
      result.flag = rootsFlag::TWO_ROOTS;
      result.roots.at(0) = -b - std::sqrt(c);
      result.roots.at(1) = -b + std::sqrt(c);
    }
    else if (c == 0.0) {
      result.flag = rootsFlag::ONE_ROOT;
      result.roots.at(0) = -b;
    }
    else {
      result.flag = rootsFlag::NO_ROOTS;
    }
  }

  return result;
}

void Interface(std::istream& _in, std::ostream& _out) {
  std::array<double, 3> poly;
  roots_t result;

  poly = InputPoly(_in);

  if (err == errType::NO_ERR) {
    result = Solve(poly);
    switch (result.flag)
    {
    case rootsFlag::NO_ROOTS:
      _out << "Equations has no solutions.";
      break;
    case rootsFlag::ONE_ROOT:
      _out << "Equations has one root:\n\tx = " << result.roots.at(0);
      break;
    case rootsFlag::TWO_ROOTS:
      _out << "Equations has two root:\n\tx1 = " << result.roots.at(0) 
        << "\n\tx2 = " << result.roots.at(1);
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