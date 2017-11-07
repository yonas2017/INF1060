#include "client.h"
#include "queue.h"
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
	/*
	 * Check arguments used. has to have 2 args
	 */
	if(argc < 3)
	{
		help();
		return -1;
	}

	printf("Client Started\n");

	/*
	 * Create Queue
	 */
	int queueSize = 16;
	struct Client client;
	client.m_queue[0] = queueCreate(queueSize);
	client.m_queue[1] = queueCreate(queueSize);

	/*
	 * Initialize TCP
	 */
	client.m_tcp.m_ip = argv[1];
	client.m_tcp.m_port = atoi(argv[2]);

	/*
	 * Get input from User
	 */
	 char option, numJobs;
   printf("1 - Get one Job from server.\n");
   printf("2 - Get X number of jobs from the server\n");
   printf("3 - Get all jobs from the server\n");
   printf("4 - Quit Program\n\n");

   scanf("%c", &option);

   switch(option)
	 {
		 case'1':
		 	printf("Getting one job from the server has been selected.\n");
      break;
     case'2':
			 printf("Enter number of jobs to get from the server:\n");
			 scanf("%c", &numJobs);
       printf("Getting %c job from the server has been selected.\n", numJobs);
       break;
     case'3':
			 printf("Getting all jobs from the server has been selected.\n");
       break;
     case'4':
       printf("Quiting program.\n");
       break;
 		 default:
			 printf("Invald choice  %c\n", option);
			 return -1;
		 }

//	/*
//	 * FIFO queue
//	 */
//	int size = 10;
//	QueuePtr queue = queueCreate(size);
//	if(queue)
//	{
//		enqueue(queue, 10);
//		enqueue(queue, 3);
//		printf("queue->m_size = %d\n", queue->m_stack1->m_size);
//		while(!queueIsEmpty(queue))
//		{
//			ServerMessagePtr data = dequeue(queue);
//
//			if(ServerMessagePtr)
//			{
//				printf("queue->m_stack = %s\n", ServerMessagePtr->JobInfo); //TODO
//        printf("queue->jobTextLength = %s\n", ServerMessagePtr->jobTextLength);
//			}
//		}
//
//		queueDestroy(queue);
//	}

	queueDestroy(client.m_queue[0]);
	queueDestroy(client.m_queue[1]);

	return 0;
}
