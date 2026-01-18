#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "pTree.h"

//AdmitPatient(PatientTree);
/****************************************************
int menu()

Description:
This function will display a menu with all the option
for the librarian to manage the library's members

Return value:
(answer) - selection from the menu
(-1) - failure (i.e. failure when reading answer)
*****************************************************/
/*
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
    int err = scanf_s("%d", &answer);
    if (err <= 0 || answer <= 0) //failure in reading
    {
        //clean_stdin(); //flush extra chars in consule
        return -1;
    }

    return answer;
}

/*
AdmitPatient(PatientTree)
{

    if (CheckAvalibleDoc(pDoc) //???? ????? ?????, ?? ????? ?? ???? ???? ???? ?????. ????? ????, ??? ????? ?? ????? ??????
    {
        char* name;
        int ID[11];
        GetID(ID); //????? ??? ???? ????, ????? ????? ??????? ???? ? ??? ?.
        unsigned char Allergies;
        Patient* pPatient = searchPatient(ID);
        if (searchPatient(ID) == NULL) //????? ??? ?????? ???? ????? ???????
        {
            //not exist, get all patient data
            //allocate pPatient
            getName(name); //need to alloc inside
            getAllergies(&Allergies);
            pPatient.name = name;
            pPatient.Allergies = Allergies;
            AddPatientToTree(pTree, pPatient)
        }
        assignDoctor2case;//find a doc
        AddVisit(pPatient);//add a visit struct to the patient
        AddPatientToLine(pLine, pPatient); //add to the end of the line
        UpdateDoctorsList(pDoc, ? )//



    }




}*/