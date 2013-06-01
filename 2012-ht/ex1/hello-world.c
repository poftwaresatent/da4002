/* 
 * This file can be compiled using:
 *
 *   gcc -o hello-world hello-world.c
 *
 * In order to run the resulting executable, type ./ followed by the
 * executable file name (you have to be in the directory where the
 * file is stored for this to work):
 *
 *   ./hello-world
 */


/*
 * Lines beginning with # are pre-processor commands. The
 * pre-processor prepares the source file for compilation, for example
 * to define compile-time constants and to include function
 * declarations. Those two are also the most frequently encountered.
 *
 * The line below tells the pre-processor to find the file called
 * stdio.h underneath the standard library search path, and then to
 * copy-paste it into this source file. The stdio.h file is a
 * so-called header, which in this case defines many functions (and
 * other things) that are needed to access the standard input-output
 * library. This allows the current source file to use functions such
 * as printf() without defining them.
 */
#include <stdio.h>


/*
 * Every executable written in C has to have one main function with a
 * declaration like the one below. This is a convention used by the
 * operating system (OS), which will search this function in the
 * compiled executable, and call it, when the application is
 * launched. Thus, the main function is an automatic connection
 * between the application and the OS.
 */
int main(int argc, char ** argv)
{
  
  /* A typical main() will initialize the application, call
     subroutines to perform the actual work, and clean up after itself
     before exiting. But here, there is just a single function call to
     the standard input/output library. The printf() function converts
     its arguments to the standard output stream (which is called
     stdout). The OS takes care of connecting stdout to the terminal
     where the application was launched, so whenever printf() is
     called there will be messages written on the terminal.
     
     In the most simple example, printf() takes a single string and
     writes it as-is to stdout. Note that the terminal needs to be
     specifically instructed when a new line should be opened, which
     is achieved by placing the special two-character code \n into the
     string. Such two-character codes that begin with a backslash are
     called escape-sequence, they are translated by the C-compiler
     into character codes that signify special commands for the
     terminal.
  */
  printf("hello, world\n");
  
  
  /* When main() is finished, it returns an exit code (a single
     integer) to the OS, which then shuts down the application. It is
     customary to return a zero, unless something went wrong in your
     application.
  */
  return 0;
}
