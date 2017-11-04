#ifndef STACK_H
#define STACK_H

struct Stack
{
	int* m_stack;  // Pointer to the stack
	int m_curSize; // Current stack size
};

/*
 *
 */
void stackPush(struct Stack* stack, int val);

/*
 *
 */
int stackPop(struct Stack* stack);

/*
 *
 */
bool stackIsEmpty(const struct Stack* stack);

#endif
