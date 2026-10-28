
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_DIDNT_OPEN_ERROR (-1)
#define MAX_LINE (1024)
#define MEMORY_NOT_ALLOCATED_CORRECT (-1)

struct _person;
typedef struct _person* position;

typedef struct _person {
    char name[MAX_LINE];
    char lastName[MAX_LINE];
    int birthYear;

    position next;
} person;

position CreateNewPerson(char* name, char* lastName, int birthYear);
int PrependList(position p, char* name, char* lastName, int birthYear);
int PrintList(position p);
position FindLast(position p);
int AppendList(position p, char* name, char* lastName, int birthYear);
position FindByLastName(position p, char* lastName);
int DeleteByLastName(position p, position toDelete);
position FindPrevious(position p, position q);
int DeleteList(position p);

int main(void) {
    char name[MAX_LINE] = { 0 };
    char lastName[MAX_LINE] = { 0 };
    int birthYear = 0;
    char lastNameDel[MAX_LINE] = { 0 };
    int choice;

    position temp = NULL;
    position head = NULL;
    position q = NULL;

    head = (position)malloc(sizeof(person));

    if (head == NULL) {
        printf("Memory not allocated correctly!\n");
        return MEMORY_NOT_ALLOCATED_CORRECT;
    }

    head->name[0] = '\0';
    head->lastName[0] = '\0';
    head->birthYear = 0;
    head->next = NULL;

    while (1) {
        printf("\nChoose what you want to do:\n");
        printf("1 - Insert a person at the beginning of the list\n");
        printf("2 - Insert a person at the end of the list\n");
        printf("3 - Find a person in the list by last name\n");
        printf("4 - Delete a person with certain last name\n");
        printf("5 - Print list\n");
        printf("6 - Delete list\n");
        printf("7 - Exit\n");
        printf("Your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            DeleteList(head);
            free(head);
            return EXIT_FAILURE;
        }

        switch (choice) {
        case 1:
            printf("Type in name of the person you want to insert: ");
            scanf("%1023s", name);

            printf("Type in last name of the person you want to insert: ");
            scanf("%1023s", lastName);

            printf("Type in birth year of the person you want to insert: ");
            scanf("%d", &birthYear);

            PrependList(head, name, lastName, birthYear);
            break;

        case 2:
            printf("Type in name of the person you want to insert: ");
            scanf("%1023s", name);

            printf("Type in last name of the person you want to insert: ");
            scanf("%1023s", lastName);

            printf("Type in birth year of the person you want to insert: ");
            scanf("%d", &birthYear);

            AppendList(head, name, lastName, birthYear);
            break;

        case 3:
            printf("Type in the last name of a person you want to find: ");
            scanf("%1023s", lastName);

            temp = FindByLastName(head->next, lastName);

            if (temp != NULL) {
                printf("\nPerson you were looking for is: %s %s, %d\n",
                    temp->name, temp->lastName, temp->birthYear);
            }
            break;

        case 4:
            printf("Type in the last name of a person you want to delete: ");
            scanf("%1023s", lastNameDel);

            q = FindByLastName(head->next, lastNameDel);

            if (q != NULL) {
                DeleteByLastName(head, q);
            }
            break;

        case 5:
            PrintList(head->next);
            break;

        case 6:
            DeleteList(head);
            break;

        case 7:
            DeleteList(head);
            free(head);
            return EXIT_SUCCESS;

        default:
            printf("Invalid choice!\n");
            break;
        }
    }

    return EXIT_SUCCESS;
}

position CreateNewPerson(char* name, char* lastName, int birthYear) {
    position newPerson = NULL;

    newPerson = (position)malloc(sizeof(person));

    if (newPerson == NULL) {
        printf("Memory not allocated correctly!\n");
        return NULL;
    }

    strcpy(newPerson->name, name);
    strcpy(newPerson->lastName, lastName);
    newPerson->birthYear = birthYear;
    newPerson->next = NULL;

    return newPerson;
}

int PrependList(position p, char* name, char* lastName, int birthYear) {
    position q = NULL;

    q = CreateNewPerson(name, lastName, birthYear);

    if (q == NULL) {
        return MEMORY_NOT_ALLOCATED_CORRECT;
    }

    q->next = p->next;
    p->next = q;

    return EXIT_SUCCESS;
}

int PrintList(position p) {
    if (p == NULL) {
        printf("Nema elemenata, lista je prazna!\n");
        return EXIT_SUCCESS;
    }

    while (p != NULL) {
        printf("%s\n", p->name);
        printf("%s\n", p->lastName);
        printf("%d\n", p->birthYear);

        p = p->next;
    }

    return EXIT_SUCCESS;
}

position FindLast(position p) {
    while (p->next != NULL) {
        p = p->next;
    }

    return p;
}

int AppendList(position p, char* name, char* lastName, int birthYear) {
    position q = NULL;
    position last = NULL;

    q = CreateNewPerson(name, lastName, birthYear);

    if (q == NULL) {
        return MEMORY_NOT_ALLOCATED_CORRECT;
    }

    last = FindLast(p);

    q->next = last->next;
    last->next = q;

    return EXIT_SUCCESS;
}

position FindByLastName(position p, char* lastName) {
    while (p != NULL && strcmp(p->lastName, lastName) != 0) {
        p = p->next;
    }

    if (p == NULL) {
        printf("There is no such element in the list.\n");
    }

    return p;
}

int DeleteByLastName(position p, position toDelete) {
    position prev = NULL;

    if (p == NULL || toDelete == NULL) {
        return FILE_DIDNT_OPEN_ERROR;
    }

    prev = FindPrevious(p, toDelete);

    if (prev == NULL) {
        return FILE_DIDNT_OPEN_ERROR;
    }

    prev->next = toDelete->next;
    free(toDelete);

    return EXIT_SUCCESS;
}

position FindPrevious(position p, position q) {
    position temp = p;

    while (temp != NULL && temp->next != q) {
        temp = temp->next;
    }

    return temp;
}

int DeleteList(position p) {
    position temp = NULL;

    if (p == NULL) {
        return EXIT_SUCCESS;
    }

    while (p->next != NULL) {
        temp = p->next;
        p->next = temp->next;
        free(temp);
    }

    return EXIT_SUCCESS;
}
