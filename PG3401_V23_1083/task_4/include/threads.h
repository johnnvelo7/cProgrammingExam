/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
--------------------------------------------------------------------------------

Project			:	TASK 4 - Threads (EXAM)
Author			:	Candidate number 1083
Revision			:	3.0
Description		:	Header file for threads.c

--------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////*/

#ifndef __TASK4_THREADS_H__
#define __TASK4_THREADS_H__

// DEFINE
#define BUFFER_SIZE 		4096
#define NUM_THREADS 		2
#define LETTER_RANGE 	95 // printable characters
#define TOTAL_WORDS 		6
#define OK 					0
#define ERROR 				1

// STANDARD C LIBS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
#include <semaphore.h>

/* STRUCTS--------------------------------------------------------------------*/

typedef struct _THREADS {
	char *szBuffer;	
	char *szFileName;
	int *iCount;
	int *iWordCount;
	int iReadBytes;
	FILE *pFile;
	sem_t *psemFull;
	sem_t *psemEmpty;
	pthread_mutex_t *pmutex;
} THREADS;


/* PROTOTYPES-----------------------------------------------------------------*/
// Functions for Thread A and Thread B
void *readThreads(void *pArg);
void *countThreads(void *pArg);

// Functions I created to make main function shorter
int createThreads(pthread_t *pThreads, THREADS *pThreadArg);
int joinThreads(pthread_t *pThreads);
void printLetterCount(const int *iCount);
void printWordCount(const int *iWordCount, const char **apszWords);
void clearScreen();

#endif // __TASK4_THREADS_H__

/* End of file ---------------------------------------------------------------*/
