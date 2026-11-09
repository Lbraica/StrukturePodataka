
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 100

// Napisati program koji cita postfiks izraz i zatim koristenjem stoga
// racuna rezultat. Stog je potrebno realizirati preko vezane liste.

struct _postfiks;
typedef struct _postfiks* Pozicija;

typedef struct _postfiks
{
    float broj;
    Pozicija next;
} postfiks;

int mnozi(Pozicija P);
int dijeli(Pozicija P);
int zbroji(Pozicija P);
int oduzmi(Pozicija P);

int unos(float broj, Pozicija P);
int brisi_sve(Pozicija P);
int ispisi_listu(Pozicija P);
Pozicija trazi_prethodni(Pozicija P, Pozicija trazeni);
int operacija(Pozicija P, char znak);


int main()
{
    char ime_datoteke[MAX_LINE] = { '\0' };
    char buffer[MAX_LINE] = { '\0' };
    char* kraj = NULL;

    FILE* f = NULL;

    float broj = 0;
    int provjera = 0;
    int br_clanova = 0;
    int status = 0;

    Pozicija head = NULL;

    head = (Pozicija)malloc(sizeof(postfiks));

    if (head == NULL)
    {
        printf("Greska pri inicijalizaciji memorije\n");
        return -1;
    }

    head->next = NULL;

    printf("Unesite ime datoteke: ");

    provjera = scanf("%99s", ime_datoteke);

    if (provjera != 1)
    {
        printf("Krivi unos\n");
        brisi_sve(head);
        return -1;
    }

    f = fopen(ime_datoteke, "r");

    if (f == NULL)
    {
        printf("Datoteka se nije mogla otvoriti\n");
        brisi_sve(head);
        return -1;
    }

    while (fscanf(f, "%99s", buffer) == 1)
    {
        broj = strtof(buffer, &kraj);

        if (kraj != buffer && *kraj == '\0')
        {
            if (unos(broj, head) == -1)
            {
                status = -1;
                goto kraj;
            }

            br_clanova++;
        }
        else if (strlen(buffer) == 1)
        {
            if (br_clanova < 2)
            {
                printf("Krivi izraz\n");
                status = -1;
                goto kraj;
            }

            if (operacija(head, buffer[0]) == -1)
            {
                status = -1;
                goto kraj;
            }

            br_clanova--;
        }
        else
        {
            printf("Nepoznat znak ili neispravan broj: %s\n", buffer);
            status = -1;
            goto kraj;
        }
    }

    if (ferror(f))
    {
        printf("Greska pri citanju datoteke\n");
        status = -1;
        goto kraj;
    }

    if (br_clanova != 1)
    {
        printf("Krivi izraz\n");
        status = -1;
        goto kraj;
    }

    printf("\nRezultat:\n");
    ispisi_listu(head->next);

kraj:

    fclose(f);
    brisi_sve(head);

    return status;
}


int unos(float broj, Pozicija P)
{
    Pozicija q;

    while (P->next != NULL)
    {
        P = P->next;
    }

    q = (Pozicija)malloc(sizeof(postfiks));

    if (q == NULL)
    {
        printf("Greska pri alokaciji memorije\n");
        return -1;
    }

    q->broj = broj;
    q->next = NULL;
    P->next = q;

    return 0;
}


Pozicija trazi_prethodni(Pozicija P, Pozicija trazeni)
{
    while (P->next != NULL && P->next != trazeni)
    {
        P = P->next;
    }

    return P;
}


int operacija(Pozicija P, char znak)
{
    switch (znak)
    {
    case '+':
        return zbroji(P);

    case '-':
        return oduzmi(P);

    case '*':
        return mnozi(P);

    case '/':
        return dijeli(P);

    default:
        printf("Nepoznat znak\n");
        return -1;
    }
}


int mnozi(Pozicija P)
{
    Pozicija zadnji = P;
    Pozicija prethodni = NULL;
    Pozicija prije_drugog = NULL;

    float broj = 0;

    while (zadnji->next != NULL)
    {
        prethodni = zadnji;
        zadnji = zadnji->next;
    }

    prije_drugog = trazi_prethodni(P, prethodni);

    broj = prethodni->broj * zadnji->broj;

    prije_drugog->next = NULL;

    free(zadnji);
    free(prethodni);

    return unos(broj, P);
}


int dijeli(Pozicija P)
{
    Pozicija zadnji = P;
    Pozicija prethodni = NULL;
    Pozicija prije_drugog = NULL;

    float broj = 0;

    while (zadnji->next != NULL)
    {
        prethodni = zadnji;
        zadnji = zadnji->next;
    }

    if (zadnji->broj == 0)
    {
        printf("Greska, dijeljenje s 0\n");
        return -1;
    }

    prije_drugog = trazi_prethodni(P, prethodni);

    broj = prethodni->broj / zadnji->broj;

    prije_drugog->next = NULL;

    free(zadnji);
    free(prethodni);

    return unos(broj, P);
}


int zbroji(Pozicija P)
{
    Pozicija zadnji = P;
    Pozicija prethodni = NULL;
    Pozicija prije_drugog = NULL;

    float broj = 0;

    while (zadnji->next != NULL)
    {
        prethodni = zadnji;
        zadnji = zadnji->next;
    }

    prije_drugog = trazi_prethodni(P, prethodni);

    broj = prethodni->broj + zadnji->broj;

    prije_drugog->next = NULL;

    free(zadnji);
    free(prethodni);

    return unos(broj, P);
}


int oduzmi(Pozicija P)
{
    Pozicija zadnji = P;
    Pozicija prethodni = NULL;
    Pozicija prije_drugog = NULL;

    float broj = 0;

    while (zadnji->next != NULL)
    {
        prethodni = zadnji;
        zadnji = zadnji->next;
    }

    prije_drugog = trazi_prethodni(P, prethodni);

    broj = prethodni->broj - zadnji->broj;

    prije_drugog->next = NULL;

    free(zadnji);
    free(prethodni);

    return unos(broj, P);
}


int ispisi_listu(Pozicija P)
{
    while (P != NULL)
    {
        printf("REZULTAT: %f\n", P->broj);
        P = P->next;
    }

    return 0;
}


int brisi_sve(Pozicija P)
{
    Pozicija temp = NULL;

    while (P != NULL)
    {
        temp = P;
        P = P->next;
        free(temp);
    }

    return 0;
}
