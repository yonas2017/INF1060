#include "server.h"
#include "tcp.h"

#include <messages.h>
#include <stdio.h>

static void help()
{
	printf("./server <fileName> <port>\n");
	printf("	<fileName> : Job file to read from and send to cleant.\n");
	printf("	<port>     : Server Listening Port.\n");
}

int main(int argc, char* argv [])
{
	printf("Server Started\n");

	/*
	 * Check number of arguments passed by user.
	 */
	if(argc < 3)
	{
		help();
		return -1;
	}

	/*
	* Create the client object
	*/
	struct Server server;

	/*
	 * Open TCP Socket
	 */
	server.m_tcp.m_fileName = argv[1];
	sscanf(argv[2], "%d", &server.m_tcp.m_port);

	if(tcpOpen(&server.m_tcp) != 0)
	{
		return -1;
	}

	/*
	* Receive client message
	*/
	while(tcpReceive(&server.m_tcp, &server.m_clientMessage))
	{
		printf("received msg_type: '%s'\n",
					ClientMessageType_str((enum ClientMessageType) server.m_clientMessage.msg_type));

		/*
		* Send jobText to client
		*/
		tcpSend(&server.m_tcp, &server.m_serverMessage);
	}

	return 0;
}
