#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/*
  A custom struct to represent a person and their age
*/
typedef struct {
  char * name;
  unsigned int age;
} Person;


/*
  helper function to create a person, the name gets duplicated
*/
Person * person_create (char const * name, int age)
{
  Person * person;
  if (NULL == (person = malloc (sizeof(*person))))
    return NULL;
  person->name = strdup (name);
  person->age = age;
  return person;
}


/*
  helper function to free the memory taken up to store the information
  in a person struct
*/
void person_destroy (Person * person)
{
  free (person->name);
  free (person);
}


/*
  helper function to print a person's information
*/
void person_print (Person * person)
{
  printf ("  %-15s (%2u year%-1s old)\n",
	  person->name,
	  person->age,
	  person->age > 1 ? "s" : "");
}


/*
  helper function to read the current time, using the standard struct
  tm to store the time information
*/
int clock_read (struct tm * now)
{
  time_t raw;
  if (-1 == time(&raw))
    return -1;
  localtime_r (&raw, now);
  return 0;
}


/*
  helper function to printf a clock value
*/
void clock_print (struct tm * tt)
{
  char buf[26];
  asctime_r (tt, buf);
  printf ("  %s", buf);
}


/*
  this program illustrates how to use void* as a generic pointer, how
  to use pointer casts to get the generic pointer interpreted
  according to what type of value it points to, and the danger of
  making an incorrect cast
*/
int main (int argc, char ** argv)
{
  struct tm now;		/* standard struct for storing a time value */
  double lightspeed;
  Person * albert;		/* pointer to our custom struct person */
  
  void * generic_pointer;
  
  /*
    let's read the clock, it gets stored in a standard struct tm (from
    the time.h header)
  */
  if (0 != clock_read (&now)) {
    printf ("failed to read the clock\n");
    return 1;
  }
  
  /*
    the speed of light as a double-precision floating point number
  */
  lightspeed = 299792458.0;
  
  /*
    Albert Einstein was born on March 14, 1879. His age depends on
    today's date...
  */
  albert = person_create ("Albert Einstein",
			  (now.tm_mon >= 3 && now.tm_mday >= 14) ?
			  now.tm_year + 1901 - 1879 :
			  now.tm_year + 1900 - 1879);
  
  /* **************************************************
   * NOW FOR THE FUN PART *****************************
   * **************************************************/
  
  /*
    the generic pointer can store the address of any of our variables
  */
  
  generic_pointer = &now;
  printf ("the date and time is\n");
  clock_print (&now);
  
  generic_pointer = &lightspeed;
  printf ("the speed of light is\n  %g m/s\n", *(double*)generic_pointer);
  
  generic_pointer = albert;
  printf ("the person is\n");
  person_print (generic_pointer);
  
  return 0;
}
