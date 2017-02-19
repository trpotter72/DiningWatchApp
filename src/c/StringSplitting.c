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
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Start string split");
	char** formattedMenu = malloc(sizeof(char)*1024);
	int i = 0;
	
	for (char *token = strtok_r(a_str, a_delim ,&a_str); token != NULL; token = strtok_r(NULL, a_delim, &a_str)){
		formattedMenu[i] = strdup(token);
		i++;
	}
	return formattedMenu;
}

char* strtok_r(char *s, const char *delim, char **lasts)
 {
         const char *spanp;
         int c, sc;
         char *tok;
 					
         /* s may be NULL */
         /*netsnmp_assert(delim != NULL);*/
         /*netsnmp_assert(lasts != NULL);*/
 
         if (s == NULL && (s = *lasts) == NULL)
                 return (NULL);
 
         /*
          * Skip (span) leading delimiters (s += strspn(s, delim), sort of).
          */
 cont:
         c = *s++;
         for (spanp = delim; (sc = *spanp++) != 0;) {
                 if (c == sc)
                         goto cont;
         }
 					
         if (c == 0) {           /* no non-delimiter characters */
                 *lasts = NULL;
                 return (NULL);
         }
         tok = s - 1;
 
         /*
          * Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
          * Note that delim must have one NUL; we stop if we see that, too.
          */
         for (;;) {
                 c = *s++;
                 spanp = delim;
                 do {
                         if ((sc = *spanp++) == c) {
                                 if (c == 0)
                                         s = NULL;
                                 else
                                         s[-1] = 0;
                                 *lasts = s;
                                 return (tok);
                         }
                 } while (sc != 0);
         }
         /* NOTREACHED */
 }