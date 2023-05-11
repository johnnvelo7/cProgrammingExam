/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
--------------------------------------------------------------------------------

Project			:	TASK 2 - File Management and Functions (EXAM)
Author			:	Candidate number 1083
Revision			:	2.0
Description		:	Function for isOdd

--------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////*/

// INCLUDE HEADER FILE isOdd
#include "eksamen_v23_oppgave2_odd.h"

/* FUNCTION ------------------------------------------------------------------*/
/* This function checks if the remainder of n divided by 2 is not equal to 0.
If it is not, the function returns true (1), indicating that n is an odd 
number. If the remainder is equal to 0, the function returns false (0), 
indicating that n is an even number.*/

bool isOdd(int n) {
   return (n % 2 != 0);
}

/* End of file ---------------------------------------------------------------*/
