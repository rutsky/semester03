/* list.c
 * Semester 03. Task 01. Variant 08.
 * Working with lists program.
 * Basic list functions declaration.
 * Bob Rutsky 2057/2
 * 19.09.2007
 */

#ifndef _LIST_H_
#define _LIST_H_

/* Date structure */
typedef struct
{
  int year, month, day;
} Date;

/* List node data */
typedef struct
{
  char   *name;     /* Employee name */
  Date   date;      /* Day */
  double workHours; /* Work hours */
} Data;

/* Main list structure */
typedef struct tagList
{
  Data data;

  struct tagList *next;
} List;

/* Destroying entire list function */
void destroyList( List *list );

/* Adding new element to list function */
List *addElement( List *list, Data *data );

#endif /* _LIST_H_ */

/* END OF 'list.h' FILE */
