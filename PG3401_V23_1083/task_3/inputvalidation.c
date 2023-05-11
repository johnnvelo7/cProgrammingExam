/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
--------------------------------------------------------------------------------

Project			:	TASK 3 - Flight Departures (EXAM)
Author			:	Candidate number 1083
Revision			:	5.0
Description		:	inputvalidation.c for Flight Departure task

--------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////*/

// INCLUDE HEADER FILE FOR INPUTVALIDATION.C
#include "inputvalidation.h"

/* FUNCTION ------------------------------------------------------------------*/

/* This function takes szBuffer as input and returns a boolean valule checking
if the input string has a valid ID format. The ID format I made for the app was
3 letters followed by 3 numbers like for example: SAS123, NOR143 etch...*/
bool isValidFlightID(const char *szBuffer) {

   // Check flight ID format
   if (strnlen(szBuffer, MAX_BUFFERSZ) != 6 	// Check if length is 6
  	|| !isupper(szBuffer[0])						// Check if 1st char is uppercase
  	|| !isupper(szBuffer[1]) 						// Check if 2nd char is uppercase
  	|| !isupper(szBuffer[2]) 						// Check if 3rd char is uppercase
  	||	!isdigit(szBuffer[3]) 						// Check if 4th char is digit
  	|| !isdigit(szBuffer[4]) 						// Check if 5th char is digit
  	|| !isdigit(szBuffer[5])) {					// Check if 6th char is digit
  	
  	// If result is not valid, return false
      return false;
   }
   
   // Otherwise return true if szBuffer is valid format for flight ID
   return true;
}

/* FUNCTION ------------------------------------------------------------------*/

/* This function takes szBuffer as input and checks if the string has a valid
destination format. The format I chose for this app was three letters for 
example: OSL, TYO, SWE, CPH etch... Just like at the airport*/
bool isValidDestination(const char *szBuffer) {

   // Check if length of szBuffer is exactly 3 
   int iLen = strnlen(szBuffer, MAX_BUFFERSZ);
   if (iLen != 3) return false;
   
   // Loop through character and check if it is alphabet
   for (int i = 0; i < iLen; i++) {
   
   	// Return false if not valid
      if (!isalpha(szBuffer[i])) {
      	return false;
      }
   }
   
   // Otherwise return true if valid
   return true;
}

/* FUNCTION ------------------------------------------------------------------*/

/* This function takes szBuffer and checks if it's a valid number. The format I
chose for this app is a seat number from 1 to 100. This function returns true
if the input is valid, and false if not.*/
bool isValidSeats(const char *szBuffer) {

	// Convert szBuffer to digits and check if value is between 1 and 100
   int iSeats = atoi(szBuffer);
   if (iSeats < 1 || iSeats > 100) {
   
   	// Return false if seat number is invalid
   	return false; 
   }
   // Otherwise return true if valid
   return true;
}

/* FUNCTION ------------------------------------------------------------------*/

/* This function takes szBuffer and checks if it's a valid number. The format I
chose for time in this app is a 24 hour format (4 numbers). For exapmle: 1300,
1500, 1930 etch... This function returns true if the input is valid, and false 
if not.*/
bool isValidTime(const char *szBuffer) {
	
	// Get the length of the buffer by using strnlen
   int iLen = strnlen(szBuffer, MAX_BUFFERSZ);
   
   // If the szBuffer is not equals to 4, return false
   if (iLen != 4){
   	return false;
   }
   
   // Loop through each character in the szBuffer, if not digit, return false
   for (int i = 0; i < iLen; i++) {
      if (!isdigit(szBuffer[i])){
      	return false;
      }
   }
   
   // Extract the hour and minute values from the szBuffer
   int iHour = (szBuffer[0] - '0') * 10 + (szBuffer[1] - '0');
   int iMinute = (szBuffer[2] - '0') * 10 + (szBuffer[3] - '0');
   
   // If neither iHour nor iMinute in range, return false
   if (iHour < 0 || iHour >= 24 || iMinute < 0 || iMinute >= 60){
   	return false;
   }
   
   // Otherwise return true if szBuffer is valid time in 24h format
   return true;
}

/* FUNCTION ------------------------------------------------------------------*/

/* This function takes szBuffer and checks if it's a valid string. The format I
chose for passenger's last name in 'this app is just a normal string with max
21 character -1 for zero-termination. This function returns true
if the input is valid, and false if not.*/
bool isValidPassengerName(const char *szBuffer) {

	// Get the length of the szBuffer and check if between 1 and 20 chars
   int iLen = strnlen(szBuffer, MAX_BUFFERSZ);
   
   // If invalid, return false
   if (iLen < 1 || iLen > 20){
   	return false;
   }
   
   // If valid, loop though each character and check if is alphabet
   for (int i = 0; i < iLen; i++) {
      if (!isalpha(szBuffer[i])) {
      	return false;
      }
   }
   
   // Otherwise return true if valid
   return true;
}

/* FUNCTION ------------------------------------------------------------------*/

/* This function takes szBuffer and checks if it's a valid string. The format I
chose for age in this app is just a number from 1 to 99. This function returns 
true if the input is valid, and false if not.*/
bool isValidAge(const char *szBuffer) {

	// Get the length of the szBuffer using strnlen
   int iLen = strnlen(szBuffer, MAX_BUFFERSZ);
   
   // Check if szBuffer length is between 2 and 3, if invalid return false
   if (iLen < 2 || iLen > 3){
   	return false;
   }
   
   // Loop through the characters and check if isdigit, return false if invalid
   for (int i = 0; i < iLen; i++) {
   	if (!isdigit(szBuffer[i])){
   		return false;
   	}
   }
   
   // Check if integer value of szBuffer is between 18 and 99
   int iAge = atoi(szBuffer);
   if (iAge < 18 || iAge > 99){
   	return false;
   }
   
   // Otherwise return true if valid
   return true;
}

/* FUNCTION ------------------------------------------------------------------*/

/* This function takes a character pointer (szBuffer), buffer size, a prompt, 
and a boolean value to_upper as input. It asks the user and retrieves the input 
by fgets function. The newline character is removed by using "strcspn", and then 
finally the input converts lowercase characters to uppercase by using "to_upper"
function. The result is then returned as a constant character pointer. */
const char *getUserInput(char *szBuffer, int iBufferSize, // Continue line
const char *pPrompt, bool to_upper) {

	// Print the prompt message for the user
   printf("%s", pPrompt);
   
   // Read input from the user using fgets and remove newline character
   fgets(szBuffer, iBufferSize, stdin);
   szBuffer[strcspn(szBuffer, "\n")] = 0;
   
   // Convert szBuffer to uppercase
   if (to_upper) {
      for (int i = 0; i < strnlen(szBuffer, MAX_BUFFERSZ); i++) {
         if (islower(szBuffer[i])) {
            szBuffer[i] = toupper(szBuffer[i]);
         }
      }
   }
   
   // Return the user input
   return szBuffer;
}

/* FUNCTION ------------------------------------------------------------------*/

// This function checks if the flight is empty
bool isNoFlightsRegistered(const FLIGHTDATABASE *pFlightList) {

	// Check if the number of flights in the list is 0. If 0, display a message
   if (pFlightList -> iCount == 0) {
   	printf("There are no flights registered.\n");
   	
   	// Ask the user to press "Enter" to continue
      promptEnterKey();
      return true;
   }

   // Otherwise return true if flight is not empty
   return false;
}


/* FUNCTION ------------------------------------------------------------------*/

/* This function takes a prompt string and a function pointer to a validator as
an input. The function creates a static character buffer to store the user input
inside. The function then calls the validator function with the input string as
an argument to check if the input is valid. If the input is invalid, it prints 
an error message and asks the user again to input a valid one. Finally, valid
input stored from the szBuffer is returned*/

/*The reason why I chose to make a static char szBuffer[MAX_BUFFERSZ] is to make
the buffer persistent across multiple function calls. By doing this, the same 
buffer is reused each time "getValidInput" function is called, instead of 
creating a new buffer and allocating memory for szBuffer each time the function
is called.*/
const char *getValidInput(const char *pPrompt, bool(*pValidator)
(const char *)) {

	// Declare a static variable to store the user input into a buffer
   static char szBuffer[MAX_BUFFERSZ];
   
   // Initialize the validInput to false
   bool validInput = false;
   
   // Loop until the user inputs a valid input
   while (!validInput) {
   	
   	// Get the user input using the getUserInput function
   	getUserInput(szBuffer, sizeof(szBuffer), pPrompt, true);
   	
   	// Validate the user input using the pValidator function
      validInput = pValidator(szBuffer);
      
      // If invalid input, display a simple error message
      if (!validInput){
      	printf("Invalid input. Please try again.\n");
      }
   }
   
   // Otherwise return the validated user input
   return szBuffer;
}

/* End of file ---------------------------------------------------------------*/
