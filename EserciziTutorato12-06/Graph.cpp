#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

struct set{
    int* arrayList = nullptr;
    int current_size = 0;
    int buffer_length = 5;
    const float EXPANSION_FACTOR = 2.0;
    const float LOAD = 0.25;
};

void init(set& s){
  s.arrayList = new int[s.buffer_length];
}

void shrink(set& s){
  int * new_array = new int[(int)(s.buffer_length/2)];
  for(int i = 0; i < s.current_size; i++){
    new_array[i] = s.arrayList[i];
  }
  delete[] s.arrayList;
  s.arrayList = new_array;
  s.buffer_length = s.buffer_length/2;
}

void remove_element(set& s, int value){
  bool trovato = false;
  for(int i = 0; i < s.current_size; i++){
    if(s.arrayList[i]==value){
      trovato = true;
      while(i<s.current_size){
        int t = s.arrayList[i];
        s.arrayList[i] = s.arrayList[i+1];
        s.arrayList[i+1] = t;
        i++;
      }
      s.current_size--;
      if(s.current_size*100/s.buffer_length<s.LOAD){
        shrink(s);
      }
    }
  }
}

bool contains(set& s, int value){
  //binary search
  bool ritorno = false;
  int inizio = 0, fine = s.current_size;
  int middle;
  while(inizio<fine){
    middle = (inizio+fine)/2;
    if(s.arrayList[middle]>value){
      fine = middle;
    }else if(s.arrayList[middle]<value){
      inizio = middle+1;
    }else if(s.arrayList[middle]==value){
      ritorno = true;
      inizio = fine;
    }
  }
  return ritorno;
}

void expand(set& s){
  int * new_array = new int[(int)(s.buffer_length*s.EXPANSION_FACTOR)];
  for(int i = 0; i < s.current_size; i++){
    new_array[i] = s.arrayList[i];
  }
  delete[] s.arrayList;
  s.arrayList = new_array;
  s.buffer_length = s.buffer_length*s.EXPANSION_FACTOR;
}
bool empty(set& s){
  return (s.current_size==0);
}
bool full(set &s){
  return (s.current_size==s.buffer_length);
}
void print_set(set& s){
  cout << "[";
  for(int i = 0; i < s.current_size; i++){
    cout << " " <<s.arrayList[i];
  }
  cout << " ]";
}
void dealloc(set& s){
  delete[] s.arrayList;
}

void insert(set& s, int value){
  if(empty(s)){
    s.arrayList[0] = value;
    s.current_size++;
  }else{
    if(!contains(s, value)){
      if(full(s)){
        expand(s);
      }
      s.arrayList[s.current_size] = value;
      s.current_size += 1;
      for(int i = 0; i < s.current_size-1; i++){
        for(int j = 0; j < s.current_size-1-i; j++){
          if(s.arrayList[j]>s.arrayList[j+1]){
            int t = s.arrayList[j];
            s.arrayList[j] = s.arrayList[j+1];
            s.arrayList[j+1] = t;
          }
        }
      }
    }
  }
}

struct graph{
    int** adjMatrix = nullptr;
    int number_of_nodes = 0;
};

void init(graph& g, int number_of_nodes){
  g.number_of_nodes = number_of_nodes;
  g.adjMatrix = new int*[number_of_nodes];
  for(int i = 0; i<number_of_nodes; i++){
    g.adjMatrix[i] = new int[number_of_nodes];
  }
}

void fill_graph(graph& g, const char* file_path){
  int n1, n2;
  fstream input;
  input.open(file_path, ios::in);
  if(input.fail()){
    cout << "Errore nell'apertura del file";
  }else{
    char carattere[2];
    input >> carattere;
    init(g, atoi(carattere));
    while(input >> carattere){
      n1 = atoi(carattere);
      input >> carattere;
      n2 = atoi(carattere);
      g.adjMatrix[n1][n2] = 1;
    }
  }
  input.close();
}

void print_graph(graph& g){
  for(int i = 0; i < g.number_of_nodes; i++){
    for(int j = 0; j < g.number_of_nodes; j++){
      if(g.adjMatrix[i][j]==1){
	cout << "Node "<< i <<" -> " << j << endl;
      }
    }
  }
}

static void dependences_aux(graph& g, int node, int nodeStart, set& s){
  if(nodeStart==node||(contains(s, node))){
  }else{
    for(int j = 0; j < g.number_of_nodes; j++){
      if((g.adjMatrix[node][j]==1)){
        dependences_aux(g, j, nodeStart, s);
        insert(s, j);
      }
    }
  }
}

void dependences(graph& g, int node){
  set s;
  init(s);
  for(int j = 0; j < g.number_of_nodes; j++){
    if(g.adjMatrix[node][j]==1){
      dependences_aux(g, j, node, s);
      insert(s, j);
    }
  }
  remove_element(s, node);
  print_set(s);
  dealloc(s);
}

void dealloc(graph& g){
  for(int i = 0; i<g.number_of_nodes; i++){
    delete[] g.adjMatrix[i];
  }
  delete[] g.adjMatrix;
}
