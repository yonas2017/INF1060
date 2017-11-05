#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

QueuePtr queueCreate(int size)
{
	QueuePtr p_queue;

	/*
	 * Allocate the queue data structure on the Heap
	 */
	p_queue = (QueuePtr) malloc(sizeof(struct Queue));

	/*
	 * Allocate the stack storage memory on the Heap
	 */
	if(p_queue)
	{
		p_queue->m_stack1 = stackCreate(size);
		p_queue->m_stack2 = stackCreate(size);

		printf("Queue Created Successfully.\n");
	}

	return p_queue;
}

void enqueue(QueuePtr p_queue, int data)
{
	if(!p_queue)
	{
		return;
	}

	stackPush(p_queue->m_stack1, data);
}

int queueIsFull(const QueuePtr p_queue)
{
	if(!p_queue)
	{
		return 0;
	}
	else
	{
		return stackIsFull(p_queue->m_stack1);
	}
}

int* dequeue(QueuePtr p_queue)
{
	int* data = NULL;

	if(!p_queue)
	{
		return NULL;
	}

	while(!stackIsEmpty(p_queue->m_stack1))
	{
		stackPush(p_queue->m_stack2, *stackPop(p_queue->m_stack1));
	}

	//pop the data
	data = stackPop(p_queue->m_stack2);

	while(!stackIsEmpty(p_queue->m_stack2))
	{
		stackPush(p_queue->m_stack1, *stackPop(p_queue->m_stack2));
	}

	return data;
}

int queueIsEmpty(const QueuePtr p_queue)
{
	if(!p_queue)
	{
		return 0;
	}
	else
	{
		return stackIsEmpty(p_queue->m_stack1);
	}
}

void queueDestroy(QueuePtr p_queue)
{
	if(p_queue)
	{
		/*
		 * Free stack1
		 */
		if(p_queue->m_stack1)
		{
			stackDestroy(p_queue->m_stack1);
		}

		/*
		 * Free stack2
		 */
		if(p_queue->m_stack2)
		{
			stackDestroy(p_queue->m_stack2);
		}

		/*
		 * Free the queue data structure finally
		 */
		free(p_queue);

		printf("Queue Destroyed.\n");
	}
}
