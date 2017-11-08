#ifndef CLIENT_H
#define CLIENT_H

#include "queue.h"
#include "tcp.h"
#include <messages.h>

struct Client
{
	QueuePtr      m_queue[2];
	struct Tcp    m_tcp;
	struct ClientMessage m_clientMessage;
	struct ServerMessage m_serverMessage;
};

typedef struct Client* ClientPtr;

/*
*
*/
int getClientMessage(ClientMessagePtr p_message);

/*
*
*/
char getJobType(char JobType);

/*
*
*/
void releaseResources(ClientPtr p_client);

#endif
