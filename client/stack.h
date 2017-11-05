#ifndef STACK_H
#define STACK_H

/*
 * Stack data structure
 */
struct Stack
{
	int* m_storage; // Stack storage
	int  m_top;     // Stack position
	int  m_size;    // Stack size
};

typedef struct Stack* StackPtr;

/*
 *
 */
StackPtr stackCreate(int size);

/*
 *
 */
void stackPush(StackPtr p_stack, int data);

/*
 *
 */
int stackIsFull(const StackPtr p_stack);

/*
 *
 */
int* stackPop(StackPtr p_stack);

/*
 *
 */
int stackIsEmpty(const StackPtr p_stack);

/*
 *
 */
void stackDestroy(StackPtr p_stack);

#endif
