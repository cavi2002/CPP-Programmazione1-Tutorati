#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

// Anche se c'è questa costante che limita la dimensione degli array,
// è fatta solo per evitare di far girare i vostri programmi per decine
// di minuti. Non programmate con dimensioni fisse, per favore.
const int UPPER_BOUND_DIM = 10;
const int UPPER_BOUND_VAL = 50;

struct nodo {
    float valore;
    nodo *pred;
    nodo *succ;
};

typedef nodo *lista;

float randVal();
lista generaLista();
void stampaLista(lista nodoCorrente);
nodo *creaNodo(float cartaDaInserire);

// ------------------------
// Inserire qui le dichiarazioni delle funzioni richieste
// ------------------------

lista unisciListe(lista nodoCorrente1, lista nodoCorrente2);
float scorriLista(lista nodoCorrente);
void deallocaLista(lista nodoCorrente);

// IMPORTANTE. Non modificare il main.
int main() {
    srand(time(NULL));

    lista lista1 = generaLista();
    lista lista2 = generaLista();

    cout << "Lista 1: ";
    stampaLista(lista1);
    cout << endl;

    cout << "Lista 2: ";
    stampaLista(lista2);
    cout << endl;

    lista listaUnita = unisciListe(lista1, lista2);

    cout << "Liste unite: ";
    stampaLista(listaUnita);
    cout << endl;

    float somma = scorriLista(listaUnita);

    cout << "Liste filtrate: ";
    stampaLista(listaUnita);
    cout << endl;
    cout << "Somma degli elementi > 0: " << somma << endl;

    // E' compito della funzione scorriLista liberare
    // la memoria dei nodi intermedi! Non decommentare
    // queste righe, altrimenti verrà rseba a prendervi con l'ascia.
    deallocaLista(listaUnita);

    return 0;
}

// IMPORTANTE. Non modificare questa funzione.
nodo *creaNodo(float val) {
    nodo *n = new nodo;
    n->valore = val;
    n->pred = NULL;
    n->succ = NULL;
    return n;
}

// IMPORTANTE. Non modificare questa funzione.
float randVal() {
    float valore = (float)rand() / (float)(RAND_MAX / UPPER_BOUND_VAL);
    if (rand() % 2 == 0) {
        valore *= -1;
    }

    return valore;
}

// IMPORTANTE. Non modificare questa funzione.
nodo *generaLista() {
    int size = rand() % UPPER_BOUND_DIM;

    nodo *nodoIniziale = creaNodo(randVal());
    nodo *nodoPredecente = nodoIniziale;
    nodo *nodoCorrente = NULL;

    for (int i = 1; i < size; i++) {
        nodoCorrente = creaNodo(randVal());
        nodoPredecente->succ = nodoCorrente;
        nodoCorrente->pred = nodoPredecente;
        nodoPredecente = nodoCorrente;
    }

    return nodoIniziale;
}

// IMPORTANTE. Non modificare questa funzione.
void stampaLista(nodo *nn) {
    while (nn != NULL) {
        cout << nn->valore << " ";
        nn = nn->succ;
    }
    cout << endl;
}

// ------------------------
// Inserire qui le definizioni delle funzioni richieste
// ------------------------

lista unisciListe(lista nodoCorrente1, lista nodoCorrente2){
  nodo *nodoIniziale;
  nodo *nodoPrecedente;
  nodo *nodoCorrente;
  if(nodoCorrente1->pred!=NULL){
    cout << "Attenzione, puntatore lista 1 sbagliato" << endl;
    return NULL;
  }
  if(nodoCorrente2->pred!=NULL){
    cout << "Attenzione, puntatore lista 2 sbagliato" << endl;
  }
  if(nodoCorrente1==NULL){
    if(nodoCorrente2==NULL){
      nodoIniziale = NULL;
    }else{
      nodoIniziale = creaNodo(nodoCorrente2->valore);
      nodoPrecedente = nodoIniziale;
      nodoCorrente = NULL;
      nodo *nodoAppoggio2 = nodoCorrente2;
      nodoAppoggio2 = nodoAppoggio2->succ;
      while(nodoAppoggio2!=NULL){
	nodoCorrente = creaNodo(nodoAppoggio2->valore);
	nodoPrecedente->succ = nodoCorrente;
	nodoCorrente->pred = nodoPrecedente;
	nodoPrecedente = nodoCorrente;
	nodoAppoggio2 = nodoAppoggio2->succ;
      }
    }
  }else{
    nodoIniziale = creaNodo(nodoCorrente1->valore);
    nodoPrecedente = nodoIniziale;
    nodoCorrente = NULL;
    nodo *nodoAppoggio1 = nodoCorrente1;
    nodoAppoggio1 = nodoAppoggio1->succ;
    while(nodoAppoggio1!=NULL){
      nodoCorrente = creaNodo(nodoAppoggio1->valore);
      nodoPrecedente->succ = nodoCorrente;
      nodoCorrente->pred = nodoPrecedente;
      nodoPrecedente = nodoCorrente;
      nodoAppoggio1 = nodoAppoggio1->succ;
    }
    if(nodoCorrente2!=NULL){
      nodo *nodoAppoggio2 = nodoCorrente2;
      while(nodoAppoggio2!=NULL){
	nodoCorrente = creaNodo(nodoAppoggio2->valore);
	nodoPrecedente->succ = nodoCorrente;
	nodoCorrente->pred = nodoPrecedente;
	nodoPrecedente = nodoCorrente;
	nodoAppoggio2 = nodoAppoggio2->succ;
      }
    }
  }
  return nodoIniziale;
}

float scorriLista(lista nodoCorrente){
  float somma = 0;
  nodo * appoggio = nodoCorrente;
  while(appoggio->succ!=NULL){
    if(appoggio->valore>0){
      
      nodo * t = appoggio;
      
      somma += t->valore;
      t->succ->pred = t->pred;
      t->pred->succ = t->succ;
      
      appoggio = t->succ;
      delete t;
    }else{
      appoggio = appoggio->succ;
    }
  }
  return somma;
}

void deallocaLista(lista nodoCorrente){
  nodo * appoggio = nodoCorrente;
  while(appoggio!=NULL){
    nodo * t = appoggio;
    appoggio = appoggio->succ;
    delete t;
  }
}
