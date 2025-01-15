#include "strcmpa.h"

int strcmpa(char *s1, char *s2) {
 while (*s1 && tolower(*s1) == tolower(*s2)){
 	s1++;
 	s2++;
 }
return tolower(*s1) - tolower(*s2);
}

