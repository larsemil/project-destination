#include <iostream>
#include <iomanip>
#include "functions.hpp"

void hexdump(char* buffer, int buflen)
{
  for (char* c = buffer; c < buffer + buflen; ++c)
  {
    std::cout << std::setw(2) << std::setfill('0') << std::hex
      << int(static_cast<unsigned char>(*c)) << " ";
  }
  std::cout << std::endl;
}

void clamp(int& val, int min, int max)
{
  if (val > max)
    val = max;
  else if (val < min)
    val = min;
}

void clamp(double& val, double min, double max)
{
  if (val > max)
    val = max;
  else if (val < min)
    val = min;
}

double deg2rad(double val)
{
  return (2 * M_PI * val) / 360.0;
}
