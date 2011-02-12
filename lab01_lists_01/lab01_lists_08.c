/* lab01_lists_08.c
 * Semester 03. Task 01. Variant 08.
 * Working with lists program.
 * Main module.
 * Bob Rutsky 2057/2
 * 19.09.2007
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "list.h"

/* Program constants */
enum
{
  BUF_SIZE              = 1000, /* Input buffer size */
  MAX_FILE_NAME_LEN     = 200,  /* File name maximum length */
  LIST_INPUT_BUF_SIZE   = 1000, /* Reading list from file buffer size */
  MAX_NAME              = 100, /* Maximum employee name length */
  READ_REQUEST_BUF_SIZE = 1000, /* Parsing input string local buffer size */
};

/* Main menu states */
typedef enum
{
  MENU_INCORRECT = 0,
  MENU_EXIT,
  MENU_LOAD_FILE,  
  MENU_SEARCH_EMPLOYEE,  
} MenuState;

/* Retrieving word from stream */
size_t getWord( char const *buf, char *resultWord, size_t resultWordLength )
{
  size_t i = 0;

  for (i = 0; i < resultWordLength - 1 && *buf && !isspace(*buf); ++i, ++buf)
    resultWord[i] = *buf;
  resultWord[i] = 0;

  return i;
}

/* Reading string from file stream function */
char *readString( FILE *fp, char *buf, size_t bufLength )
{
  char *pCharRes;

  pCharRes = fgets(buf, bufLength - 1, fp);

  if (pCharRes != NULL)
  {
    buf[bufLength - 1] = 0;
    if (buf[0] && buf[strlen(buf) - 1] == '\n')
      buf[strlen(buf) - 1] = 0;
  }

  return pCharRes;
}

/* Retrieving data information from string function */
void getDataFromString( char const *str, Data *data )
{
  char readRequestBuf[READ_REQUEST_BUF_SIZE];
  char *readRequest1 = "%d.%d.%d ", readRequest2[READ_REQUEST_BUF_SIZE], *readRequest3 = " %lf";

  sprintf(readRequest2, "%%%ds", (int)MAX_NAME - 1);

  strncpy(readRequestBuf, readRequest1, READ_REQUEST_BUF_SIZE - 1);
  strncat(readRequestBuf, readRequest2, READ_REQUEST_BUF_SIZE - strlen(readRequestBuf) - 1);
  strncat(readRequestBuf, readRequest3, READ_REQUEST_BUF_SIZE - strlen(readRequestBuf) - 1);

  sscanf(str, readRequestBuf, &data->date.day, &data->date.month, &data->date.year,
    data->name, &data->workHours);
}

/* Loading list from file function */
List *loadList( FILE *fp )
{
  static char buf[LIST_INPUT_BUF_SIZE];
  static char name[MAX_NAME];
  static Data data;
  List *list = NULL;

  data.name = name;
  data.date.month = 30;

  while (!feof(fp))
  {
    buf[0] = 0;
    readString(fp, buf, LIST_INPUT_BUF_SIZE);
    if (buf[0])
    {
      getDataFromString(buf, &data);
      list = addElement(list, &data);
    }
  }

  return list;
}

/* Loading list from file function */
List *loadListFromFile( char const *fileName )
{
  FILE *fp;
  List *list;

  if ((fp = fopen(fileName, "rt")) == NULL)
  {
    perror("fopen");
    return NULL;
  }

  list = loadList(fp);

  fclose(fp);

  return list;
}

/* Printing list to stream function */
void printList( FILE *fp, List *list )
{
  if (list == NULL)
    fprintf(fp, "Empty list.\n");
  else
    fprintf(fp, "Date     %-20s Work hours\n", "Name");

  while (list != NULL)
  {
    fprintf(fp, "%02d.%02d.%02d %-20s %g\n", 
      list->data.date.day, list->data.date.month, list->data.date.year,
      list->data.name, list->data.workHours);
    
    list = list->next;
  }
}

/* Printing each employee work time function */
void printEachEmployeeWorkTime( FILE *fp, List *list )
{
  char *lastName = NULL;
  double workHours;

  if (list != NULL)
  {
    lastName = list->data.name;
    workHours = 0;
    fprintf(fp, "%-20s Total work hours\n", "Name");
  }

  while (list != NULL)
  {
    if (!strcmp(lastName, list->data.name))
      workHours += list->data.workHours;
    else
    {
      fprintf(fp, "%-20s %g\n", lastName, workHours);
      lastName = list->data.name;
      workHours = list->data.workHours;
    }

    list = list->next;
  }

  if (lastName != NULL)
    fprintf(fp, "%-20s %g\n", lastName, workHours);
}

/* Printing all employees with provided name function */
void printEmployeesWithName( FILE *fp, List *list, char const *name )
{
  char *lastName = "";
  int isAnyone = 0;

  fprintf(fp, "Searching '%s*' emplyee...\n", name);

  while (list != 0)
  {
    if (strcmp(lastName, list->data.name))
    {
      if (!strncmp(list->data.name, name, strlen(name)))
      {
        fprintf(fp, "%-20s\n", list->data.name);
        isAnyone = 1;
      }
      lastName = list->data.name;
    }

    list = list->next;
  }

  if (!isAnyone)
    fprintf(fp, "There is no employee which name starting with '%s'.\n", name);
}

/* The main program function */
int main( void )
{
  int done = 0;
  static char buf[BUF_SIZE];
  FILE *inFp = stdin, *outFp = stdout;
  List *list = NULL;

  /* Main program cycle */
  while (!done)
  {
    int isError = 0;

    fprintf(outFp, "Semester 03. Task 01. Variant 08.\n");
    printList(outFp, list);
    printEachEmployeeWorkTime(outFp, list);
    fprintf(outFp,
      "\n"
      "0 - Exit.\n"
      "1 - Load list from file.\n"
      "2 - Search employee.\n"
      "Your choice:\n");

    isError |= (readString(inFp, buf, BUF_SIZE) == NULL);
 
    printf("\n");

    if (isError || feof(inFp) || ferror(inFp))
    {
      printf("I/O error! Aborting...\n");
      done = 1;
    }
    else
    {
      MenuState choice;

      /* Parsing choices */
      if (!strcmp(buf, "0"))
        choice = MENU_EXIT;
      else if (!strcmp(buf, "1"))
        choice = MENU_LOAD_FILE;
      else if (!strcmp(buf, "2"))
        choice = MENU_SEARCH_EMPLOYEE;
      else
        choice = MENU_INCORRECT;

      /* Doing selected job */
      if (choice == MENU_EXIT)
      {
        /* Exiting */

        printf("Quiting...\n");
        done = 1;
      }
      else if (choice == MENU_LOAD_FILE)
      {
        /* Loading list from file */

        char *defaultFileName = "input.txt";
        static char fileNameBuf[MAX_FILE_NAME_LEN];
        char *fileName;

        printf("Enter file name: [%s]\n", defaultFileName);
        readString(inFp, fileNameBuf, MAX_FILE_NAME_LEN);

        if (fileNameBuf[0])
          fileName = fileNameBuf;
        else
          fileName = defaultFileName;

        if (list != NULL)
          destroyList(list);

        list = loadListFromFile(fileName);
      }
      else if (choice == MENU_SEARCH_EMPLOYEE)
      {
        /* Searching employee in list be name */

        static char nameBuf[MAX_NAME];

        printf("Enter employee name:\n");
        readString(inFp, nameBuf, MAX_NAME);

        printEmployeesWithName(outFp, list, nameBuf);
      }
      else
      {
        printf("Incorrect choice!\n");
      }
    }

    printf("\n");
  }

  destroyList(list);

  return 0;
}

/* END OF 'lab01_lists_08.c' FILE */
