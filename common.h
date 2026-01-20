#ifndef Common_h
#define Common_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBER_PATIENTS 4
#define NONE          0x00  // 0000 0000
#define PENICILLIN    0x01  // 0000 0001
#define SULFA         0x02  // 0000 0010
#define OPIOIDS       0x04  // 0000 0100
#define ANESTHETICS   0x08  // 0000 1000
#define EGGS          0x10  // 0001 0000
#define LATEX         0x20  // 0010 0000
#define PRESERVATIVES 0x40  // 0100 0000

/*
Year - positive number (1900 - present)
Month - positive number (1 - 12)
Day - positive number
Hour - 24 hour format (0 - 23)
Min - (0 - 59)
*/
typedef struct Date {
	int Year;
	int Month;
	int Day;
	int Hour;
	int Min;
}Date;

/*
name - pointer to dynamic string (letters and spaces only)
nLicense - 7 number string including \0 (numbers only, one-to-one fucntion)
nPatients - number of patients for a specific doctor (4 patients max)
*/
typedef struct Doc {
	char* name;
	int nLicense[8];
	int nPatients[MAX_NUMBER_PATIENTS];
}Doc;

/*
tArrival - Date and time of arrival (struct date, use time.h for real time)
tDissmised - Date and time of dissmisal (struct date, if patient is still in then all fields initialize to -1)
Duration - time stayed in hospital in hours and minutes 
Doctor - pointer to struct Doc
vSummary - Conclusion of stay, pointer to dynamic string (if there is no summary, pointer + NULL)
*/
typedef struct Visit {
	struct Date tArrival;
	struct Date tDismissed;
	float fDuration;
	struct Doc* Doctor;
	char* vSummary;
}Visit;

typedef struct VisitList {//Rotem: adding list of visits for every patient 
	Visit* visit;
	struct VisitList* next;
} VisitList;

/*
name - pointer to dynamic string (letters and spaces only)
ID - 10 number string including \0
Allergies - bitwise 7 option + None (one person can have more than one option)
Visits - to save information about specific visit, pointer to dynamic stack
nVisits - number of visits for specific patient
*/
typedef struct Patient {
	char* name;
	char ID[11];//Rotem change to char (based on instructions)
	unsigned char Allergies;
	struct VisitList* Visits;
	int nVisits;
}Patient ;

#endif //Common_h