/* Lab #6
 * Bob Rutsky, 2057/2
 * 12.12.2007
 */

#ifndef STACK_H
#define STACK_H

typedef struct tagStackElem
{
  void *data;
  struct tagStackElem *prev;
} StackElem;

StackElem * allocateStackElem( void *data );

void freeStackElem( StackElem *elem );

int push( StackElem **stack, void *data );

void * pop( StackElem **stack );

#endif // STACK_H
