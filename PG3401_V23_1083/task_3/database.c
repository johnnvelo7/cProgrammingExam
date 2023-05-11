/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
--------------------------------------------------------------------------------

Project			:	TASK 3 - Flight Departures (EXAM)
Author			:	Candidate number 1083
Revision			:	5.0
Description		:	Database.c for Flight Departure task

--------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////*/

//INCLUDE HEADER FILE FOR DATABASE.C
#include "database.h"

/* FUNCTION ------------------------------------------------------------------*/

// My version of Print menu screen
void printMenuScreen(){
	printf("---------------------------------------------\n");
	printf("           N O R F L Y    A P P             \n");
	printf("---------------------------------------------\n");
	printf("\r\nWelcome to NORFLY booking system.\r\n\r\n");
   printf("\r1. Add flight\n");
   printf("\r2. Add passenger to a flight\n");
   printf("\r3. Print flight details\n");
   printf("\r4. Find flight by departure time\n");
   printf("\r5. Delete flight\n");
   printf("\r6. Delete passenger from a flight\n");
   printf("\r7. Change passenger's seat on a flight\n");
   printf("\r8. Search for passenger's flights\n");
   printf("\r9. Exit\n");
   printf("\r\n\r\nEnter your choice (1-9): ");
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

/* FUNCTION ------------------------------------------------------------------*/

// This function registers a flight in my FLIGHT struct (double linked list)
FLIGHT *createFlight(char *szFlight_Id, char *szDestinationName, 
int iSeats, int iTime) {

	//First allocate memory of pFlight pointer
	FLIGHT *pFlight = NULL;
   pFlight = malloc(sizeof(FLIGHT));
   
   //Copy the user input (flight id) to flight object + zero termination
   strncpy(pFlight -> szFlight_Id, szFlight_Id, //Continue to next line
   sizeof(pFlight -> szFlight_Id) -1);
   pFlight -> szFlight_Id[sizeof(pFlight -> szFlight_Id) - 1] = '\0';
   
   //Copy user input (destination name) to flight object + zero termination
   strncpy(pFlight -> szDestinationName, szDestinationName, 
   sizeof(pFlight -> szDestinationName)-1);
   
   //Set number of seats and departure time for the flight
   pFlight -> szDestinationName[sizeof(pFlight -> szDestinationName)-1] = '\0';
   pFlight -> iSeats = iSeats;
   pFlight -> iTime = iTime;
   
   //After that the the list set back to NULL
   pFlight -> pPassengers = NULL;
   pFlight -> pPrev = pFlight -> pNext = NULL;
   
   //Return the newly registered flight
   return pFlight;
}

/* FUNCTION ------------------------------------------------------------------*/

/* Prompt enter key function so that the user will see what happened in the app
before the screen will be cleared and show the menu... */
void promptEnterKey() {
    printf("\nPress <Enter key> to continue...");
    while (getchar() != '\n'); // wait for Enter key
}

/* FUNCTION ------------------------------------------------------------------*/

// This function is used to register "flights" to my double linked list (FLIGHT) 
void addFlight(FLIGHTDATABASE *pDatabase, FLIGHT *pNew_flight) {
	//This checkcs if the head is not NULL, then the list is empty
   if (!pDatabase -> pHead) {
      pDatabase -> pHead = pNew_flight;
      pDatabase -> pTail = pNew_flight;
      
   //If the list is not empty, then flight is added at the end as the tail
   } else {
      pDatabase -> pTail -> pNext = pNew_flight;
      pNew_flight -> pPrev = pDatabase -> pTail;
      pDatabase -> pTail = pNew_flight;
   }
   
   //This is used to know how many index currently there is in the list
   pDatabase -> iCount++;
}

/* FUNCTION ------------------------------------------------------------------*/

/* I used this function for both case 3 and 4 to print the flight.
In this function 2 is for case 3 while 1 is for */
void printFlightByCriteria(FLIGHTDATABASE *pDatabase, 
int iCriteriaType, int iValue) {

	//Initializes iFound to 0 so that I can use it later on if match found
   int iFound = 0;
   
   //I made a pointer to the first flight (pHead) in my FLIGHTDATABASE
   FLIGHT *pCurrent = NULL;
   pCurrent = pDatabase -> pHead;
   
   //I set it to 1 to keep track of the index of the current flight (case 3)
   int iIndex = 1;
   
   //Start of my while loop to check each flight in the FLIGHTDATABASE
   while (pCurrent) {
   
   /* If-else statement to determine what type of argument that user wants. If 
   the user want's to print flight details by Index, it will use "2" and "1"
   for finding flight by time. This checks the user input by iValue == iTime, it
   prints the details by time, and if iValue == iIndex, it prints the flight 
   details by index. Finally, if match is found, iMatch sets to 1.*/
      int iMatch = 0;
      if (iCriteriaType == 1 && iValue == pCurrent -> iTime) {
      	iMatch = 1;
      } else if (iCriteriaType == 2 && iValue == iIndex) {
      	iMatch = 1;
      }
      if (iMatch) {
      	iFound = 1;
         printf("\nFlight Details\n");
         printf("Flight ID: \t%s\n", pCurrent -> szFlight_Id);
         printf("Destination: \t%s\n", pCurrent -> szDestinationName);
         printf("Seats: \t\t%d\n", pCurrent -> iSeats);
         printf("Time: \t\t%d\n", pCurrent -> iTime);
			printf("Flight found in index: \t%d\n", iIndex);
         printf("\nPassenger Details\n");
         PASSENGER *pPassenger = pCurrent -> pPassengers;
         if (!pPassenger) {
         	printf("No passengers on this flight.\n");
            } else {
            	while (pPassenger) {
               	printf("Name: \t\t%s\n", pPassenger -> szUserName);
                  printf("Age: \t\t%d\n", pPassenger -> iAge);
                  printf("Seat Number: \t%d\n\n", pPassenger -> iSeatNumber);
                  pPassenger = pPassenger -> pNext;
               }
         }
         if (iCriteriaType == 2) {
				break;
         }
		}
		if (iMatch && iCriteriaType == 2) {
		
      	// Only decrement iValue if I found a matching flight using iIndex
      	iValue--;
      }
      
      /*This sets the pCurrent to the next flight in the list and the iIndex is
      incremented to keep track of the current index in flight lists. This 
      allows the program to keep track of the current flight when searching.*/
      pCurrent = pCurrent -> pNext;
      iIndex++;
	}
	
	//Simple error message if no flight was found.
   if (!iFound) {
		printf("No flight found with the given criteria.\n");
	}
}

/* FUNCTION ------------------------------------------------------------------*/

// Create a new passenger with the given information
PASSENGER *createPassenger(const char *szUserName, //Continue to next line
int iAge, int iSeatNumber) {

	//First I set the pPassenger to NULL, then allocate enough memory (sizeof)
	PASSENGER *pPassenger = NULL;
   pPassenger = malloc(sizeof(PASSENGER));
   
   /*It then copies the passenger name stored in PASSENGER struct to the new
   field of the passenger (szUserName). I also used "strncpy" to prevent buffer
   overflows and -1 to do zero-termination."*/
   strncpy(pPassenger -> szUserName,szUserName, // Continue to next line
   sizeof(pPassenger -> szUserName ) - 1 );
   
	//Now I can set the Age, and Seat number in PASSENGER fields
   pPassenger -> iAge = iAge;
   pPassenger -> iSeatNumber = iSeatNumber;
   
   //This sets pNext to NULL because new passenger is not yet added to the list.
   pPassenger -> pNext = NULL;
   
   //Returning a pointer to the newly created passenger struct
   return pPassenger;
}
   
/* FUNCTION ------------------------------------------------------------------*/

// Add a new passenger to the flight's linked list of passengers
void addPassenger(FLIGHT *pFlight, PASSENGER *pNew_passenger) {

	/*If the PASSENGER linked list is empty, I set the new passenger as the 
	first element in the list. */
   if (!pFlight -> pPassengers) {
      pFlight -> pPassengers = pNew_passenger;
      
  	//Otherwise I find the correct position for the new passenger in the list
   } else {
      PASSENGER *pCurrent = pFlight -> pPassengers, *pPrev = NULL;
      
      //It then traverse the linked list until the correct position is found
      while (pCurrent && pCurrent -> iSeatNumber < // Continue next line
      pNew_passenger -> iSeatNumber) {
         pPrev = pCurrent;
         pCurrent = pCurrent -> pNext;
      }
      
      /*This is to insert the new passenger at the beginning of the list if it
      is the first element in the list.*/
      if (!pPrev) {
         pNew_passenger -> pNext = pFlight -> pPassengers;
         pFlight -> pPassengers = pNew_passenger;
         
      //OTherwise, it inserts the new passenger at the correct position
      } else {
         pNew_passenger -> pNext = pPrev -> pNext;
         pPrev -> pNext = pNew_passenger;
      }
   }
   
   //After the new passenger is added, it sorts it by using seat number function
   sortPassengers(pFlight);
}

/* FUNCTION ------------------------------------------------------------------*/

// Delete the flight in the linked list by the given index
void deleteFlight(FLIGHTDATABASE *pDatabase, int iIndex) {

	//First it sets the pointers to NULL;
   FLIGHT *pFlightToDelete = NULL;
   FLIGHT *pCurrentFlight = pDatabase -> pHead;
   //First it checks if the user input (index) is valid
   if (iIndex < 0 || iIndex >= pDatabase -> iCount) {
      printf("Invalid flight index.\n");
      return;
   }
   
   /*If the index is 0, this functions deletes the head of the list by setting
   pDatabase->pHead to the next element. The head element is then deleted or
   freed using free() function.*/
   if (iIndex == 0) {
   
      // Deleting the head of the linked list
      pFlightToDelete = pDatabase -> pHead;
      pDatabase -> pHead = pDatabase -> pHead -> pNext;

      // Update pTail if the list is now empty
      if (pDatabase -> pHead == NULL) {
      	pDatabase -> pTail = NULL;
      }
      
   /*If the index > 0, the function deletes the element in the middle or the
   end of the linked list. It uses a while loop to traverse the linked list
   until it reaches the element before the element that the user wants to 
   delete. The function then sets the next pointer of the current element to
   point to the element after the element the user wants to delete. 
   It also frees it using free().*/
   } else {
   
   	// Deleting an element or item that is not the head of the linked list
      int i = 0;
      while (i < iIndex - 1) {
      	pCurrentFlight = pCurrentFlight -> pNext;
         i++;
      }
      pFlightToDelete = pCurrentFlight -> pNext;
      pCurrentFlight -> pNext = pFlightToDelete -> pNext;

      // Update pTail if the last node is being deleted
      if (pFlightToDelete == pDatabase -> pTail) {
      	pDatabase -> pTail = pCurrentFlight;
      }
   }
   
   /*Finally, if the element to be deleted is at the end or tail of the
   double linked list, it updates the pDatabase->pTail to point to the new
   tail element or item.*/
   if (pFlightToDelete != NULL) {
   	free(pFlightToDelete); // free only the flight being deleted
      pDatabase -> iCount--; // decrement the count of flights in the database
   }
}

/* FUNCTION ------------------------------------------------------------------*/

// Delete a passenger from the flight's linked list of passengers by seat number
void deletePassenger(FLIGHT *pFlight, int iSeatNumber) {

	/*I first initialize the current and previous passenger pointers to the
	start of the linked list (PASSENGER) */
   PASSENGER *pCurrent = pFlight -> pPassengers, *pPrev = NULL;
   
   /*The function then traverses the linked list until it finds the passenger
   with the specific seat number*/
   while (pCurrent && pCurrent -> iSeatNumber != iSeatNumber) {
		pPrev = pCurrent;
		pCurrent = pCurrent -> pNext;
   }
   
   //Simple error message if the seat number is invalid or not found.
   if (!pCurrent) {
      printf("Invalid seat number. \n");
      return;
   }
   
  	/*If the passenger to dleete is not the first passenger in the linked list,
  	the function sets the previous passenger's next pointer to the passenger
  	after the one to delete. Otherwise, update the start of the linked list to 
  	the passenger after the one to delete.*/
   if (pPrev) {
      pPrev -> pNext = pCurrent -> pNext;
   } else {
      pFlight -> pPassengers = pCurrent -> pNext;
   }
   
   //Using free() to free the allocated memory from the deleted passenger
   free(pCurrent);
   pCurrent = NULL; //Setting it back to null so that I can reuse the function
}

/* FUNCTION ------------------------------------------------------------------*/

// Change the seat number of in the flight's linked list of passengers
void changeSeat(FLIGHT *pFlight, int iOldSeatNumber, int iNewSeatNumber) {

	/*The function first initializes the current and previous passenger pointers
	to the start of the linked list*/
   PASSENGER *pCurrent = pFlight -> pPassengers, *pPrev = NULL;
   
   /*Using while loop to traverse the linked list until the passenger with the 
   specific old seat number is found*/
   while (pCurrent && pCurrent -> iSeatNumber != iOldSeatNumber) {
      pPrev = pCurrent;
      pCurrent = pCurrent -> pNext;
   }
   
   //Simple error message if the old seat number is not found
   if (!pCurrent) {
      printf("Invalid old seat number.\n");
      return;
   }
   
   /*If the passenger to change seat is not the first passenger in the linked
   list, the function then sets the previous passenger's next pointer to the 
   passenger after the one to change seat. Otherwise, the function updates the
   start of the linked list to the passenger after the one to change seat.*/
   if (pPrev) {
      pPrev -> pNext = pCurrent -> pNext;
   } else {
      pFlight -> pPassengers = pCurrent -> pNext;
   }
   
   //Setting the passenger's next pointer to NULL and updating the seat number
   pCurrent -> pNext = NULL;
   pCurrent -> iSeatNumber = iNewSeatNumber;
   
   //Add the passenger back to the linked list in the correct order
   addPassenger(pFlight, pCurrent);
}

/* FUNCTION ------------------------------------------------------------------*/

/* This is a simple function I had to make to double check if the flight has 
passengers or not. It takes a pointer to the FLIGHT and returns an integer
that indecates whether or not the flight has any passengers.*/
int hasPassengers(FLIGHT *flight) {

	//Set the current pointer to the start of the passenger linked list
	PASSENGER *passenger = NULL;
   passenger = flight -> pPassengers;
   
   //Using while loop to traverse the list and check if seat number > 0.
   while (passenger) {
   
   	//If seat number > 0 it will return 1, otherwise move to next passenger
   	if (passenger -> iSeatNumber > 0) {
      	return ERROR;
      }
      passenger = passenger -> pNext;
   }
   
   //If the function reaches the list without finding any passenger, return OK
   return OK;
}

/* FUNCTION ------------------------------------------------------------------*/

// Search for passengers name in all flights' linked list of passengers
void searchPassenger(FLIGHTDATABASE *pDatabase, char *szUserName) {
	//Initializes pointer to the current flight, starting at the head of the list
	FLIGHT *pCurrent = NULL;
  	pCurrent = pDatabase -> pHead;
  	
  	//Initialize an index to keep track of the number of flights searched
   int iIndex = 1;
   printf("Flights for %s: \n", szUserName);
   
   //Using while loop to traverse the list of flights
   while (pCurrent) {
   
   	//Initialize a pointer to the current passenger, starting at the head
   	PASSENGER *pPassenger = NULL;
      pPassenger = pCurrent -> pPassengers;
      
      //Traverse the linked list of passengers
      while (pPassenger) {
      
      	//If the name matches the user input, print the flight ID and index
         if (strncmp(pPassenger -> szUserName, szUserName, 
         sizeof(pPassenger -> szUserName)) == 0) {
            printf("%d: %s\n", iIndex, pCurrent -> szFlight_Id);
         }
         
         //Move to the next passenger in the linked list
         pPassenger = pPassenger -> pNext;
      }
      
      //Move to the next flight in the linked list
      pCurrent = pCurrent -> pNext;
      
      //Increment the flight index to keep track of which flight it is checking
      ++iIndex;
   }
}
   
/* FUNCTION ------------------------------------------------------------------*/

// This function is to retrieve a specific flight from the FLIGHTDATABASE
FLIGHT *getFlight(FLIGHTDATABASE *pDatabase, int iIndex) {

	//Check if the given index is within the range of flights in the database
   if (iIndex < 0 || iIndex >= pDatabase -> iCount) {
      printf("Invalid index.\n");
      return NULL;
   }
   
   //Initialize pointer to NULL first, then to the start of the list
	FLIGHT *pCurrent = NULL;
	pCurrent = pDatabase -> pHead;
	
	//Initialize a counter to keep track of the index while traversing
	int i = 0;
	
	//Using while loop to traverse in the linked list until index is reached
	while (i < iIndex){
		pCurrent = pCurrent -> pNext; //Move to next flight in the list
		i++; //Increment the counter
	}
	
	//Print the flight index and return the current pointer to the flight
	printf("Returning flight: %d\n", iIndex+1); //+1 so index starts at 1
	return pCurrent;
}

/* FUNCTION ------------------------------------------------------------------*/

// This is my version of sort passenger function
void sortPassengers(FLIGHT *pFlight) {

	//First it initializes pointers to current and next passenger in the list 
   if (!pFlight || !pFlight -> pPassengers) {
      return;
   }
   
   //Initialize a pointer to the previous passenger in the linked list
   PASSENGER *pCurrent = pFlight -> pPassengers, *pNext;
   PASSENGER *pPrev = NULL;
   
   //Using nested while loops to traverse linked list and sort the passengers
   while (pCurrent -> pNext) {
      pNext = pCurrent -> pNext;
      while (pNext) {
      
      	//If the current passenger's seat > next one, swap their positions
         if (pCurrent -> iSeatNumber > pNext -> iSeatNumber) {
         
         	/*If the current passenger is the first in the list, set the next
         	passenger as the head*/
            if (!pPrev) {
               pFlight -> pPassengers = pNext;
               
            //Otherwise, set the previous passenger's next pointer to the next
            } else {
               pPrev -> pNext = pNext;
            }
            
            //Swap the positions of the two passengers
            pCurrent -> pNext = pNext -> pNext;
            pNext -> pNext = pCurrent;
            PASSENGER *pTemp = pCurrent;
            pCurrent = pNext;
            pNext = pTemp;
         }
         
         //Move to the next passenger in the linked list and do it again
         pPrev = pNext;
         pNext = pNext -> pNext;
      }
      
      //Reset the previous pointer to NULL and move to the next passenger
      pPrev = NULL;
      pCurrent = pCurrent -> pNext;
   }
}

/* FUNCTION ------------------------------------------------------------------*/

/* Used in case 2. This function takes a pointer to a FLIGHT struct and an
integer iSeatNumber as the input. This is to check for passenger index*/
int findPassengerIndex(FLIGHT *pFlight, int iSeatNumber) {

	//Create a pointer to the first passenger in the flight
	PASSENGER *pPassenger = NULL;
   pPassenger = pFlight -> pPassengers;
   
   //It initializes a counter variable for the passenger index. Starts with 1
   int iIndex = 1;
   
   //Using while loop to trverse in the list until a mathc i found
   while (pPassenger != NULL) {
      if (pPassenger -> iSeatNumber == iSeatNumber) {
      
      	//Return the valid index
      	return iIndex;
      }
      
      //Move to the next passenger in the list
      pPassenger = pPassenger -> pNext;
      
      //Increment the index to keep track of seat number
      iIndex++;
   }
   
   //Return 0 if none found
   return OK;
}
   
/* FUNCTION ------------------------------------------------------------------*/

/* This function takes a pointer to a FLIGHT struct and an integer iSeatNumber
as input. It searches for a passenger in the flight with the matching 
seat number. If a match is found, a pointer to the matching passenger is 
returned, otherwise NULL is returned. */
PASSENGER *findPassengerBySeatNumber(FLIGHT *pFlight, int iSeatNumber) {

	//Set the starting passenger pointer to the head of the list
	PASSENGER *passenger = NULL;
   passenger = pFlight -> pPassengers;
   
   //Using while loop to traverse through the list until match is found
   while (passenger) {
      if (passenger -> iSeatNumber == iSeatNumber) {
      
      	//Return the matched pointer if found
         return passenger;
      }
      
      //Move to the next passenger in the list
      passenger = passenger -> pNext;
   }
   
   //If found nothing, return NULL
   return NULL;
}

/* FUNCTION ------------------------------------------------------------------*/

/* Finally, this is how I free all memory allocated to the FLIGHTDATABASE, 
FLIGHT, and PASSENGER structs. The function takes a pointer to a
FLIGHTDATABASE struct as input, then the function traverses through the 
FLIGHT structs in the FLIGHTDATABASE, and for each FLIGHT, frees all
associated PASSENGER structures. 

After that, it then frees the FLIGHT struct, and repeats this process for all 
FLIGHT structures in the list. Finally, it resets the FLIGHTDATABASE structs 
to its initial state. */
void freeFlights(FLIGHTDATABASE *pDatabase) {

	//Initialize pointers to the first FLIGHT and PASSENGER in the database
   FLIGHT *pCurrent = pDatabase -> pHead, *pTemp;
   
   //Using while loop to traverse the flights and free all passengers
   while (pCurrent) {
   
   	//Save the current pointer to a temporary one
      pTemp = pCurrent;
      
      //Move to the next one
      pCurrent = pCurrent -> pNext;
      
      //Traverse the passengers in the current flight and frees them
      PASSENGER *pPassenger = pTemp -> pPassengers, *p_Temp;
      while (pPassenger) {
      
      	//Save the current passenger to a temp pointer
         p_Temp = pPassenger;
         
         //Move on to next passenger and frees it
         pPassenger = pPassenger -> pNext;
         free(p_Temp);
      }
      
      //frees the current flight
      free(pTemp);
   }
   
   //Reset the database back to its initial state
   pDatabase -> pHead = NULL;
   pDatabase -> pTail = NULL;
   pDatabase -> iCount = 0;
}

/* End of file ---------------------------------------------------------------*/
