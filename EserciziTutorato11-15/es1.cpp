#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

void leggi_e_calcola_massimo(char nome_file[], int &massimo);

const int MAX_DIM = 1000;

int main() {
    char nome_file[] = "input1.txt";
    int result = 0;
    leggi_e_calcola_massimo(nome_file, result);

    cout << "Il numero massimo in " << nome_file << " e': " << result << endl;
    return 0;
}

// Scrivere qui sotto la definizione della funzione "funzione"

void leggi_e_calcola_massimo(char nome_file[], int &massimo){
  ifstream input;
  ofstream output;
  input.open(nome_file, ios::in);
  output.open(nome_file, ios::app);
  char stringa[MAX_DIM];
  input >> stringa;
  massimo = strlen(stringa);
  while(input>>stringa){
    if(massimo<strlen(stringa)){
      massimo = strlen(stringa);
    }
  }
  output << endl << massimo << endl;
  input.close();
  output.close();
}

// Scrivere qui sopra la definizione della funzione "funzione"
