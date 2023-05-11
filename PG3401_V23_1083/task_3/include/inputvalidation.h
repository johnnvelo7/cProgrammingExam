/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
--------------------------------------------------------------------------------

Project			:	TASK 3 - Flight Departures (EXAM)
Author			:	Candidate number 1083
Revision			:	5.0
Description		:	Header file for inputvalidation.c

--------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////*/

#ifndef __TASK2_INPUTVALIDATE_H__
#define __TASK2_INPUTVALIDATE_H__

// STANDARD C LIBS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//Include database.h so that inputvalidation.c can access the lists
#include "database.h"

/* PROTOTYPES-----------------------------------------------------------------*/

bool isValidFlightID(const char *szBuffer);
bool isValidDestination(const char *szBuffer);
bool isValidSeats(const char *szBuffer);
bool isValidTime(const char *szBuffer);
bool isValidPassengerName(const char *szBuffer);
bool isValidAge(const char *szBuffer);
bool isNoFlightsRegistered(const FLIGHTDATABASE *pFlightList);

//Used const to make sure that my user validation variables does not change
const char *getUserInput(char *szBuffer, int iBufferSize,
const char *pPrompt, bool to_upper);
const char *getValidInput(const char *pPrompt, bool(*pValidator)
(const char *));

#endif // __TASK3_INPUTVALIDATE_H__
/* End of file ---------------------------------------------------------------*/
