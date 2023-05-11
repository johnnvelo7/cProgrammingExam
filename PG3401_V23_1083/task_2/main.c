/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
--------------------------------------------------------------------------------

Project			:	TASK 2 - File Management and Functions (EXAM)
Author			:	Candidate number 1083
Revision			:	2.0
Description		:	Main Function for File Management and Functions task

--------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////*/

// INCLUDE HEADER FILE FOR MAIN.C
#include "main.h"

/*MAIN-FUNCTION --------------------------------------------------------------*/
int main(int iArgC, char *apszArgV[]) {

	// A simple welcome screen to make my app pleasant for the user
	clearScreen();
	printf("---------------------------------------------\n");
	printf("         N U M B E R   C H E C K E R         \n");
	printf("---------------------------------------------\n");
	
	// Initialize pointers and variables to null first before using them
   FILE *pInputFile = NULL;
   FILE *pOutputFile = NULL;
   METADATA *pMetadata = NULL;
   pMetadata = malloc(sizeof(METADATA));
   int iNum = 0;
   int iIndex = 1; // Start from 1 (the first number in the input file)
   
   // Open input and output file for reading and writing
   pInputFile = fopen("eksamen_v23_oppgave2.txt", "r");
   pOutputFile = fopen("output.txt", "w");

	// If file cannot be opened, display a simple error message
   if (pInputFile == NULL) {
   	printf("Error: Cannot open input file.\n");
      return ERROR;
   }

	// If file cannot be opened, display a simple error message
   if (pOutputFile == NULL) {
   	printf("Error: Cannot open output file.\n");
      fclose(pInputFile);
      return ERROR;
   }
    
   // Use fscanf to read integer input from the input file
   while (fscanf(pInputFile, "%d", &iNum) != EOF) {
   	// Simple print ---- to make the output file easier to read
      fprintf(pOutputFile, "-------------------------------------------------");
      fprintf(pOutputFile, "\n");
      
   /* The task asked for binary to be printed, but I printed the number as 
      well to make the user know which number is being tested. */
   	fprintf(pOutputFile, "Number: \t\t\t%d\n", iNum);
   	
   /* Here I set the metadata for the number based from the METADATA struct
   	using the "pMetadata pointer. */
      pMetadata -> iIndex = iIndex;
      pMetadata -> iNumber = iNum;
      pMetadata -> bIsFibonacci = isFibonacci(iNum);
      pMetadata -> bIsPrimeNumber = isPrime(iNum);
      pMetadata -> bIsAbundantNumber = isAbundantNumber(iNum);
      pMetadata -> bIsSquareNumber = isSquareNumber(iNum);
      pMetadata -> bIsCubeNumber = isCubeNumber(iNum);
      pMetadata -> bIsPerfectNumber = isPerfectNumber(iNum);
      pMetadata -> bIsDeficientNumber = isDeficientNumber(iNum);
      pMetadata -> bIsOddNumber = isOdd(iNum);

		// Print the metadata for the number based on the format of the struct
      fprintf(pOutputFile, "Index: \t\t\t%d\n", pMetadata -> iIndex);
      fprintf(pOutputFile, "Number (binary): ");
      writeBinaryNumber(pOutputFile, pMetadata -> iNumber);
      fprintf(pOutputFile, "\n");
      fprintf(pOutputFile, "-------------------------------------------------");
      fprintf(pOutputFile, "\n");      
      
	/* The fprintf function is printing the metadata information into the output
		file including the boolean value if the number has certain mathematical
		characteristics or not. It prints*/
      fprintf(pOutputFile, "Is Fibonacci: \t%s\n", pMetadata->bIsFibonacci ?
      "True" : "False");
      fprintf(pOutputFile, "Is Prime: \t\t%s\n", pMetadata->bIsPrimeNumber ?
      "True" : "False");
      fprintf(pOutputFile, "Is Abundant: \t%s\n", pMetadata->bIsAbundantNumber ?
      "True" : "False");
      fprintf(pOutputFile, "Is Squared: \t%s\n", pMetadata->bIsSquareNumber ?
      "True" : "False");
      fprintf(pOutputFile, "is Cube: \t\t%s\n", pMetadata->bIsCubeNumber ?
      "True" : "False");
      fprintf(pOutputFile, "is Perfect: \t%s\n", pMetadata->bIsPerfectNumber ?
      "True" : "False");
      fprintf(pOutputFile, "is Deficient: \t%s\n",pMetadata->bIsDeficientNumber?
      "True" : "False");
      fprintf(pOutputFile, "is Odd: \t\t\t%s\n", pMetadata->bIsOddNumber ?
      "True" : "False");
      
      // Print newline to make the output file easier to read
      fprintf(pOutputFile, "\n");
      // Index is incremented to move to the next number in the input file
      iIndex++;
   }
   
	// Simple print statement telling the user that the program is done running
   printf("\nFile has been successfully printed to -> output.txt.\n");

	// After everything, close the opened files and free the used pointer
   fclose(pInputFile);
   fclose(pOutputFile);
	free(pMetadata);
   return OK;
}

/* FUNCTION ------------------------------------------------------------------*/
/* This is a simple clear screen function that was inspired from the cashier
Register task. This function is used in the main to make the program cleaner */
 
void clearScreen(){
	#ifdef _WIN32
	   system("cls");
	#else
	   system("clear");
	#endif
}

/* FUNCTION ------------------------------------------------------------------*/
/* This is the function used to print the number into binary. It takes two
arguments, a pointer to a file and the value of the integer. The binary version 
of the given number is generated using the for loop below that iterates over 
each bit in the number. */

void writeBinaryNumber(FILE *pFile, int iNumber) {
	// Iterate over each bit in the number, starting from most significant bit
   for (int i = sizeof(int) * 8 - 1; i >= 0; i--) {
   	/* Check if the current bit is set by using a bitwise AND with a mask
   		that only has one bit set to "1". If the result of the AND operation
   		is a non-zero, the bit is set to "1", otherwise it is set to "0".  */
		fprintf(pFile, "%d", (iNumber & (1 << i)) ? 1 : 0);
   }
}

/* End of file ---------------------------------------------------------------*/

