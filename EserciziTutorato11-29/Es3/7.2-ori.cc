#include <iostream>
#include <cmath>
using namespace std;

struct persona {
   int codiceInvito;
   persona *primo;
   persona *secondo;
   persona *terzo;
};
typedef persona *piramide;

piramide generaPiramide(int numeroDiPersone = 20);

int calcolaGuadagno(piramide vertice, int quota, float commissioni = 0.2);

int altezzaPiramide(piramide vertice);

void deallocaPiramide(piramide vertice);

int main(int argc, char *argv[]) {

    piramide p = generaPiramide();

    cout << "Fuffox potrà guadagnare: " << calcolaGuadagno(p, 100) << "$" << endl;
    cout << "La piramide è alta: " << altezzaPiramide(p) << endl;

    deallocaPiramide(p);

    return 0;
}


piramide generaPiramide(int numeroDiPersone) {

    srand(time(NULL));
    persona *persone[numeroDiPersone];

    cout << "La piramide è composta da:";

    for (int i = 0; i < numeroDiPersone; i++) {
        persone[i] = new persona;
        persone[i]->codiceInvito = i;
        persone[i]->primo = NULL;
        persone[i]->secondo = NULL;
        persone[i]->terzo = NULL;
        cout << " " << persone[i]->codiceInvito;
    }
    cout << endl;

    for (int i = 0; (3 * i + 1) < numeroDiPersone; i++) {
        persone[i]->primo = persone[3 * i + 1];
        if ((3 * i + 2) < numeroDiPersone) {
            persone[i]->secondo = persone[(3 * i + 2)];
            if ((3 * i + 3) < numeroDiPersone) {
                persone[i]->terzo = persone[(3 * i + 3)];
            }
        }
    }

    return persone[0];
}

/*
 * Inserire qui la definizione di "calcolaGuadagno", "altezzaPiramide",
 * "deallocaPiramide" e di eventuali altre funzioni ausiliarie.
 */

int calcolaGuadagno(piramide vertice, int quota, float commissioni){
  int ritorno = 0;
  int quote_invito = 0;
  if(vertice!=NULL){
    int c1 = calcolaGuadagno(vertice->primo, quota);
    int c2 = calcolaGuadagno(vertice->secondo, quota);
    int c3 = calcolaGuadagno(vertice->terzo, quota);
    if(c1==0){
      quote_invito++;
    }
    if(c2==0){
      quote_invito++;
    }
    if(c3==0){
      quote_invito++;
    }
    ritorno = quota + (c1+c2+c3 - commissioni*quote_invito);
  }
  return ritorno;
}

int altezzaPiramide(piramide vertice){
  int ritorno = 0;
  if(vertice != NULL){
    int a1 = altezzaPiramide(vertice->primo);
    int a2 = altezzaPiramide(vertice->secondo);
    int a3 = altezzaPiramide(vertice->terzo);
    ritorno = max(a1, a2);
    ritorno = max(ritorno, a3);
  }
  return (1+ritorno);
}

void deallocaPiramide(piramide vertice){
  if((vertice!=NULL)){
    deallocaPiramide(vertice->primo);
    deallocaPiramide(vertice->secondo);
    deallocaPiramide(vertice->terzo);
  }
  delete vertice;
}
