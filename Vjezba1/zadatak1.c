
#include <stdio.h>
#include <stdlib.h>

#define MAX_DULJINA 50
#define MAX_BODOVA 100.0f

typedef struct {
    char ime[MAX_DULJINA];
    char prezime[MAX_DULJINA];
    int bodovi;
} Student;

int main(void) {
    FILE *datoteka;
    Student *studenti;
    int broj_studenata = 0;
    int i;
    char redak[200];

    datoteka = fopen("studenti.txt", "r");

    if (datoteka == NULL) {
        printf("Greska pri otvaranju datoteke.\n");
        return 1;
    }

    /* Brojanje redaka u datoteci */
    while (fgets(redak, sizeof(redak), datoteka) != NULL) {
        broj_studenata++;
    }

    rewind(datoteka);

    studenti = malloc(broj_studenata * sizeof(Student));

    if (studenti == NULL && broj_studenata > 0) {
        printf("Greska pri alokaciji memorije.\n");
        fclose(datoteka);
        return 1;
    }

    /* Ucitavanje podataka o studentima */
    for (i = 0; i < broj_studenata; i++) {
        if (fscanf(datoteka, "%49s %49s %d",
                   studenti[i].ime,
                   studenti[i].prezime,
                   &studenti[i].bodovi) != 3) {
            printf("Greska pri ucitavanju podataka.\n");
            free(studenti);
            fclose(datoteka);
            return 1;
        }
    }

    fclose(datoteka);

    /* Ispis rezultata */
    printf("%-15s %-15s %10s %15s\n",
           "Ime", "Prezime", "Bodovi", "Relativni bodovi");

    for (i = 0; i < broj_studenata; i++) {
        float relativni_bodovi =
            studenti[i].bodovi / MAX_BODOVA * 100.0f;

        printf("%-15s %-15s %10d %14.2f%%\n",
               studenti[i].ime,
               studenti[i].prezime,
               studenti[i].bodovi,
               relativni_bodovi);
    }

    free(studenti);

    return 0;
}
