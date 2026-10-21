
#include <stdio.h>
#include <stdlib.h>

#define MAX_BODOVA 30

typedef struct {
    char ime[50];
    char prezime[50];
    int br_bodova;
} Student;

int main(void) {
    FILE *dat;
    Student *studenti;
    int n = 0;
    int i;

    /* Otvaranje datoteke */
    dat = fopen("studenti.txt", "r");

    if (dat == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        return 1;
    }

    /* Brojanje redaka u datoteci */
    char redak[200];

    while (fgets(redak, sizeof(redak), dat) != NULL) {
        n++;
    }

    /* Vracanje na pocetak datoteke */
    rewind(dat);

    /* Dinamicka alokacija memorije */
    studenti = malloc(n * sizeof(Student));

    if (studenti == NULL && n > 0) {
        printf("Greska pri alokaciji memorije!\n");
        fclose(dat);
        return 1;
    }

    /* Ucitavanje podataka o studentima */
    for (i = 0; i < n; i++) {
        if (fscanf(dat, "%49s %49s %d",
                   studenti[i].ime,
                   studenti[i].prezime,
                   &studenti[i].br_bodova) != 3) {
            printf("Greska pri citanju podataka!\n");
            free(studenti);
            fclose(dat);
            return 1;
        }
    }

    fclose(dat);

    /* Ispis rezultata */
    printf("%-15s %-15s %-15s %-20s\n",
           "Ime", "Prezime", "Broj bodova",
           "Relativni bodovi (%)");

    for (i = 0; i < n; i++) {
        double relativni_bodovi =
            (double)studenti[i].br_bodova / MAX_BODOVA * 100;

        printf("%-15s %-15s %-15d %-20.2f\n",
               studenti[i].ime,
               studenti[i].prezime,
               studenti[i].br_bodova,
               relativni_bodovi);
    }

    /* Oslobadanje dinamicki alocirane memorije */
    free(studenti);

    return 0;
}
