/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
--------------------------------------------------------------------------------

Project			:	TASK 5 - Server (EXAM)
Author			:	Candidate number 1083
Revision			:	4.0
Description		:	Header file for serverclient.c

--------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////*/

#ifndef __TASK5_SERVER_H__
#define __TASK5_SERVER_H__

// DEFINE
#define MAX_BUFFER_SIZE 1024
#define OK 					0
#define ERROR				1

// STANDARD C LIBS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h> // find out what this is for
#include <arpa/inet.h>
#include <signal.h> // signal functions
#include <stdbool.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>

/* STRUCTS--------------------------------------------------------------------*/

typedef struct _SOCKETS {
	int iServerSocket;
	int iClientSocket;
} SOCKETS;

/* PROTOTYPES-----------------------------------------------------------------*/

void ServerFunction(int iPort, SOCKETS *pSockets);
void ClientFunction(const char *pszServerIP, int iPort, SOCKETS *pSockets);
char *ExecuteCommand(const char *pcszCommand);
void HandleSignal(int iSignal);
void clearScreen();

#endif // __TASK5_SERVER_H__
/* End of file ---------------------------------------------------------------*/
