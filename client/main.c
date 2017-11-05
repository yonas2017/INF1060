#include "client.h"
#include "queue.h"
#include <stdio.h>

int main(int argc, char* argv [])
{
	printf("Client Started\n");

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
//			int* data = dequeue(queue);
//
//			if(data)
//			{
//				printf("queue->m_stack = %d\n", *data); //TODO
//			}
//		}
//
//		queueDestroy(queue);
//	}

	return 0;
}
