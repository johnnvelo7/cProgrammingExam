/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
--------------------------------------------------------------------------------

Project			:	TASK 2 - File Management and Functions (EXAM)
Author			:	Candidate number 1083
Revision			:	2.0
Description		:	Function for isCubeNumber

--------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////*/

// INCLUDE HEADER FILE isCubeNumber
#include "eksamen_v23_oppgave2_cube.h"

/* FUNCTION ------------------------------------------------------------------*/
/* This function first computes the cubic root of n using the cbrt function 
from the math.h library. It then checks if the cbrt of the cbrt root of n 
is equal to n. If it is, the function returns true (1), otherwise, it returns 
false (0)..*/

bool isCubeNumber(int n) {
   int cube_n = (int)cbrt(n);
   return (cube_n * cube_n * cube_n == n);
}

/* End of file ---------------------------------------------------------------*/
