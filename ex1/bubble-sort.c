#include <stdio.h>

int main (int argc, char ** argv)
{
  int ii, jj, length;
  double data[] = { 351.354, 21.02, -3544.2, 152.999 };
  double tmp;
  
  length = sizeof(data) / sizeof(double);
  
  for (ii = 0; ii < length; ++ii) {
    for (jj = 1; jj < length; ++jj) {
      if (data[jj] < data[jj - 1]) {
	tmp = data[jj];
	data[jj] = data[jj - 1];
	data[jj - 1] = tmp;
      }
    }
  }
  
  for (ii = 0; ii < length; ++ii) {
    printf ("% 8.2f\n", data[ii]);
  }
  
  return 0;
}
