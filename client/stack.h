#ifndef STACK_H
#define STACK_H

struct Stack
{
	int* m_stack; // Pointer to the stack
	int  m_top;   // stack position
	int  m_size;  // Stack size
};

typedef struct Stack* StackPtr;

/*
 *
 */
StackPtr stackCreate(int size);

/*
 *
 */
void stackPush(StackPtr stack, int data);

/*
 *
 */
int stackIsFull(const StackPtr stack);

/*
 *
 */
int* stackPop(StackPtr stack);

/*
 *
 */
int stackIsEmpty(const StackPtr stack);

/*
 *
 */
void stackDestroy(StackPtr stack);

#endif
