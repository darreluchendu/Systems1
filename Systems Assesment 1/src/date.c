//Name: Bulienna Uchendu
//GUID: 2236676u
//Title: SP Excercise 1
//This is my own work as defined in the Academic Ethics agreement
//gg

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
	int day;
	int month;
    int year;

	Date *date= malloc(sizeof(Date));

	if (strlen(datestr)!=10){
		return NULL;
	}
	if (datestr[2]!='/'){
		return NULL;
	}
	if (datestr[5]!='/'){
		return NULL;
	}


	int x= sscanf(datestr, "%u/%u/%u", &day,&month,&year);
	if (x!=3){
		return NULL;
	}

	if (day>31 || day<1){
		return NULL;
	}

	if (month>12 || month <1){
		return NULL;
	}

	if (year<1){
		return NULL;
	}
	date->day = day;
	date->month =month;
	date->year =year;



	if (date){
	 return date;

	}else{
		return NULL;
	}
}


Date *date_duplicate(Date *d){
	Date *date= malloc(sizeof(Date));
	date = d;

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
	if(date1->year >= date2->year) {
		return 1;
	}else if (date1->year <= date2->year) {
		return -1;
	}else {
		if(date1->month >= date2->month) {
			return 1;
		}else if (date1->month <= date2->month) {
			return -1;
		}else {
			if(date1->day >= date2->day) {
				return 1;
			}else if (date1->day <= date2->day) {
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
