/* BĂNESCU Ema-Ioana - Grupa 311CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func_arbore.h"
void formare_arbore(Tree arbore, FILE *input, int N) {
    int i, j;
    for (i = 0; i < N; i++) {
        char cuv[101];
        fgets(cuv, 101, input);  // stim sigur ca e doar un cuv pe linie.
        for (j = 0; j < (int)strlen(cuv); j++) {
            if (cuv[j] == '\n') {
                cuv[j] = '\0';
                break;
            }
        }
        strcat(cuv, "$");
        insereaza(arbore, cuv);
    }
}
void task1(Tree arbore, FILE* input, FILE* output) {
    int N;
    fscanf(input, "%d", &N);
    fgetc(input);  // Consum newline-ul
    formare_arbore(arbore, input, N);
    parcurgere_latime(arbore, output);
    elibereaza_arbore(arbore);
}

void task2(Tree arbore, int K, FILE* input, FILE* output) {
    int N;
    fscanf(input, "%d", &N);
    fgetc(input);
    formare_arbore(arbore, input, N);
    fprintf(output, "%d\n", frunze(arbore));
    fprintf(output, "%d\n", nr_sufixe_k(arbore, K));
    fprintf(output, "%d\n", nr_max_descendenti(arbore));
    elibereaza_arbore(arbore);
}
void task3(Tree arbore, FILE* input, FILE* output) {
    int N, M, i, j;
    fscanf(input, "%d", &N);
    fscanf(input, "%d", &M);
    fgetc(input);
    formare_arbore(arbore, input, N);
    for (i = 0; i < M; i++) {
        char sufix[100];
        fgets(sufix, 100, input);
        for (j = 0; j < (int)strlen(sufix); j++) {
            if (sufix[j] == '\n') {
                sufix[j] = '\0';
                break;
            }
        }
        fprintf(output, "%d\n", cauta_sufix(arbore, sufix));
    }
    elibereaza_arbore(arbore);
}

void task4(Tree arbore, FILE* input, FILE* output) {
    int N;
    fscanf(input, "%d", &N);
    fgetc(input);  // Consum newline-ul
    formare_arbore(arbore, input, N);
    compactare_arbore(arbore);
    parcurgere_latime(arbore, output);
    elibereaza_arbore(arbore);
}

int main(int argc, char* argv[]) {
    char* nume_fisier_intrare;
    char* nume_fisier_iesire;
    char* flag;
    int k;
    // preiau din lista de argumente, in functie de numarul lor 4/5
    flag = argv[1];
    if (argc == 4) {
        nume_fisier_intrare = argv[2];
        nume_fisier_iesire = argv[3];
    } else if (argc == 5) {
        k = atoi(argv[2]);
        nume_fisier_intrare = argv[3];
        nume_fisier_iesire = argv[4];
    }
    // Mi am selectat in variabilele de mai sus argumentele pe diferite pozitii
    // dupa caz (task 1 + 3 + 4), (task 2, unde intervine
    // pe pozitia 2, cifra K).
    // Deschid fisierele.
    FILE* input = fopen(nume_fisier_intrare, "r");
    if (!input) {
        printf("Eroare la deschidere!\n");
        return 1;
    }

    FILE* output = fopen(nume_fisier_iesire, "w");
    if (!output) {
        printf("Eroare la deschidere!\n");
        fclose(input);
        return 1;
    }

    Tree arbore = AlocaNod(".");  // Inițializarea arborelui de sufixe
    if (strcmp(flag, "-c1") == 0) {
        task1(arbore, input, output);
    } else if (strcmp(flag, "-c2") == 0) {
        task2(arbore, k, input, output);
    } else if (strcmp(flag, "-c3") == 0) {
        task3(arbore, input, output);
    } else if (strcmp(flag, "-c4") == 0) {
        task4(arbore, input, output);
    }
    fclose(input);
    fclose(output);
    return 0;
}
