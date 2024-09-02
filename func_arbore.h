/* BĂNESCU Ema-Ioana - Grupa 311CB */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    char *info;
    int deep;  // pozitia pe care se afla in arbore, de sus, in jos.
    struct node *children[27];
} Node, *Tree;

typedef struct cel_com {
    Tree nod;  // Nodul stocat în celulă
    struct cel_com *urm;
    struct cel_com *pre;
} cel_com, *lista_com;

typedef struct coada_com {
    lista_com inc;
    lista_com sf;
} coada_com;

coada_com* InitQ();
void IntrQ(coada_com *c, Tree nod);
Tree ExtrQ(coada_com *c);
void elibereaza_coada(coada_com* c);
Tree AlocaNod(char *info);
int transforma_ascii_poz(char c);
void insereaza(Tree arbore, char *sufix);
void parcurgere_latime(Tree arbore, FILE* output);
int frunze(Tree arbore);
int nr_sufixe_k(Tree arbore, int k);
int nr_max_descendenti(Tree arbore);
int cauta_sufix(Tree arbore, char *sufix);
Tree compactare_arbore(Tree arbore);
void elibereaza_arbore(Tree arbore);
