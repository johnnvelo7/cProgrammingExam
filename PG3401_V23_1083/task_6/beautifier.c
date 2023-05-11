/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
--------------------------------------------------------------------------------

Project			:	TASK 6 - Code Beautifier (EXAM)
Author			:	Candidate number 1083
Revision			:	3.0
Description		:	Formatter functions for task 6

--------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////*/

// INCLUDE HEADER FILE FOR THREADS.C
#include "beautifier.h"

/* FUNCTION ------------------------------------------------------------------*/
/* This is my take on the function that replaces every occurences of three
	consecutive spaces into a single tab "\t". */
	
void ReplaceThreeSpaces(char *pszLine) {
	
	// Initialize my pointers and local variables to 0 and NULL
   char *pTemp = NULL; // This is a pointer used to traverse the string
   size_t stLineLen = 0; // Length of the input string
   size_t stNumberOfCharsToMove = 0; // Number of characters to move after tab
   
   // Initialize the pointer to the start of the input string
   pTemp = pszLine;
   
   // Get the length of the input string
   stLineLen = strnlen(pszLine, MAX_LENSIZE); 
   
/* Loop through the input string and replace every 3 spaces with a Tab "\t" 
   using "strstr" function. It searches the input string and returns the 
   pointer to the first occurrences of the given substring, in this case "   "*/
   
   while ((pTemp = strstr(pTemp, "   ")) != NULL) {
   	*pTemp = '\t';
   	// Calculate the number of characters to move after replacing with a tab
      stNumberOfCharsToMove = strnlen // Continue to next line
      (pTemp + 3, stLineLen - (pTemp - pszLine) - 3) + 1;
      // Move the remaining characters after replacing the 3 spaces
      memmove(pTemp + 1, pTemp + 3, stNumberOfCharsToMove);
	}
}

/* FUNCTION ------------------------------------------------------------------*/
/* This is my take on the function that applies Hungarian Notation on every 
	occurrence of "unsigned int" variables.*/
	
void ApplyHungarianNotation(char *pszLine) {

	// Initialize my pointers and local variables to 0 and NULL
	const char *pPattern = "unsigned int "; // String pattern to search for
   char *pTemp = NULL; // This is a pointer used to traverse the string
   size_t stLineLen = 0; // Length of the input string
   size_t stNumberOfCharsToMove = 0; // Number of characters to move after tab
    
   // Initialize the pointer to the start of the input string
   pTemp = pszLine;

   // Get the length of the input string
   stLineLen = strnlen(pszLine, MAX_LENSIZE); 
   
/* Loop through the input string and apply Hangarian Notation to every occurence
  	of "unsigned int". It searches the input string and replaces the variables
  	by calculating the position, and adding "ui" at the start, and changing the
  	first character to uppercase. 
  	
  	15 = Fifteen bytes from "unsigned int ui"
  	13 = Number of characters needed to be moved to make room for "ui"
  	11 = Eleven bytes from string "unsigned int" excluding trailing space */
   
   while ((pTemp = strstr(pTemp, pPattern)) != NULL) {
   	// Calculate the number of characters to move after applying the function
   	stNumberOfCharsToMove = strnlen(pTemp + 11, // Continue to next line
      stLineLen - (pTemp - pszLine) - 11) + 1;
      
      // Move the remaining characters to their new position
      memmove(pTemp + 13, pTemp + 11, stNumberOfCharsToMove);
      // Insert "ui" at the beginning, and make the first character capitalized
      strncpy(pTemp, "unsigned int ui", 15);
      pTemp[15] = toupper(pTemp[15]);
      // Finally, move the pointer back at the end of the variable
      pTemp += 15;
	}
}

/* FUNCTION ------------------------------------------------------------------*/
/*	This is my take on the function that converts every simple while loops into
	a for loop. This function searches for a pattern, and then tries to apply the
	for-loop format in my simple while loop program.
	
	DISCLAIMER: This function is designed to convert my simple while loop
					program, and may not work on other and more complex while loops
*/

int ReplaceWhileLoops(char *pszLine) {

   // Initialize pointers and local variable to NULL or 0 
   char *pOpenParenthesis = NULL; // Pointer for open parenthesis
   char *pClosePaenthesis = NULL; // Pointer for close parenthesis 
   char *pLessThanSign = NULL; // Pointer for "<" less than sign
   char *pWhilePattern = NULL; // Pointer for the "while" string
   static int siFoundWhileLoop = 0; // Flag indicating that while loop is found
	static char scLoopVar[MAX_VARSIZE] = {0}; // Buffer to store variable name
   static char scLoopLimit[MAX_VARSIZE] = {0}; // Buffer to store limit value
   size_t stLineLen = 0; // Length of the input string
   size_t stRemainingSpace = 0; // Remaining spaces in the input string

	// If a while loop has not yet been found, try to find from input string
	if (!siFoundWhileLoop) {
   	// Search for the "while" keyword in the input string
   	pWhilePattern = strstr(pszLine, "while");
   	
   	// If keyword "while" was found, parse the loop variable and limit
      if (pWhilePattern) {
			pOpenParenthesis = strchr(pszLine, '(');
      	pClosePaenthesis = strchr(pszLine, ')');
         pLessThanSign = strchr(pszLine, '<');
         
         // If parsing was successfull, replace the while loop with for loop
			if (pOpenParenthesis && pClosePaenthesis && pLessThanSign && //continue
         pLessThanSign > pOpenParenthesis && pClosePaenthesis > pLessThanSign) {
         	// Set the flag to 1, indicating the while loop has been found
         	siFoundWhileLoop = 1;
         	
         	// Parse the loop variable and limit values from the while loop
            sscanf(pOpenParenthesis + 1, "%31[^<]< %31[^)]", // Continue line
            scLoopVar, scLoopLimit);

				// Replace the while loop with equivalent for loop
            snprintf(pszLine, MAX_LENSIZE, "   for (%s = 0; %s < %s; %s++) {\n",
            scLoopVar, scLoopVar, scLoopLimit, scLoopVar);
            // Return OK if the input string has been modified
            return OK;
            }
			}
	}
	
/* If the while has been found and modified, skip the "i++;" pszLine inside
	the while loop, as it's already handled in the for loop */
	if (siFoundWhileLoop && strstr(pszLine, "++;") != NULL) {
	
		// Reset the flag to 0 to indicate that while loop has ended
   	siFoundWhileLoop = 0;
   	
   	// Indicate that the input string has been modified
      return OK;
	}
	
/*	If a while loop has been found and modified, append the closing brackets for
	the for loop */
   // Check if we've reached the end of the while loop
   if (siFoundWhileLoop && strstr(pszLine, "}") != NULL) {
   
		// Reset the flag to 0 to indicate that while loop has ended
   	siFoundWhileLoop = 0;
   	
      // Append the closing brace to the for loop and return OK if successfull
      stLineLen = strnlen(pszLine, MAX_LENSIZE);
      stRemainingSpace = MAX_LENSIZE - stLineLen - 1;
      strncat(pszLine, "}\n", stRemainingSpace);
      return OK;
   }
   
   // If nothing matched, return ERROR
   return ERROR;
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
