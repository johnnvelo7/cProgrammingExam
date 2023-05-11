/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
--------------------------------------------------------------------------------

Project			:	TASK 3 - Flight Departures (EXAM)
Author			:	Candidate number 1083
Revision			:	5.0
Description		:	Header file for database.c

--------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////*/

#ifndef __TASK2_DATABASE_H__
#define __TASK2_DATABASE_H__

//Defining my maximum size for the integers and string
#define MAX_USERNAME		21
#define MAX_FLIGHTID 	7
#define MAX_DESTNAME 	4
#define MAX_BUFFERSZ		32

#define OK 					0
#define ERROR				1

//STANDARD C LIBS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* STRUCTS--------------------------------------------------------------------*/
//struct for my single linked list
typedef struct _PASSENGER {
	int iSeatNumber;
	int iAge;
	char szUserName[MAX_USERNAME];
	struct _PASSENGER *pNext;
} PASSENGER;

//Structs for my double linked list
typedef struct _FLIGHT {
	int iTime;
	int iSeats;
	char szFlight_Id[MAX_FLIGHTID];
	char szDestinationName[MAX_DESTNAME]; 
	PASSENGER *pPassengers;
	struct _FLIGHT *pNext;
	struct _FLIGHT *pPrev;
} FLIGHT;

typedef struct _FLIGHTDATABASE {
	struct _FLIGHT *pHead;
	struct _FLIGHT *pTail;
	int iCount;
} FLIGHTDATABASE;

/* PROTOTYPES-----------------------------------------------------------------*/

void printMenuScreen();
void clearScreen();
void promptEnterKey();
FLIGHT *createFlight(char *szFlight_Id, char *szDestinationName, 
int iSeats, int iTime);
void addFlight(FLIGHTDATABASE *pDatabase, FLIGHT *pNew_flight);
void printFlightByCriteria(FLIGHTDATABASE *pDatabase, 
int iCriteriaType, int iValue);
PASSENGER *createPassenger(const char *szUserName, 
int iAge, int iSeat_number);
void addPassenger(FLIGHT *pFlight, PASSENGER *pNew_passenger);
void deleteFlight(FLIGHTDATABASE * pDatabase, int iIndex);
void deletePassenger(FLIGHT *pFlight, int iSeatNumber);
void changeSeat(FLIGHT *pFlight, int iOld_seat_number, int iNew_seat_number);
void searchPassenger(FLIGHTDATABASE *pDatabase, char *szUserName);
int findPassengerIndex(FLIGHT* pFlight, int iSeatNumber);
FLIGHT *getFlight(FLIGHTDATABASE *pDatabase, int iIndex);
void sortPassengers(FLIGHT *pFlight);
int hasPassengers(FLIGHT *pFlight);
PASSENGER *findPassengerBySeatNumber(FLIGHT *pFlight, int iSeatNumber);
void freeFlights(FLIGHTDATABASE *pDatabase);

#endif // __TASK3_DATABASE_H__
/* End of file ---------------------------------------------------------------*/

