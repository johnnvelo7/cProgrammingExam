/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
--------------------------------------------------------------------------------

Project          : TASK 3 - Flight Departures (EXAM)
Author           : Candidate number 1083
Revision         : 5.0
Description      : Main.c for Flight Departure task

--------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////*/

//STANDARD C LIBS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//INCLUDE CUSTOM HEADER FILES 
#include "database.h"
#include "inputvalidation.h"

//ENUM FOR MENUSELECTION
enum MENUSELECTION {
	MENU_UNINITIALIZED = 0,
	MENU_ADDFLIGHT = 1,
	MENU_ADDPASSENGER = 2,
	MENU_PRINTFLIGHT = 3,
	MENU_FINDFLIGHTBYTIME = 4,
	MENU_DELETEFLIGHT = 5,
	MENU_DELETEPASSENGER = 6,
	MENU_CHANGESEAT = 7,
	MENU_SEARCHPASSENGER = 8,
	MENU_EXIT = 9
};

enum MENUSELECTION ___getch();

/*MAIN-FUNCTION---------------------------------------------------------------*/

int main(int iArgC, char * apszArgV[]) {
	//Structs and Pointers set to NULL and 0
	enum MENUSELECTION eMenu = MENU_UNINITIALIZED;
	FLIGHTDATABASE flightList = { .pHead = NULL, .pTail = NULL, .iCount = 0 };
	FLIGHTDATABASE *pDatabase = &flightList;
	FLIGHT *pFlight = NULL;
	PASSENGER* pNewPassenger = NULL;
	char szFlight_Id[MAX_FLIGHTID] = {0};
	char szDestinationName[MAX_DESTNAME] = {0};
	char szBuffer[MAX_BUFFERSZ] = {0};
	int iFlightIndex = 0;
	int iPassengerIndex = 0;
	int iSeats = 0;
	int iSeatNumber = 0;
	int oldSeatNumber = 0;
	int newSeatNumber = 0;
	int c = 0;
	int iAge = 0;
	int iTime = 0;
	int iHour = 0;
	int iMinute = 0;
	int iConfirm = 0;
 
/*START-OF-SWITCH-CASE--------------------------------------------------------*/
 
	do {
		clearScreen();
		printMenuScreen();
		eMenu = ___getch();
		switch (eMenu) {
      
/*CASES-ONE-------------------------------------------------------------------*/

		case MENU_ADDFLIGHT:
			/* First, clear the memory allocated for the flight ID and destination 
			to avoid any garbage data. In this case, I used szFlight_Id and 
			szDestinationName to get the user input, instead of just using 
			szBuffer. I did this to easily differentiate between the two strings.*/
			memset(szFlight_Id, 0, sizeof(szFlight_Id));
			memset(szDestinationName, 0, sizeof(szDestinationName));
			
			/* Then ask the user to enter flight ID, and validate its input using
			the "getValidInput" function from inputvalidation.c */
			printf("\n");
			strncpy(szFlight_Id, getValidInput //continue to next line
			("Enter flight ID (3 uppercase letters followed by 3 digits): ", 
			isValidFlightID), sizeof(szFlight_Id));
			
			// Ask the user about destination name and validate the input format
			strncpy(szDestinationName, getValidInput( //continue to next line
			"Enter destination (3 letters only, ex. OSL, SWE, or CPH): ", 
			isValidDestination), sizeof(szDestinationName));
			
			// Ask the user about how many seats and validate the input format
			iSeats = atoi(getValidInput( //continue to next line
			"Enter number of seats (1-10): ", isValidSeats));
			
			// Ask the user about departure time and validate the input format
			iTime = atoi(getValidInput( //continue to next line
			"Enter departure time (4-digit military time, e.g. 1300, 1330): ", 
			isValidTime));
			
			// Extract and display the hours and minutes from the entered time
			iHour = iTime / 100;
			iMinute = iTime % 100;
			printf("Time entered: %02d:%02d\n", iHour, iMinute);

			// Call to createFlight function
			pFlight = createFlight(szFlight_Id, szDestinationName, iSeats, iTime);
			
			// Finally, the new flight is registered by calling addFlight function
			addFlight(pDatabase, pFlight);
			printf("Flight added successfully.\n");
			
			// After the information is displayed, the user can go back to the menu
			promptEnterKey();
			break;
			 
/*CASES-TWO-------------------------------------------------------------------*/

		case MENU_ADDPASSENGER:
			/* First, clear the memory allocated for the szBuffer to avoid any 
			garbage data */
			memset(szBuffer, 0, sizeof(szBuffer));
			
			// Checks if flights are registered. If not, display error message
			if (isNoFlightsRegistered(pDatabase)){
				break;
			}
			
			/* Ask the user about flight index (iCount). In this code, I used -1
			is to ensure that the loop validates the user's input at least once .*/
			iFlightIndex = -1;
			while (iFlightIndex < 1 || iFlightIndex > flightList.iCount) {
				iFlightIndex = atoi(getValidInput(
				"Enter flight index: ", //continue to next line
				isValidSeats));
				if (iFlightIndex < 1 || iFlightIndex > flightList.iCount) {
					printf("Invalid flight index. Please enter a valid index.\n");
					}                                                               
			}

			// Call to getFlight function
			pFlight = getFlight(&flightList, iFlightIndex -1);
			if (!pFlight) {
				printf("Invalid flight index.\n");
				promptEnterKey();
				break;
			}
			
			// Ask the user about passenger's last name and validate it
			strncpy(szBuffer, getValidInput(
			"Enter passenger's last name (max 20 letters): ",//continue next line 
			isValidPassengerName), sizeof(szBuffer));
			
			// Ask the user about passenger's age and validate it
			iAge = atoi(getValidInput(
			"Enter passenger's age (18-99): ", //continue to next line
			isValidAge));
			
			// Ask the user about the seat number and validates the input
			while (1) {
				iSeatNumber = atoi(getValidInput("Enter seat number (1-100): ", 
				isValidSeats));
				
				// Check if the seat is already taken by another passenger
				iPassengerIndex = findPassengerIndex(pFlight, iSeatNumber);
				if (iPassengerIndex >= 1) {
				
					// If the seat is take, display an error and ask the user again
					PASSENGER* pPassenger = pFlight->pPassengers;
					while (pPassenger != NULL) {
				   	if (pPassenger->iSeatNumber == iSeatNumber) {
				     		printf("Seat %d is already assigned to passenger %s.\n", 
				     		iSeatNumber, pPassenger->szUserName);
							iSeatNumber = 0;
							promptEnterKey(); // reset if the input is invalid
							break;
						}
						pPassenger = pPassenger->pNext;
					}
					if (iSeatNumber == 0) { // reset if the input is invalid
						continue;
					}
				}
			break; 																					 
		}
		
		// Create a new passenger and add it to the linked list (PASSENGER)
		pNewPassenger = createPassenger(szBuffer, iAge, iSeatNumber);
		addPassenger(pFlight, pNewPassenger);
		
		// Finally, sort the passenger list by seat number order
		sortPassengers(pFlight);
		printf("Passenger added successfully.\n");
		promptEnterKey();
		break;
			
/*CASES-THREE-----------------------------------------------------------------*/
			 
		case MENU_PRINTFLIGHT:
			/* First, clear the memory allocated for the szBuffer to avoid any 
			garbage data */
			memset(szBuffer, 0, sizeof(szBuffer));
			
			printf("\n"); // Simple newline character for formatting
			
			// Checks if flights are registered. If not, display error message
			if (isNoFlightsRegistered(pDatabase)){
				break;
			}
			
			// Initialize the flight index to an invalid value (-1)
			iFlightIndex = -1;
			
			// While loop until a valid flight index is inserted
			while (iFlightIndex < 1 || iFlightIndex > flightList.iCount) {
				printf("Enter flight index (positive integer): ");
				fgets(szBuffer, sizeof(szBuffer), stdin);
				
				// Checks if the input can be converted into an integer
				if (sscanf(szBuffer, "%d", &iFlightIndex) != 1) {
					printf("Invalid input. Please enter a valid index.\n");
					continue;
				} 
				
				// This checks if the inserted index is out of range
				if (iFlightIndex < 1 || iFlightIndex > flightList.iCount) {
					printf("Invalid flight index. Please enter a valid index.\n");
				}
			} 
			
			// If successful, the user is shown what flight index is given
			printf("Retrieving flight %d\n", iFlightIndex);
			
			// printFlightByCriteria uses argument "2" to print by index
			printFlightByCriteria(&flightList, 2, iFlightIndex);
			promptEnterKey();
			break;
			
/*CASES-FOUR------------------------------------------------------------------*/
				 
		case MENU_FINDFLIGHTBYTIME:
			printf("\n");
			// Asks the user what departure time they want to see and validates it
			iTime = atoi(getValidInput( // Continue to the next line
			"Enter departure time (4-digit military time, e.g. 1300, 1330): ", 
			isValidTime));
			
			// printFlightByCriteria "1" is to print by flight time
			printFlightByCriteria(&flightList, 1, iTime);
			promptEnterKey();
			break;
			
/*CASES-FIVE------------------------------------------------------------------*/

		case MENU_DELETEFLIGHT:
			/* First, clear the memory allocated for the szBuffer to avoid any 
			garbage data */
			memset(szBuffer, 0, sizeof(szBuffer));
			printf("\n");
			
			// Checks if flights are registered. If not, display error message
			if (isNoFlightsRegistered(pDatabase)){
				break;
			}
			
			// Initializes the flight index to an invalid value
			iFlightIndex = -1;
			
			// While loop until a valid flight index is inserted
			while (iFlightIndex < 1 || iFlightIndex > flightList.iCount) {
				printf("Enter flight index (positive integer): ");
				fgets(szBuffer, sizeof(szBuffer), stdin);
				
				// Checks if the input can be converted into an integer
				if (sscanf(szBuffer, "%d", &iFlightIndex) != 1) {
					printf("Invalid input. Please enter a valid index.\n");
					continue;
				}
				
				// Checks if the entered index is out of range
				if (iFlightIndex < 1 || iFlightIndex > flightList.iCount) {
					printf("Invalid flight index. Please enter a valid index.\n");
				}
			}
			
    		// Get confirmation from user
			printf("Are you sure you want to delete the flight (y/n)? ");
			iConfirm = getchar();
			if (iConfirm == 'y' || iConfirm == 'Y') {
			
				// Calls the deleteFlight function to delete the flight
				deleteFlight(pDatabase, iFlightIndex - 1);
				printf("Flight deleted successfully.\n");
			} else if (iConfirm == 'n' || iConfirm == 'N') {
				printf("Flight deletion cancelled.\n");
			} else {
				printf("Invalid input. Please enter 'y' or 'n'.\n");
			}
			
			// Clear the input buffer
			while ((c = getchar()) != '\n' && c != EOF) {}
			promptEnterKey();
			break;
		 
/*CASES-SIX-------------------------------------------------------------------*/
			 
		case MENU_DELETEPASSENGER:
			printf("\n");
			// Checks if flights are registered. If not, display error message
			if (isNoFlightsRegistered(pDatabase)){
				break;
			}
			
			// Initializes the flight index to an invalid value
			iFlightIndex = -1;
			
			// Loop until a valid flight index is found
			while (iFlightIndex < 1 || iFlightIndex > flightList.iCount) {
				iFlightIndex = atoi(getValidInput( //Continue to next line
				"Enter flight index (positive integer): ", isValidSeats));
				
				//Checks if the entered index is out of range
				if (iFlightIndex < 1 || iFlightIndex > flightList.iCount) {
					printf("Invalid flight index. Please enter a valid index.\n");
				} else {
					pFlight = getFlight(&flightList, iFlightIndex - 1);
				  	if (!hasPassengers(pFlight)) {
				   	printf("This flight has no current passengers.\n");
				      iFlightIndex = -1;
				      promptEnterKey();
				      break; // exit loop if flight has no passengers
				   } else { // exit loop if flight has passengers
				   	break;
				   }
				}
			}
			
			// Check if the loop exited because the flight has no passengers
			if (iFlightIndex == -1) { 
				break;
			}
			
			// Initializes seat number to invalid value
			iSeatNumber = -1;
			
			// Loop until a valid seat number is found
			while (iSeatNumber < 1 || iSeatNumber > 100 || 
				!findPassengerBySeatNumber(pFlight, iSeatNumber)) {
				iSeatNumber = atoi(getValidInput( // Continue to next line
				"Enter seat number (1-100): ", isValidSeats));
				  if (iSeatNumber < 1 || iSeatNumber > 100 || 
				      !findPassengerBySeatNumber(pFlight, iSeatNumber)) {
				      printf("Invalid seat number. Please enter a number "
				             "between 1 and 100 that exists and is occupied.\n");
				}
			}
			
			// When everyting is successful, deletePassenger function is called
			deletePassenger(pFlight, iSeatNumber);
			printf("Passenger reservation deleted successfully.\n");
			promptEnterKey();
			break;
				 
/*CASES-SEVEN-----------------------------------------------------------------*/

		case MENU_CHANGESEAT:
			printf("\n");
			// Checks if flights are registered. If not, display error message
			if (isNoFlightsRegistered(pDatabase)){
				break;
			}
			
			// Initializes the flight index to an invalid value
			iFlightIndex = -1;
			
			// Loop until a valid flight index is found
			while (1) {
				iFlightIndex = atoi(getValidInput(
				"Enter flight index (positive integer): ", isValidSeats));
				if (iFlightIndex < 1 || iFlightIndex > flightList.iCount) {
					printf("Invalid flight index. Please enter a valid index.\n");
					continue;
				}
				
				// Gets the flight according to the index entered
				pFlight = NULL;
				pFlight = getFlight(&flightList, iFlightIndex - 1);
				if (!pFlight) { //continue to next line
					printf("Invalid flight index.\n");
					continue;
				}
				
				// If the flight has no passengers, display error message
				if (!hasPassengers(pFlight)) {
					printf("This flight has no current passengers.\n");
					continue;
				}
				
				// If valid flight was found, enter to continue
				promptEnterKey();
				break;
			}
			
			/* Ask the user to enter old seat number they want to change and then
			set the oldSeatNumber and newSeatNumber value to invalid number*/
			oldSeatNumber = -1; 
			newSeatNumber = -1;
			while (1) {
				oldSeatNumber = atoi(getValidInput(
				"Enter old seat number (1-100): ", isValidSeats));
				if (oldSeatNumber >= 1 && oldSeatNumber <= 100 && 
				findPassengerBySeatNumber(pFlight, oldSeatNumber)) {
					promptEnterKey();
					break;
				}
				printf("Invalid seat number. Please enter a number between 1 "
				"and 100 that exists and is occupied.\n");
			}
			
			// If old seat number was found, ask the user for the new seat number
			while (1) {
				newSeatNumber = atoi(getValidInput(
				"Enter new seat number (1-100): ", isValidSeats));
				if (newSeatNumber >= 1 && newSeatNumber <= 100 && 
				!findPassengerBySeatNumber(pFlight, newSeatNumber)) {
					promptEnterKey();
					break;
				}
				printf("Invalid seat number. Please enter a number between 1 "
				"and 100 that is not already taken.\n");
			}
			
			// If everyting was successful, changeSeat function is called
			changeSeat(pFlight, oldSeatNumber, newSeatNumber);
			printf("Passenger seat changed successfully.\n");
			promptEnterKey();
			break;

/*CASES-EIGHT-----------------------------------------------------------------*/

		case MENU_SEARCHPASSENGER:
			/* First, clear the memory allocated for the szBuffer to avoid any 
			garbage data */
			memset(szBuffer, 0, sizeof(szBuffer));
			printf("\n");
			
			// Checks if flights are registered. If not, display error message
			if (isNoFlightsRegistered(pDatabase)){
				break;
			}
			
			// Gets user input and copies it to the szBuffer and validates it
			strncpy(szBuffer, getValidInput(
			"Enter passenger name (1-20 characters): ", isValidPassengerName),
			sizeof(szBuffer));
			
			// Convert the input to uppercase
			for (int i = 0; i < strnlen(szBuffer, MAX_BUFFERSZ); i++) {
				szBuffer[i] = toupper(szBuffer[i]);
			}
			
			// If everyting was successful, searchPassenger function is called
			searchPassenger(&flightList, szBuffer);
			promptEnterKey();
			break;
			
/*CASES-NINE------------------------------------------------------------------*/
			 
      case MENU_EXIT: 
         clearScreen();
         printf("\r\n************************************************\r\n");
         printf("\r\n  Exiting... Thanks for using NORFLY app!!!\r\n");
         printf("\r\n************************************************\r\n\r\n");
         break;
 
/*DEFAULT---------------------------------------------------------------------*/

      default:
         printf("Invalid choice. Please try again.\n");
         break;
      }
   } while (eMenu != MENU_EXIT);
   
/*END-OF-SWITCH-CASE----------------------------------------------------------*/
 
	freeFlights(pDatabase);
	memset(pDatabase, 0, sizeof(FLIGHTDATABASE));
	return OK;
}

// enum menus selection inspired from Cashier Register
enum MENUSELECTION ___getch() {
	char szBuffer[10] = {0};
	int iUserChoice = 0;
	fgets(szBuffer, sizeof(szBuffer)-1, stdin); //zero terminate
	iUserChoice = atoi(szBuffer);
	if (iUserChoice == MENU_ADDFLIGHT){
		return MENU_ADDFLIGHT;
	}
	if (iUserChoice == MENU_ADDPASSENGER){
		return MENU_ADDPASSENGER;
	}
	if (iUserChoice == MENU_PRINTFLIGHT){
		return MENU_PRINTFLIGHT;
	}
	if (iUserChoice == MENU_FINDFLIGHTBYTIME){
		return MENU_FINDFLIGHTBYTIME;
	}
	if (iUserChoice == MENU_DELETEFLIGHT){
		return MENU_DELETEFLIGHT;
	}
	if (iUserChoice == MENU_DELETEPASSENGER){
		return MENU_DELETEPASSENGER;
	}
	if (iUserChoice == MENU_CHANGESEAT){
		return MENU_CHANGESEAT;
	}
	if (iUserChoice == MENU_SEARCHPASSENGER){
		return MENU_SEARCHPASSENGER;
	}
	if (iUserChoice == MENU_EXIT){
		return MENU_EXIT;
	}
	return MENU_UNINITIALIZED;
}

/*END-OF-MAIN-FILE------------------------------------------------------------*/
