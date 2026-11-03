
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILE_DIDNT_OPEN_ERROR (-1)
#define MAX_LINE (1024)
#define MAX_FILE_NAME (256)
#define MEMORY_NOT_ALLOCATED_CORRECT (-1)

struct _polinom;
typedef struct _polinom* position;

typedef struct _polinom {
    int koef;
    int eksp;
    position next;
} polinom;


int readFromFile(position p1, position p2, char* fileName);
position createNewPoli(int koef, int eksp);
int insertSort(position p, int koef, int eksp);
int insertAfter(position p, position q);
int printPoliList(position p);
int polyAdd(position add, position p1, position p2);
int deleteAfter(position p);
int polyMult(position multy, position p1, position p2);
int Delete(position p);


int main(void) {

    polinom p1 = { .koef = 0, .eksp = 0, .next = NULL };
    polinom p2 = { .koef = 0, .eksp = 0, .next = NULL };
    polinom resAdd = { .koef = 0, .eksp = 0, .next = NULL };
    polinom resMult = { .koef = 0, .eksp = 0, .next = NULL };

    char fileName[MAX_FILE_NAME] = { 0 };

    printf("Type in file name: ");
    scanf("%255s", fileName);

    if (readFromFile(&p1, &p2, fileName) == EXIT_SUCCESS) {

        printf("\nPolinom 1: ");
        printPoliList(p1.next);

        printf("Polinom 2: ");
        printPoliList(p2.next);

        polyAdd(&resAdd, &p1, &p2);

        printf("\nResult of add function: ");
        printPoliList(resAdd.next);

        polyMult(&resMult, &p1, &p2);

        printf("Result of multiply function: ");
        printPoliList(resMult.next);
    }

    printf("\n==================================\n");

    Delete(p1.next);
    Delete(p2.next);
    Delete(resAdd.next);
    Delete(resMult.next);

    printf("Memory successfully freed!\n");

    return EXIT_SUCCESS;
}


int readFromFile(position p1, position p2, char* fileName) {

    FILE* fp = fopen(fileName, "r");

    if (fp == NULL) {
        printf("Dear customer, the file %s didn't open!\n", fileName);
        return FILE_DIDNT_OPEN_ERROR;
    }

    char buffer[MAX_LINE] = { 0 };
    char* ptr = NULL;

    int koef = 0;
    int eksp = 0;
    int n = 0;
    int counter = 1;

    while (fgets(buffer, MAX_LINE, fp) != NULL) {

        ptr = buffer;

        while (*ptr != '\0') {

            while (isspace((unsigned char)*ptr))
                ptr++;

            if (*ptr == '\0')
                break;

            if (sscanf(ptr, "%d %d %n", &koef, &eksp, &n) != 2) {
                printf("Invalid data in file!\n");
                fclose(fp);
                return EXIT_FAILURE;
            }

            if (counter == 1) {
                if (koef != 0)
                    insertSort(p1, koef, eksp);
            }
            else if (counter == 2) {
                if (koef != 0)
                    insertSort(p2, koef, eksp);
            }

            ptr += n;
        }

        counter++;
    }

    fclose(fp);

    return EXIT_SUCCESS;
}


position createNewPoli(int koef, int eksp) {

    position new = NULL;

    new = (position)malloc(sizeof(polinom));

    if (new == NULL) {
        printf("Memory not allocated correctly!\n");
        return NULL;
    }

    new->koef = koef;
    new->eksp = eksp;
    new->next = NULL;

    return new;
}


int insertSort(position p, int koef, int eksp) {

    position temp = p;
    position new = NULL;

    if (koef == 0)
        return EXIT_SUCCESS;

    while (temp->next != NULL && temp->next->eksp > eksp) {
        temp = temp->next;
    }

    if (temp->next != NULL && temp->next->eksp == eksp) {

        temp->next->koef += koef;

        if (temp->next->koef == 0)
            deleteAfter(temp);

        return EXIT_SUCCESS;
    }

    new = createNewPoli(koef, eksp);

    if (new == NULL)
        return MEMORY_NOT_ALLOCATED_CORRECT;

    insertAfter(temp, new);

    return EXIT_SUCCESS;
}


int insertAfter(position p, position q) {

    q->next = p->next;
    p->next = q;

    return EXIT_SUCCESS;
}


int printPoliList(position p) {

    if (p == NULL) {
        printf("0\n");
        return EXIT_SUCCESS;
    }

    int first = 1;

    while (p != NULL) {

        if (!first) {
            if (p->koef > 0)
                printf(" + ");
            else
                printf(" - ");
        }
        else if (p->koef < 0) {
            printf("-");
        }

        int absKoef = abs(p->koef);

        if (p->eksp == 0) {
            printf("%d", absKoef);
        }
        else if (p->eksp == 1) {
            if (absKoef != 1)
                printf("%d", absKoef);
            printf("x");
        }
        else {
            if (absKoef != 1)
                printf("%d", absKoef);
            printf("x^%d", p->eksp);
        }

        first = 0;
        p = p->next;
    }

    printf("\n");

    return EXIT_SUCCESS;
}


int deleteAfter(position p) {

    position toDel = p->next;

    if (toDel == NULL)
        return EXIT_SUCCESS;

    p->next = toDel->next;
    free(toDel);

    return EXIT_SUCCESS;
}


int polyAdd(position add, position p1, position p2) {

    position pt1 = p1->next;
    position pt2 = p2->next;

    while (pt1 != NULL && pt2 != NULL) {

        if (pt1->eksp == pt2->eksp) {
            insertSort(add, pt1->koef + pt2->koef, pt1->eksp);
            pt1 = pt1->next;
            pt2 = pt2->next;
        }

        else if (pt1->eksp > pt2->eksp) {
            insertSort(add, pt1->koef, pt1->eksp);
            pt1 = pt1->next;
        }

        else {
            insertSort(add, pt2->koef, pt2->eksp);
            pt2 = pt2->next;
        }
    }

    while (pt1 != NULL) {
        insertSort(add, pt1->koef, pt1->eksp);
        pt1 = pt1->next;
    }

    while (pt2 != NULL) {
        insertSort(add, pt2->koef, pt2->eksp);
        pt2 = pt2->next;
    }

    return EXIT_SUCCESS;
}


int polyMult(position multy, position p1, position p2) {

    position i = NULL;
    position j = NULL;

    int koeficijent = 0;
    int eksponent = 0;

    if (p1->next == NULL || p2->next == NULL)
        return EXIT_SUCCESS;

    for (i = p1->next; i != NULL; i = i->next) {

        for (j = p2->next; j != NULL; j = j->next) {

            koeficijent = i->koef * j->koef;
            eksponent = i->eksp + j->eksp;

            insertSort(multy, koeficijent, eksponent);
        }
    }

    return EXIT_SUCCESS;
}


int Delete(position p) {

    position temp = NULL;

    while (p != NULL) {
        temp = p->next;
        free(p);
        p = temp;
    }

    return EXIT_SUCCESS;
}
