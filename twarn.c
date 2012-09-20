#include <unistd.h>

int main ()
{
  size_t foo;
  ssize_t bar;
  if (foo < bar)
    return 1;
  return 0;
}
