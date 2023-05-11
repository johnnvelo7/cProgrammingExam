/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
--------------------------------------------------------------------------------

Project			:	TASK 2 - File Management and Functions (EXAM)
Author			:	Candidate number 1083
Revision			:	2.0
Description		:	Function for isSquareNumber

--------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////*/

// INCLUDE HEADER FILE isSquareNumber
#include "eksamen_v23_oppgave2_kvad.h"

/* FUNCTION ------------------------------------------------------------------*/
/* This function first computes the square root of n using the sqrt function 
from the math.h library. It then checks if the square of the square root of n 
is equal to n. If it is, the function returns true (1), otherwise, it returns 
false (0).*/

bool isSquareNumber(int n) {
   int sqrt_n = (int)sqrt(n);
   return (sqrt_n * sqrt_n == n);
}

/* End of file ---------------------------------------------------------------*/
