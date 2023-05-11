/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
--------------------------------------------------------------------------------

Project			:	TASK 4 - Threads (EXAM)
Author			:	Candidate number 1083
Revision			:	3.0
Description		:	Threads function for task 4

--------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////*/

// INCLUDE HEADER FILE FOR THREADS.C
#include "threads.h"

/* FUNCTION ------------------------------------------------------------------*/
/* This function reads the words in the text file. This thread is first executed
by the main thread. It reads the file in binary mode, and then stores the data 
in a buffer until it's full. After the buffer is empty, it will then read more
data. When the reading is done, this thread will close the file, and notify the 
countThreads that reading is done.
*/
void *readThreads(void *pArg){
	// Initialize the pointer to NULL and cast the void pointer to struct type
   THREADS *pThreadArg = NULL; 
   pThreadArg = (THREADS *) pArg;
   
   // Open the file in binary mode
   pThreadArg -> pFile = fopen(pThreadArg -> szFileName, "rb");
   if (!pThreadArg -> pFile) {
   
   	// Simple error message if the file is invalid or cannot be opened
   	perror("Failed to open file");
      exit(EXIT_FAILURE);
   } 
   
   // Loop where the function starts
   while (1){
   
		// Wait for the empty semaphore to be signaled
  		sem_wait(pThreadArg -> psemEmpty);
  		
  		// Get the mutex lock to protect the shared resources
      pthread_mutex_lock(pThreadArg -> pmutex);  
      
      // Read from file into the buffer
      pThreadArg -> iReadBytes = fread(pThreadArg -> szBuffer, 1, // Continue
      BUFFER_SIZE, pThreadArg -> pFile);
      
      // If EOF is reached, unlock the mutex and break out of the loop
      if (pThreadArg -> iReadBytes <= 0){
      	pthread_mutex_unlock (pThreadArg -> pmutex);
         break;
      }
      
      // Release the mutex lock
      pthread_mutex_unlock(pThreadArg -> pmutex);
      
      // Signal the semaphore that the buffer is now full
      sem_post (pThreadArg -> psemFull);
	}
	
	// Close the file from main function
   fclose (pThreadArg -> pFile);
   
   // Notify the counting thread that read is done
   sem_post (pThreadArg -> psemFull); 
   pthread_exit(NULL);
}

/* FUNCTION ------------------------------------------------------------------*/

void *countThreads(void *pArg){

    // Initialize the pointer to NULL and cast the void pointer to struct type
    THREADS *pThreadArg = NULL;    
    char *szBinaryData = NULL;
    char *pSavePtr = NULL;
    char *szExtractedWords = NULL;
    pThreadArg = (THREADS *) pArg;

    // Define the words the task requires
    char *apszWords[TOTAL_WORDS] = {"and", "at", "it", "my", "Hamlet", "the"};

    // Loop where the function starts
    while (1) {
    
       // Wait for the full semaphore to be signaled
       sem_wait(pThreadArg -> psemFull);
       
       // Get the mutex lock to protect the shared resources 
       pthread_mutex_lock(pThreadArg -> pmutex);
        
       // If the readThreads is complete, unlock the mutex and exit the loop
       if (pThreadArg -> iReadBytes <= 0) {
       	pthread_mutex_unlock(pThreadArg -> pmutex);
         break;
       }
        
		// Create a null-terminated string from the binary data
      szBinaryData = malloc(pThreadArg -> iReadBytes + 1);
      strncpy(szBinaryData, pThreadArg -> szBuffer, pThreadArg -> iReadBytes);
      szBinaryData[pThreadArg -> iReadBytes] = '\0';

      // Count the printable 126 ASCII codes in the buffer 
      for (int i = 0; i < pThreadArg -> iReadBytes; i++) {
      	unsigned char c = pThreadArg -> szBuffer[i];
         if (c >= 32 && c <= 126) {
         
         	// Increment the count for the corresponding ASCII codes
            pThreadArg -> iCount[c - 32]++;
			}
		}

      // Extract the specific words and count them + use strtok_r for safer code
		szExtractedWords = strtok_r
		(szBinaryData, " \t\n\r.,;:!?-_\"\'", &pSavePtr);
		while (szExtractedWords != NULL) {
      	for (int w = 0; w < TOTAL_WORDS; w++) {
      	
         	// strcasecmp to match a case sensitive Word and increment
            if (strcasecmp(szExtractedWords, apszWords[w]) == 0) {
            	pThreadArg -> iWordCount[w]++;
            }
			}
			szExtractedWords = strtok_r(NULL, " \t\n\r.,;:!?-_\"\'", &pSavePtr);
		}
        
      // Release the mutex lock
      pthread_mutex_unlock(pThreadArg -> pmutex);
      
      // Signal the empty semaphore to indicate that the buffer is now empty
      sem_post(pThreadArg -> psemEmpty);

      // Free the allocated memory for the null-terminated binary data
      free(szBinaryData);
	}
   pthread_exit(NULL);
}


/* FUNCTION ------------------------------------------------------------------*/

// This function is used to create the threads and will be used in the main
int createThreads(pthread_t *pThreads, THREADS *pThreadArg){

	// Create thread A using readThreads function and pThreadArg as argument
	if (pthread_create(&pThreads[0], NULL, readThreads, // Continue next line
	(void *)pThreadArg)!= 0){
	
		// Simple error message if failed
  		perror("Could not create thread A");
      return ERROR;
   }
   
   // Create thread B using countThreads function and pThreadArg as argument
   if(pthread_create(&pThreads[1], NULL, countThreads, // Continue next line
   (void *)pThreadArg)!= 0){
   
   	// Simple error message if failed
   	perror("Could not create thread B");
      return ERROR;
   }
   return OK;
}

/* FUNCTION ------------------------------------------------------------------*/

// This is used to wait for two threads to be finished
int joinThreads(pthread_t *pThreads){

	// Used a for loop since the number of thread is known
   for (int i = 0; i < NUM_THREADS; i++){
   	if (pthread_join(pThreads[i], NULL) != 0){
   	
   		// Simple error if failed
      	perror("Could not join thread");
        	return ERROR;
      }
	}
   return OK;
}

/* FUNCTION ------------------------------------------------------------------*/

// This is used to prints the 126 ASCII characters
void printLetterCount(const int *iCount){
   printf("ASCII letters found:\n");
   printf("--------------------\n");
   // Search for the ASCII characters that are printable
   for (int i = 0; i < LETTER_RANGE; i++){
   
   	// isprint checks if that character is printable and prints it
   	if (isprint(i + 32)){
      	printf("%c: %d\n", i + 32, iCount[i]);
      }
   }
}

/* FUNCTION ------------------------------------------------------------------*/

/* This function is to print the counted words from the array. It takes two 
arguments, a pointer to an array of constant strings "apszWords", and an array 
of integers "iWordCount".*/
void printWordCount(const int *iWordCount, const char **apszWords){
	printf("\n---------------------\n");
   printf("Total count of words:\n");
   printf("---------------------\n");
   
   // It loops through iWordCount and prints each word.
   for (int i = 0; i < TOTAL_WORDS; i++){
   	printf("%s: %d\n", apszWords[i], iWordCount[i]);
   }
}

/* FUNCTION ------------------------------------------------------------------*/

// Clear screen function inspired from Cashier Register task
void clearScreen(){
	#ifdef _WIN32
	   system("cls");
	#else
	   system("clear");
	#endif
}


/* End of file ---------------------------------------------------------------*/

