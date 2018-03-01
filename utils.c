#include "types.h"
#include "linked_list.h"
#include "utils.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

const char base32[32] = {'!', '@', '#', '$', '%', '^', '&', '*', '<', '>', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v'};

/* TO DO: API, add line, file */
void printError(line_t *line, char *f, ...)
{
  va_list arg; /* This var will store the extra arguments */
  char format[MAX_ERROR_LENGTH];

  sprintf(format, "ERROR: %s:%d: %s\n", line->fileName, line->lineNumber, f);
  line->error = true; /* Set line error to true */

  va_start(arg, f); /* Init the args' pointer */
  vfprintf(stderr, format, arg); /* Format error and print to stderr using vfprintf */
  va_end(arg); /* Release the pointer */
}

void updateDataSymbolsWithOffset(int offset)
{
  symbol_node_t *ptr = symbolHead;

  /* While the item exists, the list didn't end */
  while (ptr)
  {
    if (ptr->data.type == data || ptr->data.type == strct || ptr->data.type == string) /* If the item is data(numbers, struct or string) */
      ptr->data.pointer += offset; /* Add the offset to the item' pointer */

    ptr = ptr->next; /* Point ptr to the next item in the list */
  }
}


symbol_t *checkIfSymbolExists(symbol_t symbol)
{
  symbol_node_t *ptr = symbolHead;

  /* While the item exists, the list didn't end */
  while (ptr)
  {
    if (strcmp(ptr->data.name, symbol.name) == 0) /* If the item's symbol is equal to the new one return true */
      return &ptr->data;

    ptr = ptr->next; /* Point ptr to the next item in the list */
  }

  return NULL;
}

bool isblank(char ch)
{
  return ch == ' ' || ch == '\t' ? true : false;
}

char *convertToBase32(unsigned int value)
{
  char *result;
  int i;

  /* Try allocate memory for convertion result */
  if ((result = (char *)malloc(3 * sizeof(char))) == NULL)
  {
    fprintf(stderr, "Error allocating memory for base 32 result!\n"); /* Print error */
    exit(0);
  }

  /* At start set !! as the result */
  result[0] = '!';
  result[1] = '!';
  result[2] = 0;

  for (i = 1; i >= 0 && value; i--) /* Going through the result str */
  {
    result[i] = base32[value % 32]; /* Setting first char */
    value /= 32; /* Dividing in 32 to get the second char */
  }

  return result;
}
