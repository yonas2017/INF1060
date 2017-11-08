#ifndef TCP_H
#define TCP_H

#include <messages.h>
#include <string.h>
#include <stdint.h>

struct Tcp
{
	char* m_fileName; // Filename holding one or more jobs used to send to the client
	uint16_t m_port;  // Server listening Port
	int m_listenSock; // TCP socket
	int m_newSock ;   // New socket to transmit data per connection
};

typedef struct Tcp* TcpPtr;

/*
 *
 */
int tcpOpen(TcpPtr p_tcp);

/*
 * Send UDP message
 */
int tcpSend(TcpPtr p_tcp, const ServerMessagePtr p_message);

/*
 * Receive UDP message
 */
int tcpReceive(TcpPtr p_tcp, ClientMessagePtr p_message);

/*
 *
 */
void tcpClose(TcpPtr p_tcp);

#endif
