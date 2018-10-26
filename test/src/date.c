#include "date.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct date{
	int day;
	int month;
	int year;
};

Date *date_create(char *datestr){
	 char day [3];
	 char month[3];
	 char year[5];


	 Date *date= malloc(sizeof(Date));
	 strncpy(day, datestr, 2);
	 strncpy(month, datestr+3, 2);
	 strncpy(year, datestr+6, 4);

	 date->day = atoi  (day);
	 date->month =atoi (month);
	 date->year =atoi (year);



	if (date){
	 return date;

	}else{
		return NULL;
	}
}

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
int date_compare(Date *date1, Date *date2){
	if(date1->year > date2->year) {
		return 1;
	}else if (date1->year < date2->year) {
		return -1;
	}else {
		if(date1->month > date2->month) {
			return 1;
		}else if (date1->month < date2->month) {
			return -1;
		}else {
			if(date1->day > date2->day) {
				return 1;
			}else if (date1->day < date2->day) {
				return -1;
			}else{
				return 0;
			}
		}
	}
}

/*
 * date_destroy returns any storage associated with `d' to the system
 */
void date_destroy(Date *d){
	d=NULL;
	free(d);
}

