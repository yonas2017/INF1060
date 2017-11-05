#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

StackPtr stackCreate(int size)
{
	StackPtr stack;

	/*
	 * Allocate the stack data structure on the Heap
	 */
	stack = (StackPtr) malloc(sizeof(struct Stack));

	/*
	 * Allocate the stack data memory on the Heap
	 */
	if(stack)
	{
		stack->m_stack = (int*) calloc(size, sizeof(int));
		stack->m_top = -1;
		stack->m_size = size;

		printf("Stack Created Successfully.\n");
	}

	return stack;
}

void stackPush(StackPtr stack, int data)
{
	if(!stackIsFull(stack))
	{
		stack->m_top++;
		stack->m_stack[stack->m_top] = data;
	}
	else
	{
		printf("Could not insert data, Stack is full.\n");
	}
}

int stackIsFull(const StackPtr stack)
{
   return (stack->m_top == stack->m_size) ? 1 : 0;
}

int* stackPop(StackPtr stack)
{
	int* data = NULL;
	if(!stackIsEmpty(stack))
	{
		data = &stack->m_stack[stack->m_top];
		stack->m_top--;
	}
	else
	{
		printf("Could not retrieve data, Stack is empty.\n");
	}

	return data;
}

int stackIsEmpty(const StackPtr stack)
{
	return (stack->m_top) == -1 ? 1 : 0;
}

void stackDestroy(StackPtr stack)
{
	/*
	 * Free the stack data memory first
	 */
	free(stack->m_stack);

	/*
	 * Free the stack data structure at last
	 */
	free(stack);

	printf("Stack Destroyed.\n");
}
