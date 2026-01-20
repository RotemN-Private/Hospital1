#define _CRT_SECURE_NO_WARNINGS
#define _POSIX_C_SOURCE 200809L
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pTree.h"


#define NONE 0x00
#define PENICILLIN 0x01
#define SULFA 0x02
#define OPIOIDS 0x04
#define ANESTHETICS 0x08
#define EGGS 0x10
#define LATEX 0x20
#define PRESERVATIVES 0x40

void loadPatients(pTree* FullpTree);
//void insertPatient(pTree* tree, Patient* patient); //Rotem (remove) - moved to pTree.c
//void insertPatientNode(plnTree** node, Patient* patient); // Rotem (remove) - moved to pTree.c
Patient* createPatient(char* name, char* ID, char* allergies);
unsigned char parseAllergies(const char* allergiesStr);
Doc* createDoc(char* name, char* nLicense);
Visit* createVisit(char* arrival, char* dismissed, char* duration, Doc* doctor, char* summary);
//Date parseDate(char* dateStr); //Rotem (remove) - changed signiture
void parseDate(Date* date, char* dateStr);
float parseDuration(char* durationStr);
void addVisit(Patient* patient, Visit* visit);
//void freeTree(plnTree* node);        //Rotem (remove) - moved to pTree.c
//void freePatient(Patient* patient);  //Rotem (remove) - need to move to Common.c
void freeDoc(Doc* doctor);
int isDigit(char c);
int menu();
//void printTree(plnTree* node);  //Rotem (remove) - moved to pTree.c
//void printPatient(Patient* patient); 
//void printVisit(Visit* visit);

int main(){

    pTree FullpTree;
    initBST(&FullpTree);
	loadPatients(&FullpTree);
    int answer = 0;
    do
    {
        answer = menu();
        switch (answer)
        {
        case 1:
            //AdmitPatient(FullpTree);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            break;
        case 12:
            break;
        case 0:
            break;
        default:
            printf("Invalid choice, please try again\n\n");
        }
    } while (answer);

    return 0;
}

void ReadVisitDataFromFile(FILE* pFile, Patient* patient) {
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), pFile)) {
        // Remove newline character
        buffer[strcspn(buffer, "\n")] = 0;

        if (strcmp(buffer, "========================") == 0) {//Rotem (comment) end of visit data
            return;
        }

        if (strlen(buffer) == 0) {
            continue;
        }
        else if (strstr(buffer, "Arrival:") != NULL) {
            char arrival[20] = "";
            if (sscanf(buffer, "Arrival:%[^D]", arrival) != 1) {
                fprintf(stderr, "Error parsing visit info: %s\n", buffer);
                continue;
            }

            char dismissed[20] = "";
            fgets(buffer, sizeof(buffer), pFile);
            if (sscanf(buffer, "Dismissed:%[^D]", dismissed) != 1) {
                fprintf(stderr, "Error parsing visit info: %s\n", buffer);
                continue;
            }

            char duration[10] = "";
            fgets(buffer, sizeof(buffer), pFile);
            if (sscanf(buffer, "Duration:%[^D]", duration) != 1) {
                fprintf(stderr, "Error parsing visit info: %s\n", buffer);
                continue;
            }

            char doctorName[50] = "";
            fgets(buffer, sizeof(buffer), pFile);
            if (sscanf(buffer, "Doctor:%[^S]", doctorName) != 1) {
                fprintf(stderr, "Error parsing visit info: %s\n", buffer);
                continue;
            }

            char summary[256] = "";
            fgets(buffer, sizeof(buffer), pFile);
            if (sscanf(buffer, "Summary:%[^\n]", summary) != 1) {//Rotem: error need to fix, if summary is empty it prints error and go back to while
                fprintf(stderr, "Error parsing visit info: %s\n", buffer);
                continue;
            }

            Doc* doctor = createDoc(doctorName, "0000000"); // License placeholder
            Visit* visit = createVisit(arrival, dismissed, duration, doctor, summary);
            addVisit(patient, visit);
        }
    }
}
void loadPatients(pTree* FullpTree) {
    FILE* pFile = fopen("Patients.txt", "r");
    if (pFile == NULL)
    {
        printf("Error reading file");
        return;
    }

    char buffer[100] = { 0 }; 
    Patient* currentPatient = NULL; 
    
    fgets(buffer, sizeof(buffer), pFile); //Rotem - get rid of header line
    
    while (fgets(buffer, sizeof(buffer), pFile)) {
        // Remove newline character
        buffer[strcspn(buffer, "\n")] = 0;

        if (strlen(buffer) == 0 || strcmp(buffer, "========================") == 0) {
            continue;
        }

        if (strchr(buffer, '.') && isDigit(buffer[0])) {//Rotem: what the isDigit for?
    /*        if (currentPatient != NULL) {//Rotem: (Remove) adding to the tree at the end of the while
                insertNode(FullpTree, currentPatient);
            }*/
            char name[50], id[11], allergiesStr[50];//Rotem allerrgies might be too small, if someone have all
            if (sscanf(buffer, "%*d.%[^;];%[^;];%s", name, id, allergiesStr) != 3) {
                fprintf(stderr, "Error parsing patient info: %s\n", buffer);
                continue;
            }
            currentPatient = createPatient(name, id, allergiesStr);
        }
        //Add Visits Data
        ReadVisitDataFromFile(pFile, currentPatient);

        if (currentPatient != NULL) {
            insertBST(FullpTree, currentPatient);
        }
    }
    fclose(pFile);
}

int isDigit(char c) {
    return (c >= '0' && c <= '9');
}
/*Rotem: remove, moved to pTree.c 
void insertPatient(pTree* tree, Patient* patient) {
    insertPatientNode(&tree->root, patient);
}

void insertPatientNode(plnTree** node, Patient* patient) {
    if (node == NULL) {
        fprintf(stderr, "Error: node is NULL\n");
    }
    if (*node == NULL) {
        plnTree* newNode = (plnTree*)malloc(sizeof(plnTree));
        if (newNode == NULL) {
            fprintf(stderr, "Memory allocation failed while adding a patient node\n");
            exit(EXIT_FAILURE); // Handle the error appropriately
        }
        newNode->tpatient = patient;
        newNode->left = NULL;
        newNode->right = NULL;
        *node = newNode;
    }
    else {
        if (strcmp((char*)patient->ID, (char*)(*node)->tpatient->ID) < 0) {
            insertPatientNode(&(*node)->left, patient);
        }
        else {
            insertPatientNode(&(*node)->right, patient);
        }
    }
}
*/
Patient* createPatient(char* name, char* ID, char* allergiesStr) {
    Patient* patient = (Patient*)malloc(sizeof(Patient));
    if (patient == NULL) {
        fprintf(stderr, "Memory allocation failed while creating a patient\n");
        exit(EXIT_FAILURE); // Handle the error appropriately
    }

    patient->name = strdup(name);
    strncpy(patient->ID, ID, 10);
    /* Rotem remove - no need a ID is char[] 
    for (int i = 0; i < 10; i++) {//Rotem: why not use atoi
        patient->ID[i] = ID[i] - '0';
    }
    patient->ID[10] = '\0';//Rotem: off by 1, to show Yotam in debugger
    */
    patient->Allergies = parseAllergies(allergiesStr);
    patient->Visits = NULL;
    patient->nVisits = 0;
    return patient;
}

Doc* createDoc(char* name, char* nLicense) {
    Doc* doctor = (Doc*)malloc(sizeof(Doc));
    if (doctor == NULL) {
        fprintf(stderr, "Memory allocation failed while creating a doctor\n");
        exit(EXIT_FAILURE); // Handle the error appropriately
    }

    doctor->name = strdup(name);
    for (int i = 0; i < 8; i++) {//Rotem: what for?
        doctor->nLicense[i] = nLicense[i] - '0';
    }

   // doctor->nPatients = 0; //Rotem: need to see what we put here.
    return doctor;
}

Visit* createVisit(char* arrival, char* dismissed, char* duration, Doc* doctor, char* summary) {
    Visit* visit = (Visit*)malloc(sizeof(Visit));
    if (visit == NULL) {
        fprintf(stderr, "Memory allocation failed while creating a visit\n");
        exit(EXIT_FAILURE); // Handle the error appropriately
    }

    parseDate(&visit->tArrival, arrival); //Rotem: I changed the function signiture
    parseDate(&visit->tDismissed, dismissed); //Rotem: I changed the function signiture;
    visit->fDuration = parseDuration(duration);
    visit->Doctor = doctor;
    visit->vSummary = summary[0] == '\0' ? NULL : strdup(summary);
    if (summary[0] != '\0' && visit->vSummary == NULL) {//Rotem: check this again, it is valid that there is no summary
        fprintf(stderr, "Memory allocation failed while duplicating visit summary\n");
        free(visit);
        exit(EXIT_FAILURE);
    }
    return visit;
}

unsigned char parseAllergies(const char* allergiesStr) {//Rotem, the string is not changing so use const
    unsigned char allergies = NONE;
    if (strstr(allergiesStr, "PENICILLIN")) allergies |= PENICILLIN;//Rotem, error not working as you are using capital letters
    if (strstr(allergiesStr, "SULFA")) allergies |= SULFA;
    if (strstr(allergiesStr, "OPIOIDS")) allergies |= OPIOIDS;
    if (strstr(allergiesStr, "ANESTHETICS")) allergies |= ANESTHETICS;
    if (strstr(allergiesStr, "EGGS")) allergies |= EGGS;
    if (strstr(allergiesStr, "LATEX")) allergies |= LATEX;
    if (strstr(allergiesStr, "PRESERVATIVES")) allergies |= PRESERVATIVES;
    return allergies;
}

void parseDate(Date* date, char* dateStr) {
    
    if (sscanf(dateStr, "%d/%d/%d %d:%d", &(date->Day), &(date->Month), &(date->Year), &(date->Hour), &(date->Min)) != 5) {//Rotem: add () around day, month...
        //fprintf(stderr, "Error parsing date: %s\n", dateStr); //Rotem remove this is not error when no dismissal
        date->Day = date->Month = date->Year = date->Hour = date->Min = -1; // Rotem comment patient still in ER
    }
}

float parseDuration(char* durationStr) {
    int hours, minutes;
    if (sscanf(durationStr, "%d:%d", &hours, &minutes) != 2) { 
        //fprintf(stderr, "Error parsing duration: %s\n", durationStr);//Rotem remove this is not error when no dismissal
        return -1.0f; // Rotem comment patient still in ER
    }
    return (float)hours + (float)(minutes / 60.0);
}

void addVisit(Patient* patient, Visit* visit) {
    patient->nVisits++; 
    
    //Rotem: need to add to the stuck of visits (Push?)

  /*  Visit* temp = (Visit*)realloc(patient->Visits, patient->nVisits * sizeof(Visit));//Rotem: why realloc? we already allocate visit memory
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation failed while adding a visit\n");
        // Handle the error appropriately
        exit(EXIT_FAILURE);
    }
    patient->Visits = temp;
    patient->Visits[patient->nVisits - 1] = visit;*/
}



void freeDoc(Doc* doctor) {
    if (doctor == NULL) return;
    free(doctor->name);
    free(doctor);
}

int menu()
{
    int answer = 0;
    printf("Welcome to the hospital ER System\n");
    printf("Please choose one of the following commands: \n"
        "1 : Admit Patient\n"
        "2 : Check for patient's allergies\n"
        "3 : Display all patients\n"
        "4 : Display all patients'addmissions\n"
        "5 : Display All patients in line\n"
        "6 : Advance patient in line\n"
        "7 : Display list of Doctors\n"
        "8 : Display All patients assigned to a doctor\n"
        "9 : Discharg patient\n"
        "10 : Remove visit\n"
        "11 : Remove patient\n"
        "12 : Close the hospital\n"
        "0 : Exit program\n"
    );
    int err = scanf("%d", &answer);
    if (err <= 0 || answer <= 0) //failure in reading
    {
        //clean_stdin(); //flush extra chars in consule
        return -1;
    }

    return answer;
}
