/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
--------------------------------------------------------------------------------

Project			:	TASK 6 - Code Beautifier (EXAM)
Author			:	Candidate number 1083
Revision			:	3.0
Description		:	Main Function for Code Beautifier

--------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////*/

// INCLUDE HEADER FILE FOR THREADS.C
#include "beautifier.h"

/*MAIN-FUNCTION --------------------------------------------------------------*/

/*	This is my simple main function that opens the source file, apply the changes
	and then save it to the same name but ends with "_beautified.c". 
	In my main function, it combines all the three functions that converts 
	while loops to for loop, apply Hungarian Notation, and lastly, convert 
	three spaces with a single tab. */
	
int main(int iArgC, char *apszArgV[]) {

	// Simple welcome screen
	clearScreen();
	printf("---------------------------------------------\n");
	printf("        C O D E   B E A U T I F I E R        \n");
	printf("---------------------------------------------\n");

	// Initialize and my pointers and local variables to 0 and NULL
	FILE *pFileInput = NULL;
	FILE *pFileOutput = NULL;
	size_t stOutputFileLen = 0;
	char szLine[MAX_LENSIZE] = {0};
	
	// Check if the user has provided valid arguments
   if (iArgC < 2) {
   	fprintf(stderr, "Usage: %s <source_file.c>\n", apszArgV[0]);
      return ERROR;
   }

	// Open source file for reading
   pFileInput = fopen(apszArgV[1], "r");
   if (!pFileInput) {
   	perror("Error opening input file");
      return ERROR;
   }

	// Calculate the length of the output filename and create a new filename
   stOutputFileLen = strnlen(apszArgV[1], MAX_LENSIZE) + 13;
	char szOutputFileName[stOutputFileLen];
   snprintf(szOutputFileName, stOutputFileLen, "%.*s_beautified.c",
   (int)(strnlen(apszArgV[1], MAX_LENSIZE) - 2), apszArgV[1]);

	// Open the output file for writing
   pFileOutput = fopen(szOutputFileName, "w");
   if (!pFileOutput) {
   	perror("Error opening output file");
      fclose(pFileInput);
      return ERROR;
   }
 
 	// Read each line of the input file and apply various functions
   while (fgets(szLine, sizeof(szLine), pFileInput)) {
   	ApplyHungarianNotation(szLine); // Apply Hungarian Notation Function
      ReplaceThreeSpaces(szLine); // Replace Three Spaces function
      if (!ReplaceWhileLoops(szLine)) { // Replace while loops with for loops
      	fputs(szLine, pFileOutput); // Write the modified line to the output
      } else {
      	fputs(szLine, pFileOutput); // Write the unmodified line to the output
      }
   }
   
   // Close the input and output files
   fclose(pFileInput);
   fclose(pFileOutput);
   
  	// Simple print statement telling the user that the program is done running
   printf("\nFile has been successfully printed to -> %s_beautified.c.\n",
   strtok(apszArgV[1], "."));
   // If everything was successfull, return OK
   return OK;
}

/* End of file ---------------------------------------------------------------*/

