
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_DIDNT_OPEN_ERROR (-1)
#define MAX_LINE 1024
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

int InsertAfter(position p, char* targetLastName,
    char* name, char* lastName, int birthYear);
int InsertBefore(position p, char* targetLastName,
    char* name, char* lastName, int birthYear);
int SortList(position p);
int SaveList(position p, char* fileName);
int LoadList(position p, char* fileName);

int main(void) {
    char name[MAX_LINE] = { 0 };
    char lastName[MAX_LINE] = { 0 };
    char targetLastName[MAX_LINE] = { 0 };
    char fileName[MAX_LINE] = { 0 };
    int birthYear = 0;
    int choice;

    position temp = NULL;
    position head = (position)malloc(sizeof(person));

    if (head == NULL) {
        printf("Memory not allocated correctly!\n");
        return MEMORY_NOT_ALLOCATED_CORRECT;
    }

    head->next = NULL;

    while (1) {
        printf("\nChoose what you want to do:\n");
        printf("1 - Insert a person at the beginning\n");
        printf("2 - Insert a person at the end\n");
        printf("3 - Find a person by last name\n");
        printf("4 - Delete a person by last name\n");
        printf("5 - Print list\n");
        printf("6 - Delete list\n");
        printf("7 - Exit\n");
        printf("8 - Insert after a person\n");
        printf("9 - Insert before a person\n");
        printf("10 - Sort list by last name\n");
        printf("11 - Save list to a file\n");
        printf("12 - Load list from a file\n");
        printf("Your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            DeleteList(head);
            free(head);
            return EXIT_FAILURE;
        }

        switch (choice) {
        case 1:
        case 2:
        case 8:
        case 9:
            printf("Enter name: ");
            scanf("%1023s", name);

            printf("Enter last name: ");
            scanf("%1023s", lastName);

            printf("Enter birth year: ");
            if (scanf("%d", &birthYear) != 1) {
                printf("Invalid birth year!\n");
                DeleteList(head);
                free(head);
                return EXIT_FAILURE;
            }

            if (choice == 1) {
                PrependList(head, name, lastName, birthYear);
            }
            else if (choice == 2) {
                AppendList(head, name, lastName, birthYear);
            }
            else {
                printf("Enter the target person's last name: ");
                scanf("%1023s", targetLastName);

                if (choice == 8) {
                    InsertAfter(head, targetLastName,
                        name, lastName, birthYear);
                }
                else {
                    InsertBefore(head, targetLastName,
                        name, lastName, birthYear);
                }
            }
            break;

        case 3:
            printf("Enter last name to find: ");
            scanf("%1023s", lastName);

            temp = FindByLastName(head->next, lastName);

            if (temp != NULL) {
                printf("%s %s, %d\n",
                    temp->name, temp->lastName, temp->birthYear);
            }
            break;

        case 4:
            printf("Enter last name to delete: ");
            scanf("%1023s", lastName);

            temp = FindByLastName(head->next, lastName);

            if (temp != NULL) {
                DeleteByLastName(head, temp);
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

        case 10:
            SortList(head);
            printf("List sorted by last name.\n");
            break;

        case 11:
            printf("Enter file name: ");
            scanf("%1023s", fileName);
            SaveList(head->next, fileName);
            break;

        case 12:
            printf("Enter file name: ");
            scanf("%1023s", fileName);
            LoadList(head, fileName);
            break;

        default:
            printf("Invalid choice!\n");
            break;
        }
    }
}

position CreateNewPerson(char* name, char* lastName, int birthYear) {
    position newPerson = (position)malloc(sizeof(person));

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
    position q = CreateNewPerson(name, lastName, birthYear);

    if (q == NULL) {
        return MEMORY_NOT_ALLOCATED_CORRECT;
    }

    q->next = p->next;
    p->next = q;

    return EXIT_SUCCESS;
}

int PrintList(position p) {
    if (p == NULL) {
        printf("The list is empty!\n");
        return EXIT_SUCCESS;
    }

    while (p != NULL) {
        printf("%s %s, %d\n",
            p->name, p->lastName, p->birthYear);
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
    position q = CreateNewPerson(name, lastName, birthYear);

    if (q == NULL) {
        return MEMORY_NOT_ALLOCATED_CORRECT;
    }

    position last = FindLast(p);
    last->next = q;

    return EXIT_SUCCESS;
}

position FindByLastName(position p, char* lastName) {
    while (p != NULL && strcmp(p->lastName, lastName) != 0) {
        p = p->next;
    }

    if (p == NULL) {
        printf("There is no such person in the list.\n");
    }

    return p;
}

position FindPrevious(position p, position q) {
    while (p != NULL && p->next != q) {
        p = p->next;
    }

    return p;
}

int DeleteByLastName(position p, position toDelete) {
    if (p == NULL || toDelete == NULL) {
        return FILE_DIDNT_OPEN_ERROR;
    }

    position prev = FindPrevious(p, toDelete);

    if (prev == NULL) {
        return FILE_DIDNT_OPEN_ERROR;
    }

    prev->next = toDelete->next;
    free(toDelete);

    return EXIT_SUCCESS;
}

int DeleteList(position p) {
    if (p == NULL) {
        return EXIT_SUCCESS;
    }

    position temp = NULL;

    while (p->next != NULL) {
        temp = p->next;
        p->next = temp->next;
        free(temp);
    }

    return EXIT_SUCCESS;
}

/* A - Insert after a person */
int InsertAfter(position p, char* targetLastName,
    char* name, char* lastName, int birthYear) {

    position target = FindByLastName(p->next, targetLastName);

    if (target == NULL) {
        return FILE_DIDNT_OPEN_ERROR;
    }

    position q = CreateNewPerson(name, lastName, birthYear);

    if (q == NULL) {
        return MEMORY_NOT_ALLOCATED_CORRECT;
    }

    q->next = target->next;
    target->next = q;

    return EXIT_SUCCESS;
}

/* B - Insert before a person */
int InsertBefore(position p, char* targetLastName,
    char* name, char* lastName, int birthYear) {

    position target = FindByLastName(p->next, targetLastName);

    if (target == NULL) {
        return FILE_DIDNT_OPEN_ERROR;
    }

    position prev = FindPrevious(p, target);

    if (prev == NULL) {
        return FILE_DIDNT_OPEN_ERROR;
    }

    position q = CreateNewPerson(name, lastName, birthYear);

    if (q == NULL) {
        return MEMORY_NOT_ALLOCATED_CORRECT;
    }

    q->next = target;
    prev->next = q;

    return EXIT_SUCCESS;
}

/* C - Sort list alphabetically by last name */
int SortList(position p) {
    int swapped;
    position prev;
    position current;
    position nextPerson;

    if (p == NULL) {
        return FILE_DIDNT_OPEN_ERROR;
    }

    do {
        swapped = 0;
        prev = p;
        current = p->next;

        while (current != NULL && current->next != NULL) {
            nextPerson = current->next;

            if (strcmp(current->lastName, nextPerson->lastName) > 0) {
                current->next = nextPerson->next;
                nextPerson->next = current;
                prev->next = nextPerson;

                swapped = 1;
                prev = nextPerson;
            }
            else {
                prev = current;
                current = current->next;
            }
        }
    } while (swapped);

    return EXIT_SUCCESS;
}

/* D - Save list to a file */
int SaveList(position p, char* fileName) {
    FILE* file = fopen(fileName, "w");

    if (file == NULL) {
        printf("Error opening file!\n");
        return FILE_DIDNT_OPEN_ERROR;
    }

    while (p != NULL) {
        if (fprintf(file, "%s %s %d\n",
            p->name, p->lastName, p->birthYear) < 0) {
            fclose(file);
            return FILE_DIDNT_OPEN_ERROR;
        }

        p = p->next;
    }

    fclose(file);
    printf("List saved to file.\n");

    return EXIT_SUCCESS;
}

/* E - Load list from a file */
int LoadList(position p, char* fileName) {
    FILE* file = fopen(fileName, "r");

    if (file == NULL) {
        printf("Error opening file!\n");
        return FILE_DIDNT_OPEN_ERROR;
    }

    char name[MAX_LINE];
    char lastName[MAX_LINE];
    int birthYear;

    /* Replace the current list with the contents of the file. */
    DeleteList(p);

    while (fscanf(file, "%1023s %1023s %d",
        name, lastName, &birthYear) == 3) {

        if (AppendList(p, name, lastName, birthYear) != EXIT_SUCCESS) {
            fclose(file);
            return MEMORY_NOT_ALLOCATED_CORRECT;
        }

        p = FindLast(p);
    }

    fclose(file);
    printf("List loaded from file.\n");

    return EXIT_SUCCESS;
}
