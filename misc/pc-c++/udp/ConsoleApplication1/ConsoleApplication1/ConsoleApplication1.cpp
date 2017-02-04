// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

int split (const char *txt, char delim, char ***tokens)
{
    int *tklen, *t, count = 1;
    char **arr, *p = (char *) txt;

    while (*p != '\0') if (*p++ == delim) count += 1;
    t = tklen = (int*)calloc (count, sizeof (int));
    for (p = (char *) txt; *p != '\0'; p++) *p == delim ? *t++ : (*t)++;
    *tokens = arr = (char**)malloc (count * sizeof (char *));
    t = tklen;
    p = *arr++ = (char*)calloc (*(t++) + 1, sizeof (char *));
    while (*txt != '\0')
    {
        if (*txt == delim)
        {
            p = *arr++ = (char*)calloc (*(t++) + 1, sizeof (char *));
            txt++;
        }
        else *p++ = *txt++;
    }
    free (tklen);
    return count;
}

int _tmain(int argc, _TCHAR* argv[])
{
	printf("hello");

	char **tokens;
int count, i;
const char *str = "JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC";

count = split (str, ',', &tokens);
for (i = 0; i < count; i++) printf ("%s\n", tokens[i]);

/* freeing tokens */
for (i = 0; i < count; i++) free (tokens[i]);
free (tokens);

	while(1==1){}
	return 0;
}

