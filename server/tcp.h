#ifndef TCP_H
#define TCP_H

#include <messages.h>
#include <string.h>
#include <stdint.h>

struct Tcp
{
	char* m_ip;
	uint16_t m_port;
	int m_sockDesc; // Internal Socket descriptor
};

typedef struct Tcp* TcpPtr;

/*
 *
 */
void tcpopen(TcpPtr p_tcp);

/*
 * Send UDP message
 */
int tcpSend(TcpPtr p_tcp, const ServerMessagePtr p_message);

/*
 * Receive UDP message
 */
int tcpReceive(TcpPtr p_tcp, ClientMessagePtr p_message/*, MessageType messageType*/);

/*
 *
 */
void tcpClose(TcpPtr p_tcp);

#endif
