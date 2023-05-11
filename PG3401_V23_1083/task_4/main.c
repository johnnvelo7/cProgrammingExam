/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
--------------------------------------------------------------------------------

Project			:	TASK 4 - Threads (EXAM)
Author			:	Candidate number 1083
Revision			:	3.0
Description		:	Main Function for Threads

--------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////*/

// STANDARD C LIBS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <ctype.h>
#include <time.h>

// INCLUDE HEADER FILE FOR THREADS.C
#include "threads.h"

/*MAIN-FUNCTION --------------------------------------------------------------*/

int main(int iArgC, char *apszArgV[]){

	// Simple code to check run time in C
	double dTimeSpent = 0.0;
	clock_t begin = clock();
	
	clearScreen();
	printf("---------------------------------------------\n");
	printf("                T H R E A D S                \n");
	printf("---------------------------------------------\n");
	// Check if there is a file provided by the user
   if (iArgC < 2){
   	printf("Usage: %s filename\n", apszArgV[0]);
      return ERROR;
   }
   
   // Allocate and initialize memory buffers
   THREADS *pThreadArg = NULL;
   pThreadArg = malloc(sizeof(THREADS));
   pthread_t pThreads[NUM_THREADS] = {0};
   sem_t psemFull = {0};
   sem_t psemEmpty = {0};
   pthread_mutex_t pmutex = {0};
   
/* Initialize semaphore and mutex.
   Semaphores only shared between threads with same process */
   sem_init(&psemFull, 0, 0); //0 means semaphore will be locked until released
   sem_init(&psemEmpty, 0, 1); //1 sempahore is unlocked and can be acquired
   pthread_mutex_init(&pmutex, NULL);
   
   // Allocate and initialize memory buffers using malloc() 
   pThreadArg -> iCount = (int *)malloc(LETTER_RANGE * sizeof(int));
   pThreadArg -> iWordCount = (int *)malloc(TOTAL_WORDS * sizeof(int));
   pThreadArg -> szBuffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
   
   // Initialize memory buffers to 0
   memset(pThreadArg -> iCount, 0, LETTER_RANGE * sizeof(int));
   memset(pThreadArg -> iWordCount, 0, TOTAL_WORDS * sizeof(int));
   memset(pThreadArg -> szBuffer, 0, BUFFER_SIZE * sizeof(char));
   
   // Check if any of the memory buffers failed to allocate 
   if (!pThreadArg -> iCount || !pThreadArg -> iWordCount || // Continue line
   !pThreadArg -> szBuffer){
   	perror("Failed to allocate memory buffer");
      return ERROR;
   }
   
   // Set the file name and other thread arguments
   pThreadArg -> szFileName = apszArgV[1];
   pThreadArg -> pFile = NULL;
   pThreadArg -> psemFull = &psemFull;
   pThreadArg -> psemEmpty = &psemEmpty;
   pThreadArg -> pmutex = &pmutex;
   pThreadArg -> iReadBytes = 0;
   
   // Create threads
   if (createThreads(pThreads, pThreadArg) != OK) {
   	perror("Could not create threads");
      return ERROR;
   }
   
   // Wait for threads to finish
   if (joinThreads(pThreads) != OK) {
   	perror("Could not join threads");
      return ERROR;
   }
   
   // Print letter count using my function
	printLetterCount(pThreadArg -> iCount);
	
   // Print the word count using my function
   char *apszWords[TOTAL_WORDS] = {"and", "at", "it", "my", "Hamlet", "the"};
 	printWordCount(pThreadArg -> iWordCount, (const char **) apszWords);
 	
	// Destory and free threads
   sem_destroy(&psemFull);
   sem_destroy(&psemEmpty);
   pthread_mutex_destroy(&pmutex);
   free(pThreadArg -> szBuffer);
   free(pThreadArg -> iCount);
   free(pThreadArg -> iWordCount);
   free(pThreadArg);
   
   // End the runtime check code and print the result
   clock_t end = clock();
   dTimeSpent += (double)(end - begin) / CLOCKS_PER_SEC;
   printf("\nElapsed time is %f seconds\n", dTimeSpent);
   return OK;
}
/* End of file ---------------------------------------------------------------*/

