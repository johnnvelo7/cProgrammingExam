/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
--------------------------------------------------------------------------------

Project			:	TASK 5 - Server (EXAM)
Author			:	Candidate number 1083
Revision			:	4.0
Description		:	Main Function for Server task

--------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////*/

// STANDARD C LIBS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

// INCLUDE HEADER FILE FOR THREADS.C
#include "serverclient.h"

/*MAIN-FUNCTION --------------------------------------------------------------*/

int main (int iArgC, char *apszArgV[]) {
	// Welcome Screen
	clearScreen();
	printf("---------------------------------------------\n");
	printf("         R E V E R S E    S H E L L          \n");
	printf("---------------------------------------------\n");
	
	// If usage is wrong, show the user how to use the app/program
	if (iArgC < 3) {
		printf("Run these commands on two different terminals:\n\n\n");
		printf("Server Usage: %s -listen -port <PORT>\n", apszArgV[0]);
		printf("Client Usage: %s -server <SERVERIP> -port <PORT>\n", apszArgV[0]);
		printf("\n");
      return ERROR;
   }
   
   // Initialize server and client sockets to -1 by accessing pSockets pointer
	SOCKETS pSockets = {.iServerSocket = -1, .iClientSocket = -1};
	
	// Initialize local variables to 0 and NULL
	int iPort = -1;
   const char* pszServerIP = NULL;
	
	/* Here i used sigaction to handle the signal by the client and the server.
	If either the client or the server presses CTRL+C, the program will terminate
	both from the server, and the client application. */
   struct sigaction SA; // named signation struct as SA to make it shorter
   SA.sa_handler = HandleSignal;
   SA.sa_flags = SA_RESTART;
   
   // Sigemptyset initializes the signal mask to an empty set
   if (sigemptyset(&SA.sa_mask) == -1) {
   	perror("Error initializing signal mask");
		return ERROR;
   }
   
   // sigaction sets up the signal handler for "SIGINT"
   if (sigaction(SIGINT, &SA, NULL) == -1) {
   	perror("Error setting up signal handler");
      return ERROR;
   }
   
	// Iterate through the args using a for loop and check if the args are valid
	for (int i = 1; i < iArgC; i++) {
		if (strncmp(apszArgV[i], "-port", 5) == 0 && i + 1 < iArgC) {
			iPort = atoi(apszArgV[++i]);
		} else if (strncmp(apszArgV[i], "-server", 7) == 0 && i + 1 < iArgC) {
			pszServerIP = apszArgV[++i];
		}
	}
	
   // If invalid port, display simple error message
   if (iPort == -1) {
   	fprintf(stderr, "Error: Port not specified\n");
		return ERROR;
   }
   
   // If the argument is for pszServerIP, run client function
   if (pszServerIP) {
   	ClientFunction(pszServerIP, iPort, &pSockets);
   	
  	// Else, run server function
   } else {
   	ServerFunction(iPort, &pSockets);
   }
   return OK;
}
/* End of file ---------------------------------------------------------------*/
