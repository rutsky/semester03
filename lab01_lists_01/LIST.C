/* list.c
 * Semester 03. Task 01. Variant 08.
 * Working with lists program.
 * Basic list functions implementation.
 * Bob Rutsky 2057/2
 * 19.09.2007
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "list.h"

/* Comparing datas fucntion */
int dataCompare( Data *data1, Data *data2 )
{
  return strcmp(data1->name, data2->name);
}

/* Creating list element function */
List *createListElem( Data *data )
{
  List *newElem;

  /* Allocating new element */
  if ((newElem = malloc(sizeof(List))) == NULL)
  {
    perror("malloc");
    return NULL;
  }

  /* Copying data */
  newElem->data.name = (char *)malloc(sizeof(char) * (strlen(data->name) + 1));
  if (newElem->data.name == NULL)
  {
    perror("malloc");
    free(newElem);
    return NULL;
  }
  strcpy(newElem->data.name, data->name);
  newElem->data.date = data->date;
  newElem->data.workHours = data->workHours;
  newElem->next = NULL;

  return newElem;
}

/* Destroying list element function */
void destroyListElem( List *elem )
{
  if (elem != NULL)
  {
    free(elem->data.name);
    free(elem);
  }
}

/* Destroying entire list function */
void destroyList( List *list )
{
  List *next;

  while (list != NULL)
  {
    next = list->next;
    destroyListElem(list);
    list = next;
  }
}

/* Adding new element to list function */
List *addElement( List *list, Data *data )
{
  List *pElem, *pPrevElem, *newElem;

  if ((newElem = createListElem(data)) == NULL)
    return NULL;

  /* Searching place for adding */
  pPrevElem = NULL;
  pElem = list;
  while (pElem != NULL && dataCompare(&pElem->data, &newElem->data) < 0)
  {
    pPrevElem = pElem;
    pElem = pElem->next;
  }

  /* Adding element */
  if (pPrevElem == NULL)
  {
    /* Adding to begin */
    newElem->next = list;

    return newElem;
  }
  else
  {
    /* Adding between elements */
    newElem->next = pPrevElem->next;
    pPrevElem->next = newElem;

    return list;
  }
}

/* END OF 'list.c' FILE */
