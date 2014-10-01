#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cmath>

void hexdump(char* buffer, int buflen);
void clamp(int& val, int min, int max);
void clamp(double& val, double min, double max);
double deg2rad(double val);

#endif
