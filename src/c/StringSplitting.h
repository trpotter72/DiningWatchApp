#ifndef STRINGSPLITTING_H
#define STRINGSPLITTING_H

char *strdup (const char *s);
char ** str_split(char* a_str, const char* a_delim, int eateries); 
char * strtok_r(char *s, const char *delim, char **lasts);
#endif