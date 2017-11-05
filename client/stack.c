#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

StackPtr stackCreate(int size)
{
	StackPtr p_stack;

	/*
	 * Allocate the stack data structure on the Heap
	 */
	p_stack = (StackPtr) malloc(sizeof(struct Stack));

	/*
	 * Allocate the stack storage memory on the Heap
	 */
	if(p_stack)
	{
		p_stack->m_storage = (int*) calloc(size, sizeof(int));
		p_stack->m_top     = -1;
		p_stack->m_size    = size;

		printf("Stack Created Successfully.\n");
	}

	return p_stack;
}

void stackPush(StackPtr p_stack, int data)
{
	if(!(p_stack && p_stack->m_storage))
	{
		return;
	}

	if(!stackIsFull(p_stack))
	{
		p_stack->m_storage[++p_stack->m_top] = data;
	}
	else
	{
		printf("Could not insert data, Stack is full.\n");
	}
}

int stackIsFull(const StackPtr p_stack)
{
	if(!p_stack)
	{
		return 0;
	}
	else
	{
		return (p_stack->m_top >= p_stack->m_size) ? 1 : 0;
	}
}

int* stackPop(StackPtr p_stack)
{
	int* data = NULL;

	if(!(p_stack && p_stack->m_storage))
	{
		return NULL;
	}

	if(!stackIsEmpty(p_stack))
	{
		data = &p_stack->m_storage[p_stack->m_top--];
	}
	else
	{
		printf("Could not retrieve data, Stack is empty.\n");
	}

	return data;
}

int stackIsEmpty(const StackPtr p_stack)
{
	if(!p_stack)
	{
		return 0;
	}
	else
	{
		return (p_stack->m_top) < 0 ? 1 : 0;
	}
}

void stackDestroy(StackPtr p_stack)
{
	if(p_stack)
	{
		/*
		 * Free the stack storage memory first
		 */
		if(p_stack->m_storage)
		{
			free(p_stack->m_storage);
		}

		/*
		 * Free the stack data structure finally
		 */
		free(p_stack);

		printf("Stack Destroyed.\n");
	}
}
