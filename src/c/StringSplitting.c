#include <pebble.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "StringSplitting.h"
#include <pebble_warn_unsupported_functions.h>
char *strdup (const char *s) {
    char *d = malloc (strlen (s) + 1);   // Space for length plus nul
    if (d == NULL) return NULL;          // No memory
    strcpy (d,s);                        // Copy the characters
    return d;                            // Return the new string
}

/*
char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
	  char delim[2];
   	delim[0] = a_delim;
    
		delim[1] = '0';

    
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

  
    count += last_comma < (a_str + strlen(a_str) - 1);

    
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
      	 size_t idx  = 0;
        char* token = strtok(a_str, delim);
			
        while (token)
        {
           
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        
        *(result + idx) = 0;
    }

    return result;
}
*/
char** str_split(char* a_str,const char* a_delim, int eateries)
	{
	
	char** formattedMenu = malloc(sizeof(char)*1024);
	int i = 0;
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Start string split");
	for (char *token = strtok(a_str, a_delim); token != NULL; token = strtok(NULL, a_delim)){
		formattedMenu[i] = strdup(token);
		i++;
	}
	return formattedMenu;
}