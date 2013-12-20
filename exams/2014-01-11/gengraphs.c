#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/uio.h>
#include <sys/time.h>


int random_int (int minval, int maxval)
{
  static int fd = -1;
  unsigned int delta, tmp, mask;
  
  if (0 > fd && 0 > (fd = open ("/dev/urandom", O_RDONLY))) {
    err (EXIT_FAILURE, __FILE__": %s: open /dev/urandom", __func__);
  }
  
  if (maxval < minval) {
    tmp = minval;
    minval = maxval;
    maxval = tmp;
  }
  if (0 == (delta = maxval - minval)) {
    return minval;
  }
  
  for (tmp = 1 << (8 * sizeof(int) - 1); 0 == (tmp & delta); tmp >>= 1) {
    /* nop */;
  }
  for (mask = tmp; 0 != tmp; tmp >>= 1) {
    mask |= tmp;
  }
  
  for (;;) {
    if (sizeof(int) != read (fd, &tmp, sizeof(int))) {
      err (EXIT_FAILURE, __FILE__": %s: read /dev/urandom", __func__);
    }
    tmp &= mask;
    if (tmp <= delta) {
      break;
    }
  }
  
  return minval + tmp;
}


long delay (void)
{
  return random_int (100, 101);
}


long fconst (long nn)
{
  long tt;
  long ii;
  tt = 0;
  for (ii = 0; ii < 10; ++ii) {
    tt += delay();
  }
  return tt;
}


long flin1 (long nn)
{
  long tt;
  long count = random_int (1000, 1200);
  long ii;
  tt = 0;
  for (ii = 0; ii < count; ++ii) {
    tt += delay();
  }
  for (ii = 0; ii < nn; ++ii) {
    tt += delay();
    tt += delay();
    tt += delay();
  }
  return tt;
}


long flin2 (long nn)
{
  long tt = 0;
  long count = random_int (10000, 12000);
  long ii;
  for (ii = 0; ii < count; ++ii) {
    tt += delay();
  }
  for (ii = 0; ii < nn; ++ii) {
    tt += delay();
  }
  return tt;
}


long flog1 (long nn)
{
  long ii, tt;
  tt = 0;
  tt += delay();
  nn *= 10000;
  for (ii = 1; ii <= nn; ii *= 2) {
    tt += 1001;
  }
  return tt;
}


long flog2 (long nn)
{
  long ii, tt;
  tt = 0;
  for (ii = 0; ii < 5; ++ii) {
    tt += delay();
  }
  nn *= 500000;
  for (ii = 1; ii <= nn; ii *= 2) {
    int jj;
    for (jj = 0; jj < 50; ++jj) {
      tt += delay();
    }
  }
  return tt;
}


long fn2 (long nn)
{
  long ii, jj, tt;
  tt = 0;
  nn /= 100;
  for (ii = 0; ii < nn; ++ii) {
    int dd = delay();
    for (jj = 0; jj < nn; ++jj) {
      tt += dd;
    }
  }
  return tt;
}


typedef long (*func_t)(long);


int main (int argc, char ** argv)
{
  func_t func[] = {
    flin1,			/* 2 */
    flog1,			/* 3 */
    fconst,			/* 4 */
    flog2,			/* 5 */
    fn2,			/* 6 */
    flin2			/* 7 */
  };
  
  long nn, ii;
  for (nn = 1000; nn < 500000; nn = (long) nn * 1.5) {
    printf ("%ld", nn);
    fflush (stdout);
    for (ii = 0; ii < sizeof (func) / sizeof (*func); ++ii) {
      printf ("    %ld", func[ii](nn));
      fflush (stdout);
    }
    printf ("\n");
  }
  
  return 0;
}
