#ifndef QUEUE_H
#define QUEUE_H

#include "stack.h"
#include <messages.h>

/*
 * Queue data structure
 * http://www.studytonight.com/data-structures/queue-using-stack
 */
struct Queue
{
	StackPtr m_stack1; // Stack one
	StackPtr m_stack2; // Stack two
};

typedef struct Queue* QueuePtr;

/*
 *
 */
QueuePtr queueCreate(int size);

/*
 *
 */
void enqueue(QueuePtr p_queue, ServerMessagePtr message );

/*
 *
 */
int queueIsFull(const QueuePtr p_queue);

/*
 *
 */
ServerMessagePtr dequeue(QueuePtr p_queue);

/*
 *
 */
int queueIsEmpty(const QueuePtr p_queue);

/*
 *
 */
void queueDestroy(QueuePtr p_queue);

#endif
