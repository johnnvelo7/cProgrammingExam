/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
--------------------------------------------------------------------------------

Project			:	TASK 2 - File Management and Functions (EXAM)
Author			:	Candidate number 1083
Revision			:	2.0
Description		:	Header file for main.c

--------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////*/

#ifndef __TASK2_H__
#define __TASK2_H__

// DEFINES
#define OK 		0
#define ERROR	1

// STANDARD C LIBS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// LOCAL INCLUDE
#include "main.h"
#include "eksamen_v23_oppgave2_fib.h"
#include "eksamen_v23_oppgave2_prim.h"
#include "eksamen_v23_oppgave2_kvad.h"
#include "eksamen_v23_oppgave2_cube.h"
#include "eksamen_v23_oppgave2_perf.h"
#include "eksamen_v23_oppgave2_abun.h"
#include "eksamen_v23_oppgave2_def.h"
#include "eksamen_v23_oppgave2_odd.h"

/* STRUCTS--------------------------------------------------------------------*/

typedef struct _METADATA {
    int iIndex;
    int iNumber;
    bool bIsFibonacci;
    bool bIsPrimeNumber;
    bool bIsSquareNumber;
    bool bIsCubeNumber;
    bool bIsPerfectNumber;
    bool bIsAbundantNumber;
    bool bIsDeficientNumber;
    bool bIsOddNumber;
} METADATA;

/* PROTOTYPES-----------------------------------------------------------------*/

void clearScreen();
void writeBinaryNumber(FILE *pFile, int iNumber);

#endif // __TASK2_H__
/* End of file ---------------------------------------------------------------*/
