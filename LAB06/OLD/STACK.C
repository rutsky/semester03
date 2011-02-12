/* Lab #6
 * Bob Rutsky, 2057/2
 * 12.12.2007
 */

#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

StackElem * allocateStackElem( void *data )
{
  StackElem *elem = NULL;

  if ((elem = malloc(sizeof(StackElem))) == NULL)
  {
    perror("malloc");
    return NULL;
  }

  elem->prev = NULL;
  elem->data = data;

  return elem;
}

void freeStackElem( StackElem *elem )
{
  if (elem != NULL)
    free(elem);
}

int push( StackElem **stack, void *data )
{
  StackElem *elem;

  if ((elem = allocateStackElem(data)) == NULL)
    return 1;

  elem->prev = *stack;
  *stack = elem;

  return 0;
}

void * pop( StackElem **stack )
{
  if (*stack == NULL)
    return NULL;
  else
  {
    void *data = (*stack)->data;
    StackElem *oldStack = *stack;
    *stack = (*stack)->prev;
    freeStackElem(oldStack);

    return data;
  }
}
