#include <pebble.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "StringSplitting.h"

char *strdup (const char *s) {
    char *d = malloc (strlen (s) + 1);   // Space for length plus nul
    if (d == NULL) return NULL;          // No memory
    strcpy (d,s);                        // Copy the characters
    return d;                            // Return the new string
}

char** strsplit(char* str, const char* delim){
    char** res = NULL;
    char*  part;
    int i = 0;

    char* aux = strdup(str);

    part = strdup(strtok(aux, delim));

    while(part){
        res = (char**)realloc(res, (i + 1) * sizeof(char*));
        *(res + i) = strdup(part);

        part = strdup(strtok(NULL, delim));
        i++;
    }

    res = (char**)realloc(res, i * sizeof(char*));
    *(res + i) = NULL;

    return res;
}
