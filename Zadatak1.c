/*1. Napisati program koji prvo pročita koliko redaka ima datoteka, tj. koliko ima studenata zapisanih u datoteci. Nakon toga 
potrebno je dinamički alocirati prostor za niz struktura studenata (ime, prezime, bodovi) i učitati iz datoteke sve zapise. Na ekran 
ispisati ime, prezime, apsolutni i relativni broj bodova. Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj 
bodova na kolokviju. relatvan_br_bodova = br_bodova/max_br_bodova*100*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//defininig constant values
#define MAX_BUFFER_SIZE (1024)
#define MAX_FILE_NAME (128)
#define MAX_NAME_SIZE (128)
#define MAX_LINE (128)
#define FILE_OPENING_ERROR (-1)
#define GET_INFO_SUCCESS (0)
#define MAX_NUM_POINTS (60)
#define SUCCESS (0)
#define MEMORY_ALLOC_FAIL (-1)


struct _Student;
//structure Student of type struct _Student
typedef struct _Student
{
    char name[MAX_NAME_SIZE];
    char surname[MAX_NAME_SIZE];
    int points;

}Student;


//funtion definitions
int countStudentsFromFile(char*);
int getStudentInfo(char*, int, Student*);
void printStudentInfo(int, Student*);

//main
int main(void)
{
    //variables for get_student_info
    Student* studenti = NULL;
    int i = 0;
    int show = -1;

    //variables for countStudent
    char fileName[MAX_FILE_NAME] = { 0 };
    int numOfStudents = 0;

    //ask user for file name
    printf("Insert filename > ");
    scanf(" %s", fileName);

    //get value from function thats reading the file
    numOfStudents = countStudentsFromFile(fileName);

    //check if number of students read from file is more then zero
    //and only then proceed with mem alloc
    if (numOfStudents > 0)
    {
        studenti = (Student*)calloc(numOfStudents, sizeof(Student));
        //dynamically allocate memory based on result and check it
        if (studenti == NULL)
        {
            printf("Failed while allocating the memory, exiting the program...\n");
            return MEMORY_ALLOC_FAIL;
        }
    }

    //printing num of students on screen
    if (numOfStudents >= 0)
    {
        printf("Broj studenata u datoteci '%s' je %d\n", fileName, numOfStudents);
        //get info from file and store it in the structure
        show = getStudentInfo(fileName, numOfStudents, studenti);
    }

    //calling the printStudentInfo function if there was no error while getting the student data
    if (show == 0)
    {
        printStudentInfo(numOfStudents, studenti);
    }
    else
    {
        printf("Error when getting student info from the file!\n");
    }

    //free memory allocated
    free(studenti);

    return SUCCESS;
}


//function that opens the textfile and reads all student info from it,
//stores it in a structure and closes the file
int getStudentInfo(char* fileName, int numOfStudents, Student* studenti)
{
    int i = 0;
    int count = 0;
    char buffer[MAX_LINE] = { 0 };

    //opening the text file and setting it to a variable
    FILE* fp = NULL;
    fp = fopen(fileName, "r");


    //check if file has opened successfully (if not return error)
    if (fp == NULL)
    {
        printf("The file '%s' didn't open!\r\n", fileName);
        return FILE_OPENING_ERROR;
    }

    //looping through a known number of students
    for (i = 0; i < numOfStudents; i++)
    {
        char nameInp[MAX_NAME_SIZE] = "";
        char surnameInp[MAX_NAME_SIZE] = "";
        int pointsInp = 0;

        //skipping rows which are blank and don't contain student info
        while (1)
        {
            fgets(buffer, MAX_BUFFER_SIZE, fp);

            if (strcmp("\n", buffer) != 0)
            {
                break;
            }
        }

        //copying data from the buffer to the variables 
        sscanf(buffer, "%s %s %d", nameInp, surnameInp, &pointsInp);


        Student* currentStudent = studenti + i;

        //copying data from variables to the structure via pointer
        strcpy(currentStudent->name, nameInp);
        strcpy(currentStudent->surname, surnameInp);
        currentStudent->points = pointsInp;

    }

    //closing the text file
    fclose(fp);

    return GET_INFO_SUCCESS;
}


//function that takes in num of students and structure pointer
//it prints all student info on screen
void printStudentInfo(int numOfStudents, Student* studenti)
{
    int i = 0;
    float rel_points = 0.0;
    printf("\nPrinting student info:\n");

    //looping through the known number of students and printing their info
    for (i = 0; i < numOfStudents; i++)
    {
        Student stud = *(studenti + i);
        //calculating their relative score
        rel_points = (((float)stud.points / MAX_NUM_POINTS) * 100);

        //printing everything on the screen
        printf("Student %s %s ima %d apsolutnih odnosno %.2f%% bodova!\n", stud.name, stud.surname, stud.points, rel_points);
    }

}


//function that opens the textfile reads how many students there are
//then it returns the value that it got
int countStudentsFromFile(char* fileName)
{
    //opening the text file and setting it to a variable
    FILE* fp = NULL;
    fp = fopen(fileName, "r");

    int count = 0;
    char buffer[MAX_LINE] = { 0 };


    //checking if the file opened correctly, if not returning error
    if (fp == NULL)
    {
        printf("The file %s didn't open!\r\n", fileName);
        return FILE_OPENING_ERROR;
    }

    //going through the file and counting the number of students
    while (!feof(fp))
    {
        fgets(buffer, MAX_BUFFER_SIZE, fp);

        if (strcmp("\n", buffer) != 0)
        {
            count++;
        }
    }

    //closing the text file
    fclose(fp);

    //returning the number of students in the file
    return count;
}
