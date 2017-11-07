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

#endif
