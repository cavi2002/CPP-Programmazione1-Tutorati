#include <iostream>
using namespace std;

const int DIM = 10;

void aux_somma_incrociata(int * v1, int * v2, int dim, int i, int j, int * vf);

int * somma_incrociata(int * v1, int * v2, int dim);

int main(){

  int primo[] = {1,2,3,4,5,6,7,8,9,10};
  int secondo[]  = {1,1,2,3,5,8,13,21,34,55};
  int *risultato = somma_incrociata(primo, secondo, DIM);

  for(int i = 0; i<DIM; i++){
    cout << "[" << risultato[i] <<"] "; 
  }
  cout << endl;

  delete[] risultato;
  return 0;
}

void aux_somma_incrociata(int * v1, int * v2, int dim, int i, int j, int * vf){
  if(i>=dim){
  }else{
    vf[i] = v1[i]+v2[j];
    aux_somma_incrociata(v1, v2, dim, i+1, j-1, vf);
  }
}

int * somma_incrociata(int * v1, int * v2, int dim){
  int * vf = new int[dim];
  aux_somma_incrociata(v1, v2, dim, 0, dim-1, vf);
  return vf;
}
