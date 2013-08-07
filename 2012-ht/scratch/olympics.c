#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <err.h>

#define NMAX     100
#define STRSIZE   64
#define BUFSIZE 1024


enum {
  FEMALE,
  MALE
};


struct athlete_data {
  char first_name[STRSIZE];
  char last_name[STRSIZE];
  char country[STRSIZE];
  char sport[STRSIZE];
  int age;
  int height;
  int weight;
  int gender;
};


static int next_string (char ** scanner, char * string, int strsize)
{
  int ii;
  
  if (NULL == *scanner) {
    *string = '\0';
    return -1;
  }
  
  for (ii = 0; ii < strsize - 1; ++ii, ++(*scanner), ++(string)) {
    switch (**scanner) {
      
    case ':':
      ++(*scanner);
      *string = '\0';
      return 0;
      
    case '\0':
    case '\n':
      *scanner = NULL;
      *string = '\0';
      return 1;
    }
    
    *string = **scanner;
  }
  
  *string = '\0';	 /* truncated strings also need termination */
  
  /*
    skip scanner to end of what the string would have been
  */
  for (++(*scanner); 1; ++(*scanner)) {
    switch (**scanner) {
    case ':':
      ++(*scanner);
      return 2;
    case '\0':
    case '\n':
      *scanner = NULL;
      return 3;
    }
  }
  
  return -2;			/* never reached */
}


static int next_number (char ** scanner, int * number)
{
  char string[STRSIZE];
  int status;
  
  status = next_string (scanner, string, STRSIZE);
  if (1 != sscanf (string, "%d", number)) {
    return -3;
  }
  return status;
}


static int parse_line (FILE * in, struct athlete_data * athlete)
{
  char readbuf[BUFSIZE];
  char * scanner;
  char tmp[2];
  
  if (NULL == fgets(readbuf, BUFSIZE, in)) {
    return 1;
  }
  
  scanner = readbuf;
  if (0 > next_string(&scanner, athlete->first_name, STRSIZE)) {
    return -1;
  }
  if (0 > next_string(&scanner, athlete->last_name, STRSIZE)) {
    return -2;
  }
  if (0 > next_string(&scanner, athlete->country, STRSIZE)) {
    return -3;
  }
  if (0 > next_string(&scanner, athlete->sport, STRSIZE)) {
    return -4;
  }
  if (0 > next_number(&scanner, &athlete->age)) {
    return -5;
  }
  if (0 > next_number(&scanner, &athlete->height)) {
    return -6;
  }
  if (0 > next_number(&scanner, &athlete->weight)) {
    return -7;
  }
  if (0 > next_string(&scanner, tmp, 2)) {
    return -8;
  }
  switch (tmp[0]) {
  case 'f':
  case 'F':
    athlete->gender = FEMALE;
    break;
  case 'm':
  case 'M':
    athlete->gender = MALE;
    break;
  default:
    return -9;
  }
  
  return 0;
}


static void print_athlete (FILE * out, struct athlete_data const * athlete)
{
  fprintf (out,
	   "%s %s is %d years old, %s is from %s, and %s sport is %s\n",
	   athlete->first_name,
	   athlete->last_name,
	   athlete->age,
	   athlete->gender == FEMALE ? "she" : "he",
	   athlete->country,
	   athlete->gender == FEMALE ? "her" : "his",
	   athlete->sport);
}


int main (int argc, char ** argv)
{
  struct athlete_data athletes[NMAX];
  int ndata;
  char const * fname = "sample.txt";
  FILE * in;
  int ii;  
  
  if (NULL == (in = fopen (fname, "rb"))) {
    err (EXIT_FAILURE, "%s", fname);
  }
  
  for (ndata = 0; ndata < NMAX; ++ndata) {
    int status = parse_line(in, athletes + ndata);
    if (1 == status) {
      break;
    }
    if (0 != status) {
      errx (EXIT_FAILURE, "%s:%d: error code %d", fname, ndata + 1, status);
    }
  }
  
  for (ii = 0; ii < ndata; ++ii) {
    print_athlete (stdout, &athletes[ii]);
  }
  
  return 0;
}
