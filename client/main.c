#include "client.h"
#include "queue.h"
#include "tcp.h"

#include <messages.h>
#include <stdio.h>
#include <stdlib.h>

static void help()
{
	printf("./client <ip> <port>\n");
	printf("	<ip>   : ip to use\n");
	printf("	<port> : port to use\n");
}

int main(int argc, char* argv [])
{
	printf("Client Started\n");

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
	struct Client client;

	/*
	 * Open TCP Socket
	 */
	client.m_tcp.m_ip = argv[1];
	sscanf(argv[2], "%d", &client.m_tcp.m_port);

	// if(tcpOpen(&client.m_tcp) != 0) //TODO
	// {
	// 	return -1;
	// }

	/*
	 * Create Two Queues for the childs
	 */
	int queueSize = 16;
	client.m_queue[0] = queueCreate(queueSize);
	client.m_queue[1] = queueCreate(queueSize);

	/*
	 * Get Client Message
	 */
	if(getClientMessage(&client.m_clientMessage) != 0)
	{
		releaseResources(&client);
		return -1;
	}

	/*
	* Send client messsage to server
	*/
	tcpSend(&client.m_tcp, &client.m_clientMessage);

	/*
	* Receive server message
	*/
	while(tcpReceive(&client.m_tcp, &client.m_serverMessage))
	{
		/*
		* Get Job Type
		*/
		char jobType = getJobType(client.m_serverMessage.JobInfo);
		printf("jobType: %c\n", jobType);
		printf("%s\n", client.m_serverMessage.JobTekst);

		switch(jobType)
		{
			case 'O':
			  /*
			   * Enqueue message for child 1
			   */
				enqueue(client.m_queue[0], &client.m_serverMessage);
				break;
			case 'E':
			  /*
			   * Enqueue message for child 2
			   */
				enqueue(client.m_queue[1], &client.m_serverMessage);
				break;
			case 'Q':
			 /*
			  * Enqueue message for both childs
			  */
				enqueue(client.m_queue[0], &client.m_serverMessage);
				enqueue(client.m_queue[1], &client.m_serverMessage);
				break;
			default:
				printf("Wrong Job Type: %c\n", jobType);
				releaseResources(&client);
				return -1;
		}
	}

	/*
	* Release resources
	*/
	releaseResources(&client);

	return 0;
}
