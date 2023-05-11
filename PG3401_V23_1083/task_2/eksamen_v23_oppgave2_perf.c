/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
--------------------------------------------------------------------------------

Project			:	TASK 2 - File Management and Functions (EXAM)
Author			:	Candidate number 1083
Revision			:	2.0
Description		:	Function for isPerfectNumber

--------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////*/

// INCLUDE HEADER FILE isPerfectNumber
#include "eksamen_v23_oppgave2_perf.h"

/* FUNCTION ------------------------------------------------------------------*/
/* This function uses a for loop to iterate through the numbers 1 to n-1 and 
checks if each number is a divisor of n. If it is, it adds the divisor to a 
sum. After the loop finishes, the function checks if the sum of the divisors is
equal to n. If it is, the function returns true (1), indicating that n is a 
perfect number. If the sum is not equal to n, the function returns false (0), 
indicating that n is not a perfect number.*/

bool isPerfectNumber(int n) {
   int sum = 0;
   for (int i = 1; i < n; i++) {
      if (n % i == 0) {
         sum += i;
      }
   }
   return (sum == n);
}

/* End of file ---------------------------------------------------------------*/
