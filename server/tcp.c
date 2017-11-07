#include "tcp.h"

#include <sys/types.h>  // For data types
#include <arpa/inet.h>  // For inet_addr()
#include <sys/socket.h> // For socket(), connect(), send(), and recv()
#include <netinet/in.h> // For sockaddr_in
#include <unistd.h>     // For close()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tcpopen(TcpPtr p_tcp)
{
	// open a stream socket
	if((p_tcp->m_sockDesc = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket() failed\n");
		return;
	}

	struct sockaddr_in server_address;
	memset((char *)&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(p_tcp->m_port);
	server_address.sin_addr.s_addr = inet_addr(p_tcp->m_ip);

	// bind it to listen to the incoming connections on the created server address
	if(bind(p_tcp->m_sockDesc, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
	{
		printf("bind() failed\n");
		close(p_tcp->m_sockDesc);
		p_tcp->m_sockDesc = -1;
		return;
	}
}

int tcpSend(TcpPtr p_tcp, const ServerMessagePtr p_message)
{

}

int tcpReceive(TcpPtr p_tcp, ClientMessagePtr p_message/*, MessageType messageType*/)
{

}

void tcpClose(TcpPtr p_tcp)
{
	// close the socket
	close(p_tcp->m_sockDesc);
}
