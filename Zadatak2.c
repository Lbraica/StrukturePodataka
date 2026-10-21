
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Osoba {
    char ime[50];
    char prezime[50];
    int godina_rodjenja;
    struct Osoba *sljedeci;
} Osoba;

/* Unos podataka o osobi */
void unos(Osoba *nova) {
    printf("Unesite ime: ");
    scanf("%49s", nova->ime);

    printf("Unesite prezime: ");
    scanf("%49s", nova->prezime);

    printf("Unesite godinu rodenja: ");
    scanf("%d", &nova->godina_rodjenja);
}

/* A. Dodavanje na pocetak liste */
Osoba *dodaj_na_pocetak(Osoba *lista) {
    Osoba *nova = malloc(sizeof(Osoba));

    if (nova == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return lista;
    }

    unos(nova);
    nova->sljedeci = lista;

    return nova;
}

/* B. Ispis liste */
void ispisi_listu(Osoba *lista) {
    Osoba *tek = lista;

    if (tek == NULL) {
        printf("Lista je prazna.\n");
        return;
    }

    while (tek != NULL) {
        printf("Ime: %s, Prezime: %s, Godina rodenja: %d\n",
               tek->ime,
               tek->prezime,
               tek->godina_rodjenja);

        tek = tek->sljedeci;
    }
}

/* C. Dodavanje na kraj liste */
Osoba *dodaj_na_kraj(Osoba *lista) {
    Osoba *nova = malloc(sizeof(Osoba));
    Osoba *tek;

    if (nova == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return lista;
    }

    unos(nova);
    nova->sljedeci = NULL;

    if (lista == NULL) {
        return nova;
    }

    tek = lista;

    while (tek->sljedeci != NULL) {
        tek = tek->sljedeci;
    }

    tek->sljedeci = nova;

    return lista;
}

/* D. Pronalaženje osobe po prezimenu */
Osoba *pronadji(Osoba *lista, const char *prezime) {
    Osoba *tek = lista;

    while (tek != NULL) {
        if (strcmp(tek->prezime, prezime) == 0) {
            return tek;
        }

        tek = tek->sljedeci;
    }

    return NULL;
}

/* E. Brisanje osobe po prezimenu */
Osoba *obrisi(Osoba *lista, const char *prezime) {
    Osoba *tek = lista;
    Osoba *prethodni = NULL;

    while (tek != NULL &&
           strcmp(tek->prezime, prezime) != 0) {
        prethodni = tek;
        tek = tek->sljedeci;
    }

    if (tek == NULL) {
        printf("Osoba nije pronadena.\n");
        return lista;
    }

    if (prethodni == NULL) {
        lista = tek->sljedeci;
    } else {
        prethodni->sljedeci = tek->sljedeci;
    }

    free(tek);
    printf("Osoba je uspjesno obrisana.\n");

    return lista;
}

/* Oslobađanje cijele liste */
void oslobodi_listu(Osoba *lista) {
    Osoba *tek;

    while (lista != NULL) {
        tek = lista;
        lista = lista->sljedeci;
        free(tek);
    }
}

int main(void) {
    Osoba *lista = NULL;
    Osoba *pronadjena;
    char prezime[50];
    int izbor;

    do {
        printf("\n--- IZBORNIK ---\n");
        printf("1. Dodaj osobu na pocetak\n");
        printf("2. Ispisi listu\n");
        printf("3. Dodaj osobu na kraj\n");
        printf("4. Pronadi osobu po prezimenu\n");
        printf("5. Obrisi osobu po prezimenu\n");
        printf("0. Izlaz\n");
        printf("Izbor: ");
        scanf("%d", &izbor);

        switch (izbor) {
            case 1:
                lista = dodaj_na_pocetak(lista);
                break;

            case 2:
                ispisi_listu(lista);
                break;

            case 3:
                lista = dodaj_na_kraj(lista);
                break;

            case 4:
                printf("Unesite prezime za pretragu: ");
                scanf("%49s", prezime);

                pronadjena = pronadji(lista, prezime);

                if (pronadjena != NULL) {
                    printf("Pronadena osoba: %s %s, %d\n",
                           pronadjena->ime,
                           pronadjena->prezime,
                           pronadjena->godina_rodjenja);
                } else {
                    printf("Osoba nije pronadena.\n");
                }
                break;

            case 5:
                printf("Unesite prezime za brisanje: ");
                scanf("%49s", prezime);

                lista = obrisi(lista, prezime);
                break;

            case 0:
                printf("Kraj programa.\n");
                break;

            default:
                printf("Neispravan izbor!\n");
        }

    } while (izbor != 0);

    oslobodi_listu(lista);

    return 0;
}
