#include <iostream>
#include "PriorityQ.h"
using namespace std;

priorityQueue* init(int dim){
  priorityQueue * pq = new priorityQueue;
  pq->dim = dim;
  pq->queue = new (nothrow) node *[dim];
  for(int i = 0; i < dim; i++){
    pq->queue[i] = nullptr;
  }
  return pq;
}

void enqueue(priorityQueue& pq, int value, int priority){
  if(!(priority>=pq.dim||priority<0)){
    if(pq.queue[priority]==nullptr){
      pq.queue[priority] = new (nothrow) node;
      pq.queue[priority]->value = value;
    }else{
      node * t = pq.queue[priority];
      while(t->right!=nullptr){
	t = t->right;
      }
      node * nuovo_nodo = new node;
      nuovo_nodo->value = value;
      t->right = nuovo_nodo;
      nuovo_nodo->left = t;
    }
  }else{
    cout << "Priorità non presente" << endl;
  }
}

int dequeue(priorityQueue& pq){
  int ritorno = -1;
  for(int i = 0; i < pq.dim; i++){
    if(pq.queue[i]==nullptr){
    }else{
      node * t = pq.queue[i];
      ritorno = t->value;
      node * temp;
      temp = pq.queue[i];
      pq.queue[i] = temp->right;
      pq.queue[i-1] = pq.queue[i]; 
      delete temp;
      i = pq.dim;
    }
  }
  return ritorno;
}
void print(priorityQueue& pq){
  for(int i = 0; i < pq.dim; i++){
    cout << "Coda con priorità " << i <<": ";
    if(!(pq.queue[i]==nullptr)){
      node * t = pq.queue[i];
      while(t!=nullptr){
	cout << t->value << " ";
	t = t->right;
      }
      cout << endl;
    }else{
      cout << "Vuota" << endl;
    }
  }
}

void dealloc(priorityQueue& pq){
  node* nodoCorrente;
  for(int i = 0; i < pq.dim; i++){
    nodoCorrente = pq.queue[i];
    while(nodoCorrente!=nullptr){
      auto temp = nodoCorrente;
      nodoCorrente = nodoCorrente->right;
      delete temp;
    }
  }
  delete[] pq.queue;
}
