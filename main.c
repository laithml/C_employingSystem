#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int N = 20;

typedef struct recommender {
    char firstName[20];
    char lastName[20];
    char Email[20];

} Recommender;

typedef struct developer {
    char firstName[20];
    char lastName[20];
    char Degree[20];
    Recommender *Rec1;
    Recommender *Rec2;
    struct developer *Dev1;
    struct developer *Dev2;
} Developer;

void printWorkers(Developer *emp[], int);

void printCan(Developer *can[], int index);

int Hire(Developer *can[], Developer *emp[], int can_ind, int emp_ind);

void InsertCan(Developer *can[], Developer *emp[], int index,int index2);

int main() {
    Developer *employees[N], *candidates[N];
    int can_index = 0;
    int emp_index = 0;
    int c = 0;

    while (c != 5) {
        printf("Welcome, what do you want to do?\n");
        printf("1. Print candidates.\n2. Print workers.\n3. Insert new Candidate.\n");
        printf("4. Hire candidate.\n");
        printf("5. Exit.\n");
        scanf("%d", &c);
        if (c == 1) {
            printCan(candidates, can_index);
        }
        if (c == 2)
            printWorkers(employees, emp_index);
        if (c == 3) {
            InsertCan(candidates, employees, can_index,emp_index);
            can_index++;
        }
        if (c == 4) {
            int x = Hire(candidates, employees, can_index, emp_index);
            if (x == 1) {
                emp_index++;
                can_index--;
            }
        }
        if (c == 5)
            break;
    }
    for (int i = 0; i <can_index; i++) {
        free(candidates[i]->Rec1);
        free(candidates[i]->Rec2);
        free(candidates[i]->Dev1);
        free(candidates[i]->Dev2);
        free(candidates[i]);
    }
    for (int i = 0; i < emp_index; ++i)
        free(employees[i]);



    return 0;
}

int Hire(Developer *can[], Developer *emp[], int can_ind, int emp_ind) {
    char fName[20], lName[20];
    int done = 0;
    printf("First name: \n");
    scanf("%s", fName);
    printf("Last name: \n");
    scanf("%s", lName);
    for (int i = 0; i < can_ind; i++) {
        if (strcmp(fName, can[i]->firstName) == 0 && strcmp(lName, can[i]->lastName) == 0) {
            done = 1;
            emp[emp_ind]=(Developer*) malloc(sizeof(Developer));
            strcpy(emp[emp_ind]->firstName, fName);
            strcpy(emp[emp_ind]->lastName, lName);
            emp[emp_ind]->Dev1 = NULL;
            emp[emp_ind]->Dev2 = NULL;
            emp[emp_ind]->Rec1 = NULL;
            emp[emp_ind]->Rec2 = NULL;
            emp_ind++;
            for (int j = i; j < can_ind; j++) {
                can[j] = can[j + 1];

            }
        }
    }
    if (done == 0) {
        printf("the candidate not found\n");
        return 0;
    }

    printf("Congratulations!,%s %s is now Employee\n", fName, lName);
    return 1;


}


void printWorkers(Developer *emp[], int emp_ind) {
    for (int i = 0; i < emp_ind; i++) {
        printf("Employee name: %s %s\n", emp[i]->firstName, emp[i]->lastName);

    }
    if (emp_ind == 0)
        printf("there's no worker in the company\n");
}

void printCan(Developer *can[], int index) {
    if (index == 0) {
        printf("there's no candidates\n");
        return;
    }
    for (int i = 0; i < index; i++) {
        printf("------ {Candidate number %d} ------\n", i + 1);
        printf("Candidate name: %s %s\n", can[i]->firstName, can[i]->lastName);
        printf("Candidate Degree: %s\n", can[i]->Degree);
        if (can[i]->Dev1 != NULL) {
            printf("1st Recommender from the company.\nname: %s %s\n", can[i]->Dev1->firstName, can[i]->Dev1->lastName);
        }
        if (can[i]->Dev2 != NULL ) {
            printf("2nd Recommender name from the company.\nname: %s %s\n", can[i]->Dev2->firstName,
                   can[i]->Dev2->lastName);
        }
        if (can[i]->Rec1 != NULL ) {
            printf("1st Recommender outside the company.\nname: %s %s\nEmail: %s \n", can[i]->Rec1->firstName,
                   can[i]->Rec1->lastName, can[i]->Rec1->Email);
        }
        if (can[i]->Rec2 != NULL ) {
            printf("2nd Recommender outside the company.\nname: %s %s\nEmail: %s\n", can[i]->Rec2->firstName,
                   can[i]->Rec2->lastName, can[i]->Rec2->Email);
        }
        printf("----------------------------\n");
    }
}

void InsertCan(Developer *can[], Developer *emp[], int can_index,int emp_index) {
    Recommender *rec1, *rec2;
    int RecNum, DevRecNum;
    can[can_index]=(Developer*) malloc(sizeof(Developer));
    printf("First name: \n");
    scanf("%s", can[can_index]->firstName);
    printf("Last name: \n");
    scanf("%s", can[can_index]->lastName);
    printf("Degree: \n");
    scanf("%s", can[can_index]->Degree);
    printf("how many recommenders outside the company are there?:\n");
    scanf("%d", &RecNum);
    if (RecNum > 2) {
        printf("only you can add 2 of them\n");
        printf("how many recommenders outside the company are there?:\n");
        scanf("%d", &RecNum);
    }
    if(RecNum==0){
        can[can_index]->Rec1=NULL;
        can[can_index]->Rec2=NULL;

    }
    if(RecNum==1) can[can_index]->Rec2=NULL;


    for (int i = 1; i <= RecNum; ++i) {
        if (i == 1) {
            rec1 = (Recommender *) malloc(sizeof(Recommender));
            printf("1-First name:\n");
            scanf("%s", rec1->firstName);
            printf("1-Last name:\n");
            scanf("%s", rec1->lastName);
            printf("1-Email:\n");
            scanf("%s", rec1->Email);
            can[can_index]->Rec1 = rec1;
        }
        if (i == 2) {
            rec2 = (Recommender *) malloc(sizeof(Recommender));
            printf("2-First name:\n");
            scanf("%s", rec2->firstName);
            printf("2-Last name:\n");
            scanf("%s", rec2->lastName);
            printf("2-Email:\n");
            scanf("%s", rec2->Email);
            can[can_index]->Rec2 = rec2;
        }
    }
    printf("how many recommenders from the company are there?: \n");
    scanf("%d", &DevRecNum);
    if (DevRecNum > 2) {
        printf("only you can add 2 of them\n");
        printf("how many recommenders from the company are there?: \n");
        scanf("%d", &DevRecNum);
    }
    for (int i = 0; i < DevRecNum; ++i) {
        char firstName[N], lastName[N];
        printf("First name:\n");
        scanf("%s", firstName);
        printf("Last name:\n");
        scanf("%s", lastName);
        int exist = 0;
        if (i+1 == 1) {
            for (int j = 0; j < emp_index; j++) {
                if (strcmp(firstName, emp[j]->firstName) == 0 && strcmp(lastName, emp[j]->lastName) == 0) {
                    can[can_index]->Dev1 = (Developer *) malloc(sizeof(Developer));
                    can[can_index]->Dev1 = emp[j];
                    exist = 1;
                }
            }
            if (exist == 0)
                printf("the developer isn't exist\n");
            exist = 0;
        }

        if (i+1 == 2) {
            for (int j = 0; j < emp_index; j++) {
                if (strcmp(firstName, emp[j]->firstName) == 0 && strcmp(lastName, emp[j]->lastName) == 0) {
                    can[can_index]->Dev2 = (Developer *) malloc(sizeof(Developer));
                    can[can_index]->Dev2 = emp[j];
                    exist = 1;
                }
            }
            if (exist == 0)
                printf("the developer isn't exist\n");
            exist = 0;
        }
    }
    printf("new candidate added successful\n");
}


