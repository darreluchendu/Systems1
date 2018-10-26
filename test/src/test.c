
#include "date.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){




	//printf ("%d", date_compare(x,y));


	char *b= "rEd";
	//for ( ; *b; ++b) *b = tolower(*b);
	for(int i = 0; b[i]; i++){
	  b[i] = tolower(b[i]);
	}

	printf("%s", b);
	return 0;
}
