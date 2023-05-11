/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
--------------------------------------------------------------------------------

Project			:	TASK 2 - File Management and Functions (EXAM)
Author			:	Candidate number 1083
Revision			:	2.0
Description		:	Function for isFibonacci

--------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////*/

// INCLUDE HEADER FILE isFibonacci
#include "eksamen_v23_oppgave2_fib.h"

/* FUNCTION ------------------------------------------------------------------*/
/* This function uses a while loop to iterate through the Fibonacci sequence 
until it either finds a number equal to n or a number greater than n. If a 
number equal to n is found, the function returns true (1), otherwise, it 
returns false (0).*/

bool isFibonacci(int n) {
   int a = 0, b = 1, c = a + b;
   while (c < n) {
      a = b;
      b = c;
      c = a + b;
   }
   return (c == n);
}

/* End of file ---------------------------------------------------------------*/
