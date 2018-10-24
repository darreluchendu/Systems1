#ifndef _DATE_H_INCLUDED_
#define _DATE_H_INCLUDED_

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
	char *day=(char*) malloc(sizeof(char));
	char *month=(char*) malloc(sizeof(char));
	char *year=(char*) malloc(sizeof(char));

	Date *date= malloc(sizeof(Date));
	 strncpy(day, datestr, 2);
	 strncpy(month, datestr+2, 2);
	 strncpy(year, datestr+3, 4);

	 date->day = atoi  (day);
	 date->month =atoi (month);
	 date->year =atoi (year);

	 free(day);
	 free(month);
	 free(year);

	if (date){
	 return date;

	}else{
		return NULL;
	}
}
/*
 * date_duplicate creates a duplicate of `d'
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

/*
 * date_compare compares two dates, returning <0, 0, >0 if
 * date1<date2, date1==date2, date1>date2, respectively
 */
int date_compare(Date *date1, Date *date2);

/*
 * date_destroy returns any storage associated with `d' to the system
 */
void date_destroy(Date *d);

#endif /* _DATE_H_INCLUDED_ */
