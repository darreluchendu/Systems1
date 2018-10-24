#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct date{
	int day;
	int month;
	int year;
};
typedef struct date Date;


/*
 * date_create creates a Date structure from `datestr`
 * `datestr' is expected to be of the form "dd/mm/yyyy"
 * returns pointer to Date structure if successful,
 *         NULL if not (syntax error)
 */
Date *date_create(char *datestr){


	char day [3];
	char month[3];
	char year[5];

	int l, i;
	char S[80];
	S=(char)*datestr;
	l = strlen(S);
	for (i = 0; i < l; ++i)
	printf("A[%d] = %c\n",i,S[i]);
	Date *date= malloc(sizeof(Date));


	memcpy( day, &datestr[0], 2 );
	day[2] = '\0';

	memcpy( month, &datestr[3], 2 );
	month[2] = '\0';

	memcpy( year, &datestr[6], 4 );
	year[4] = '\0';


	 date->day = atoi  (day);
	 date->month =atoi (month);
	 date->year =atoi (year);

	if (date){
	 return date;

	}else{
		return NULL;
	}

}
/*
 * date_duplicate creates a duplicate of
 * returns pointer to new Date structure if successful,
 *         NULL if not (memory allocation failure)
 */
Date *date_duplicate(Date *d){
	Date *date= malloc(sizeof(Date));
	*date = *d;

	if (date){
		 return date;

	}else{
		return NULL;
	}

}
int main(){
	Date *x= date_create("22/04/1998");
	Date *y= malloc(sizeof(Date));
	*y = *x;
	//printf ("%d", x->year);

	return 0;
}
