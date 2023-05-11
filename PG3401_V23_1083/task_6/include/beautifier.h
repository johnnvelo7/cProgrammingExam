/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
--------------------------------------------------------------------------------

Project			:	TASK 6 - Code Beautifier (EXAM)
Author			:	Candidate number 1083
Revision			:	3.0
Description		:	Header file for beautifier.c

--------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////*/

#ifndef __TASK6_BEAUTIFIER_H__
#define __TASK6_BEAUTIFIER_H__

// DEFINES
#define MAX_LENSIZE 	1024
#define MAX_VARSIZE	32
#define OK 				0
#define ERROR 			1

// STANDARD C LIBS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* PROTOTYPES-----------------------------------------------------------------*/

void ReplaceThreeSpaces(char *line);
void ApplyHungarianNotation(char *line);
int ReplaceWhileLoops(char *line);
void clearScreen();

#endif // __TASK6_BEAUTIFIER_H__

/* End of file ---------------------------------------------------------------*/
