#ifndef SERVER_H
#define SERVER_H

#include "tcp.h"
#include <messages.h>

struct Server
{
	struct Tcp    m_tcp;
	struct ClientMessage m_clientMessage;
	struct ServerMessage m_serverMessage;
};

struct Job
{
	char JobType;
	unsigned int jobTextLength;
	char JobTekst[4096];
};

/*
 *
 */
uint8_t getJobType(char JobType);

/*
 *
 */
uint8_t computeChecksum(
	unsigned int jobTextLength,
	char* JobTekst);

/*
 *
 */
unsigned char getJobInfo(
	char JobType,
	unsigned int jobTextLength,
	char* JobTekst);

#endif
