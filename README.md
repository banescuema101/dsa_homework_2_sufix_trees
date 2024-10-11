## Descrierea functiilor

Primele 4 functii, InitQ, IntrQ si ExtrQ si elibereaza_coada, sunt preluate ca si idee din tema 1, intrucat voi avea nevoie de ele
la partea de parcurgere in latime a arborelui. Sa trecem la partea de arbori din cadrul temei.

# 1. Functia AlocaNod
Aloc memorie pentru un nod din arbore si initializez toate campurile structurii. Cei 27 posibili copii ii voi
seta la NULL, voi copia sirul alocat dinamic transmis ca parametru si voi seta adnacimea pe nivel(deep) la zero. Aceasta imi va 
arata ulterior pe ce nivel se afla un anumit nod in arbore ( de la 0 la numarul de niveluri - 1).

# 2. ransforma_ascii_poz(char c)
Returnez pozitia pe care trebuie amplasat un anumit copil in arbore. Tin cont de cerinta,
astfel ca daca vreau sa introduc un nod cu informatia dolar, il voi pune pe pozitia 0, si daca vreau cu o litera a alfabetului o voi pune
pe pozitia litera_curenta - 'a' + 1, decalata cu unu pentru ca pe zero am pus dolarul.

# 3. In functia insereaza(Tree arbore, char *sir)
In aceasta functie imi propun sa inserez sufixele unui anumit sir in arbore. Parcurg sufixele ca
in exemplul expus in comentariul aferent, cu ajutorul a doua foruri. La fiecare pas al celui de-al doilea for, extrag caracterul c
din sirul de la indicele j, apoi calculez cu ajutorul functiei transforma_ascii_poz pozitia pe care ar trebui sa pun nodul, dar verific imediat
daca exista caracterul c la pozitia poz in vectorul de copii, deja inserat. Daca nu exista, creez un nou nod cu informatia c, actualizez adancimea
deep. Deplasez pointerul curr pe noul nod creat sau pe cel deja existent, in functie de existenta nodului la pozitia poz in arbore. Actualizez si
contorul deep, pt adancimea curenta a inserarii in arbore. Repet aceste proceduri pt fiecare caracter din sirul sir.

# 4. Functia parcurgere_latime
Vreau sa parcurg arborele in latime si sa afisez nodurile parcurgandu-l, in fisierul de output
transmis ca parametru. Prima data initializez coada, introduc in aceasta radacina arborelui(pe care nu vreau sa o afisez), apoi aloc
un indicator de nivel, cu o informatie care stiu sigur ca nu are cum sa existe in arbore si o introduc si pe aceasta in arbore.
Rolul acestui indicator de nivel este sa pot contoriza cand termin cu parcurgerea unui nivel, pentru a putea stii in ce moment afisez
caracterul new-line in fisier. Cat timp coada nu este goala, extrag din ea, apoi vad in ce fel afisez (nod sau new_line), dar 
tin cont sa nu afisez new_line de la nivelul pe care se afla radacina, ca dupa as printa un new-line la inceput, in plus si nu trebuie. 
De fiecare data adaug in coada toti copii nodului curent extras apoi cat timp coada nu goala tot extrag din ea si repet operatiile pana 
cand devine vida. La final, foarte important, distrug coada cu functia elibereaza_coada si eliberez memoria.

# 5. Functia recursiva frunze(Tree arbore)
Prima data verific daca arborele este vid, apoi daca nu e, initializez contorul ct, cu rol
de numarare a frunzelor. Parcurg copii din vectorul children ai arborelui radacina (la prima intrare in functie), apoi cu un for parcurg copii
nodului curent, si pentru fiecare copil nenul, care exista in arbore, apelez functia, recursiv, iar daca toti copii sunt NULI,
adica nodul acela nu are niciun copil, inseamna ca el e o frunza, deci cresc contorul ct.

# 6. Functia nr_max_sufixe
Parcurg, similar, fiecare copil nenul al nodului, intr un mod recursiv si merg pe ideea ca, pe masura ce este
apelata functia recursiv, se gaseste un nod cu informatia dolar, adica terminatorul de sufix din arbore si adancimea pe care se afla acel dolar
este egala cu k + 1 (k fiind lungimea sirului dorita, transmis ca parametru), atunci se returneaza 1, adica s-a gasit un sufix de lungime k.

# 7. Functia nr_max_descendenti
Parcurg fiecare copil din vectorul de copii ai unui nod dat si numar cati dintre ei sunt nenului, adica
exista si sunt stocati deja in acel vector, la final returnand acest numar, adica cati descendenti directi are un anumit nod.

# 8. Functia cauta_sufix
Am inceput prin a returna 1, semn ca am gasit sufixul pe care il cautam, in arbore, daca si numai daca
copilul de pe pozitia 0 al nodului curent exista si e semnat cu informatia dolar. In poz am memorat rezultatul functiei transforma_ascii,
care imi dadea pozitia pe care s-ar fi gasit un anumit caracter in vectorul de copii, si daca acel copil de pe respectiva pozitie
coincidea cu primul caracter al sufixului transmis ca parametru (am comparat info[0], pentru ca eu prin definitie am definit info ca 
fiind un sir in structura, dar stu ca in aceasta etapa eu am doar caractere in arborele meu). Daca coincidea, apelam
recursiv cauta_sufix pentru acel copil cu sirul sufix deplasat cu o pozitie(sufix + 1).

# 9. Functia compactare_arbore
Initial verific daca arborele este NULL si astfel, returnez NULL. Daca nu, apelez recursiv
functia pe fiecare copil al arborelui. Apoi, parcurgand prin vectorul de copii, am vrut sa aflu daca nodul curent la care
puncteaza arborele are doar un copil, si am memorat si pozitia acelui copil pe nivel, cat si informatia din el. Daca intr-adevar gaseam
un unic copil, dar cu conditia sa nu aiba in campul info dolar(terminatorul): Initializam un pointer copil, care indica spre copilul
nodului curent si unificam informatiile din cele doua noduri (parinte + copil). Am alocat un nou nod, nod_nou, care are setat ca si info,
informatia unificata. I am setat si deep-ul (cu toate ca nu ma interesa..). Foarte important, noului nod alocat, i am setat copii ca fiind
copii aferenti nodului la care indica pointerul copil. La final, eliberez memoria pentru nodul si pentru copilul vecho si returnez pointerul
de tip Tree la noul nod format sau arborele initial, daca nu a fost facuta nicio compactare.

# 10. Functia elibereaza_arbore
Elibereaza memoria pentru sirul info, pentru fiecare copil in parte si pentru arbore, pointer la structura
Node, la randul lui.

## Descrierea programului principal
#
Programul, conform cerintei, trebuie sa primeasca argumente din linia de comandă și în funcție de acestea, sa rezolve taskul 1, 2, 3 sau 4.
De aceea functia main, are ca parametrii, numarul de argumente si lista de argumente. Initial, verific numarul de argumente.
Daca sunt 4, inseamna ca mi se cere sa rezolv taskul 1, 3 sau 4, iar daca sunt 5, cu siguranta taskul 2, unde mai apare argumentul
K, care trebuie sa fie cifra, astfel ca ii aplic functia atoi, cu ajutorul careia pot converti argumentul. Tocmai ca apar aceste diferente
date de K, numele fisierelor se gasesc la pozitii diferite in lista de argumente, in functie de numarul lor.
Daca sunt 4, fisierele de intrare/iesire sunt pe pozitia 2/3 iar daca sunt 5 argumente, fisierul de intrare/iesire se gaseste pe pozitia
3/4, pentru ca pe 2 se gaseste K-ul.
    Apoi deschid fisierele de intrare./iesire si verific daca deshiderea s-a realizat cu succes si aloc nodul cu informatia ., care
va reprezenta radacina arborelui cu care voi lucra in functiile task1,2,3,4.
    In functia de ,,flagul" ( -c1, -c2, -c3, -c4), de pe pozitia 1 in lista de argumente, apelez functiile corespunzatoare fiecarui task
si la final inchid fisierele de intrare si de iesire.

->    In functia formare_arbore, vreau sa inserez N cuvinte, citite din fisierul de input, cu fgets, pentru ca stiu ca sunt
    fiecare pe o linie, si sunt formate, evident din mai multe caractere, am grija sa elimin new-line-urile puse de fgets,
    si apoi concatenez simbolul dolar la finalul cuvintelor citite si le inserez, cu ajutorul functiei de inserare.
    
->    In functia task1, am citit din fisierul de input nr de cuvinte pe care vreau sa le inserez, N, cu fgetc ( ca citesc doar un
    caracter), formez arborele cu functia de formare si apoi aplic functia de compactare, parcurgere si eliberez memoria arborelui.
->    In functia task2, am citit N, am format arborele si apoi am scris in fisierul de output rezultatele returnate de functiile
    frunze, nr_sufixe_k si nr_max_descendenti si la final eliberez memoria.
->    In functia task3, am citit N, dar si M, numarul de sufixe pe care vreau sa le caut, cu un for, si la fiecare pas, aplic functia
de cautare, cauta_sufix pentru fiecare dintre cele M cuvinte si la final eliberez memoria.
->    In functia task4, citesc N sin fisierul de input, apoi formez arborele, il compactez, il parcurg in latime si apoi eliberez memoria.

