/* BĂNESCU Ema-Ioana - Grupa 311CB */
#include "func_arbore.h"
#include <stdlib.h>
#include <string.h>
coada_com* InitQ() { /* creez coada vida */
    coada_com* c;
    /* spatiu pentru descriptor coada */
    c = (coada_com*)malloc(sizeof(coada_com));
    if (!c) return NULL;
    /* nu exista spatiu -> "esec" */
    c->sf = NULL;
    c->inc = NULL;
    return c;
    /* intorc adresa descriptorului cozii */
}
void IntrQ(coada_com *c, Tree nod) {
    if (!c || !nod)
        return;

    cel_com *nou = (cel_com*)malloc(sizeof(cel_com));
    // Aloc memorie pentru o nouă celulă
    if (!nou) {
        return;
    }
    nou->nod = nod;  // Setez nodul în noua celulă
    nou->urm = NULL;
    nou->pre = c->sf;
    if (!c->inc) {
        // Dacă coada este goală, setez noul nod
        // ca început și sfârșit al cozii
        c->inc = nou;
        c->sf = nou;
    } else {
        // Altfel, adaug noul nod la sfârșitul cozii
        // și actualizez sfârșitul cozii
        c->sf->urm = nou;
        c->sf = nou;
    }
}

Tree ExtrQ(coada_com *c) {
    if (!c || !c->inc)
        return NULL;

    cel_com *temp = c->inc;
    // Păstrez adresa primei celule
    Tree nod = temp->nod;
    // Extrag nodul din prima celulă
    c->inc = c->inc->urm;
    // Pun începutul cozii către următoarea celulă

    if (c->inc) {
        // Dacă există o următoare celulă,
        // setez nodul anterior al acesteia ca NULL
        c->inc->pre = NULL;
    } else {
        // Dacă nu există o următoare celulă,
        // actualizez și sfârșitul cozii ca NULL
        c->sf = NULL;
    }

    free(temp);  // Eliberez memoria alocată pentru prima celulă

    return nod;  // Returnez nodul extras din coadă
}
void elibereaza_coada(coada_com* c) {
    if (c == NULL) return;
    cel_com* current = c->inc;
    cel_com* next;
    while (current != NULL) {
        next = current->urm;
        free(current);
        current = next;
    }
    free(c);
}
// partea de coada s-a incheiat aici.........

Tree AlocaNod(char *info) {
    int i;
    Tree nod = (Tree)malloc(sizeof(Node));
    if (!nod) {
        return NULL;
    }
    // setez copii la NULL.
    for (i = 0; i < 27; i++) {
        nod->children[i] = NULL;
    }
    // Alocare și copiez in info, informatia
    nod->info = strdup(info);
    if (!nod->info) {
        free(nod);
        return NULL;
    }
    // Setez adancimea (pe ce nivel se afla arborele)
    nod->deep = 0;
    return nod;
}
int transforma_ascii_poz(char c) {
    if ('a' <= c && c <= 'z') {
        return c - 'a' + 1;
        // aici va returna 1 pentru a, 2
        // pt b etc etc...26 pt z.
    } else if (c == '$') {
        return 0;
    }
    return 0;
}
void insereaza(Tree arbore, char *sir) {
    int n = strlen(sir);
    int i, j;
    for (i = 0; i < n; i++) {
        /* pentru banana$, voi parcurge
        b a n a n a $
        a n a n a $
        n a n a $
        a n a $
        n a $
        a $
        $
        */
        Tree curr = arbore;
        int deep = 0;
        // fixez un pointer la nodul radacina al arborelui.
        for (j = i; j < n; j++) {
            char c = sir[j];
            int poz = transforma_ascii_poz(c);
            // verific daca acest nod a mai fost deja alocat,
            // inserat, pe nivelul curent
            if (!curr->children[poz]) {
                char sir[2];
                sir[0] = c;
                sir[1] = '\0';
                curr->children[poz] = AlocaNod(sir);
                curr->children[poz]->deep = deep + 1;
            // in caz ca nu, il il inserez pe pozitia corespunzatoare
            // functiei de transformare.
            }
            // altfel, imi mut pointerul, la nodul respectiv,
            // care deja exista pe nivelul
            // curent, si apoi continui sa iterez prin sir.
            curr = curr->children[poz];
            deep++;
            // incrementez nivelul pe care se afla.
        }
    }
}

void parcurgere_latime(Tree arbore, FILE* output) {
    if (arbore == NULL)
        return;

    coada_com *c = InitQ();
    IntrQ(c, arbore);  // Adaug rădăcina arborelui în coadă
    Tree indicator_nivel = AlocaNod("*");
    IntrQ(c, indicator_nivel);  // Adaug nodul special în coadă
    int prim_niv = 0;
    while (c->inc != NULL) {
        Tree nod_curent = ExtrQ(c);
        // afisarea vreau sa se faca cu un enter dupa fiecare
        // nivel, astfel ca am inclus in coada acel nod suplimentar
        // pe care l-am initializat cu *, o valoare random care nu va
        // aparea niciodata in arbore si cand voi ajunge sa o extrag,
        // voi afisa new-line, si apoi o introuc la loc in coada, daca coada
        // nu este inca goala.
        if (nod_curent == indicator_nivel) {
            // Dacă nodul extras este nodul special de sfârșit de nivel
            if (prim_niv != 0) {
                fprintf(output, "\n");
                // trec la un rand nou, dar contorul prim_niv
                // ma ajuta sa nu pun new-line la inceputul fisierului
                // imediat dupa ce am alocat primul indicator de nivel.
            }
            prim_niv++;
            if (c->inc != NULL) {
                IntrQ(c, indicator_nivel);
            // Adaug iar un nod special de sfârșit de nivel
            // în coadă (dacă există alte noduri in coada)
            }
        } else {
            // Adaug toți copiii nodului în coadă
            int i;
            for (i = 0; i < 27; i++) {
                if (nod_curent->children[i] != NULL) {
                    IntrQ(c, nod_curent->children[i]);
                }
            }
            if (strcmp(nod_curent->info, ".") != 0)
            fprintf(output, "%s ", nod_curent->info);
            // Afișez informația nodului
        }
    }
    elibereaza_coada(c);
    free(indicator_nivel->info);
    free(indicator_nivel);
}

int frunze(Tree arbore) {
    if (arbore == NULL) {
        return -1;
    }
    int i, ct = 0, ok = 0;
    for (i = 0; i <= 26; i++) {
        if (arbore->children[i] != NULL) {
            ok = 1;
            ct += frunze(arbore->children[i]);
        }
    }
    if (ok == 0) {
        ct = ct + 1;
        // inseamna ca am gasit un nod frunza.
    }
    return ct;
}

int nr_sufixe_k(Tree arbore, int k) {
    // am optat sa adaug in structura mea Tree, si numarul ce reprezinta
    // nr. nivelului pe care se afla fiecare nod in parte
    // iar aceasta atribuire am realizat-o in cadrul functiei de inserare,
    // pe masura ce inseram cate un caracter in arborele meu.
    if (arbore == NULL) {
        return 1;
    }
    // daca am ajuns la terminator si deep-ul
    // nodului cu dolar coincide cu lungimea sufixului, k
    // plus 1
    if (arbore->info[0] == '$' && arbore->deep == k + 1) {
        return 1;
    }
    int nr = 0, i;
    for (i = 0; i <= 26; i++) {
        if (arbore->children[i] != NULL) {
            nr += nr_sufixe_k(arbore->children[i], k);
        }
    }
    return nr;
}
int nr_max_descendenti(Tree arbore) {
    if (arbore == NULL) {
        return 0;
    }
    int numar_maxim = 0;
    int i;
    for (i = 0; i < 27; i++) {
        if (arbore->children[i] != NULL) {
            numar_maxim++;
        }
    }
    return numar_maxim;
}
int cauta_sufix(Tree arbore, char *sufix) {
    if (*sufix == '\0') {
        if ( arbore->children[0] != NULL && arbore->children[0]->info[0] == '$')
        // am pus conditia ca copilul de pe poz 0 sa fie si diferit de NULL
        // pentru ca daca eu ma opream in mijlocul unei ,,cai"
        // era foarte probabil ca copii nodului precedent sa aiba doar o litera
        // sau mai multe, nu si dolar.
        return 1;
        // am ajuns la sfârșitul sufixului, deci l-am găsit în arbore
    }
    int poz = transforma_ascii_poz(*sufix);
    // imi permit sa folosesc acest indice, poz, pentru ca stiu de la inceput
    // ca in arbore ca fiecare copil al unui nod este amplasat NEAPARAT
    // in ordine alfabetica !
    if (arbore->children[poz] != NULL &&
    arbore->children[poz]->info[0] == *(sufix)) {
        return cauta_sufix(arbore->children[poz], sufix + 1);
    }
    return 0;
    // astfel, nu am mai iterat prin toti copii,
    // cu for de la 0 la 26, ci m-a interesat doar copilul cu informatia
    // de pe pozitia asociata din sirul sufix.
}
Tree compactare_arbore(Tree arbore) {
    if (arbore == NULL) {
        return NULL;
    }
    int i;
    for (i = 0; i < 27; i++) {
        arbore->children[i] = compactare_arbore(arbore->children[i]);
    }

    int nr_copii = 0, poz_copil = -1;
    char info_copil[100];
    for (i = 0; i < 27; i++) {
        if (arbore->children[i] != NULL) {
            nr_copii++;
            poz_copil = i;
            strcpy(info_copil, arbore->children[i]->info);
        }
    }

    if (nr_copii == 1 && info_copil[0] != '$') {
        // doar daca nodul curent are un copil
        // si nu coincide cu terminatorul dolar.
        Tree copil = arbore->children[poz_copil];
        // memorez in copil subarborele pornind de la copil.
        int lung_info_arb = strlen(arbore->info);
        int lung_info_copil = strlen(info_copil);
        int lung_info_noua = lung_info_arb + lung_info_copil + 1;
        char *info_combinat = (char *)malloc(lung_info_noua * sizeof(char));
        strcpy(info_combinat, arbore->info);
        strcat(info_combinat, copil->info);
        // am format informatia unificata.

        Tree nod_nou = AlocaNod(info_combinat);
        nod_nou->deep = copil->deep - 1;
        free(info_combinat);
        // dezaloc memoria pentru sirul info_combinat,
        // ca deja am un nod alocat cu informatia care imi trebuie.
        int i;
        for (i = 0; i < 27; i++) {
            nod_nou->children[i] = copil->children[i];
        }
        if (copil->info != NULL) {
            free(copil->info);
        }
        if (copil != NULL) {
            free(copil);
        }

        if (arbore->info != NULL) {
            free(arbore->info);
        }
        if (arbore != NULL) {
            free(arbore);
        }

        return nod_nou;
    }

    return arbore;
}

void elibereaza_arbore(Tree arbore) {
    if (arbore == NULL) {
        return;
    }
    int i;
    for (i = 0; i < 27; i++) {
        elibereaza_arbore(arbore->children[i]);
    }
    free(arbore->info);
    free(arbore);
}
