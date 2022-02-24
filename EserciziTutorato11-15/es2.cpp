#include <cstdlib>
#include <iostream>

using namespace std;

// Scrivere qui sotto la dichiarazione della funzione "funzione"
int funzione(int n);
int aux_funzione(int n, int primo, int ultimo);
// Scrivere qui sopra la dichiarazione della funzione "funzione"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <positivenum> " << std::endl;
        exit(1);
    }
    int n = atoi(argv[1]);
    std::cout << "The read string is: " << argv[1] << std::endl;
    std::cout << "The converted value is: " << n << std::endl;
    std::cout << "function(" << n << ") = " << funzione(n) << std::endl;
}


// Scrivere qui sopra la definizione della funzione "funzione"
int funzione(int n){
  return aux_funzione(n/10, n%10, (n/10)%10);
}

int aux_funzione(int n, int primo, int ultimo){
  if(n<=0){
    return 0;
  }else{
    if(primo==ultimo){
      return 1 + aux_funzione(n/10, n%10, (n/10)%10);
    }else{
      return 0 + aux_funzione(n/10, n%10, (n/10)%10);
    }
  }
}
// Scrivere qui sotto la definizione della funzione "funzione"
