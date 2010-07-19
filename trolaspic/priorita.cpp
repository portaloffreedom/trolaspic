#include <iostream>
#include "priorita.h"
using namespace std;

//Implementazione del min-heap
#ifdef DEBUG
void stampaheap(elem_priorita* coda){
    for(int riga=1, i=1; i<dim_coda(coda) ;riga++){
        for(int limite=(1<<riga);i<dim_coda(coda) && i<limite;i++)
            cout<<coda[i].peso<<'\t'<<flush;
        cout<<endl;
    }
}
#endif

int parent(int i){
    return i/2;
}
int left  (int i){
    return (2*i);
}
int right (int i){
    return (2*i)+1;
}

void scambia(elem_priorita* coda,int a, int b){
    elem_priorita temp = coda[a];
    coda[a] = coda[b];
    coda[b] = temp;
}

int dim_coda(coda_priorita coda){
    return coda[0].nodo;
}
void dim_coda_set(coda_priorita coda, int dimensioni){
    coda[0].nodo= dimensioni;
}
void dim_coda_increase(coda_priorita coda){
    coda[0].nodo++;
}
void dim_coda_decrease(coda_priorita coda){
    coda[0].nodo--;
}

void min_heapify(elem_priorita* coda,int posizione){
    int sinistro = left (posizione);
    int destro   = right(posizione);
    int minimo   =       posizione;
    
    if(sinistro < dim_coda(coda) && coda[sinistro].peso < coda[posizione].peso) minimo = sinistro;
    if(destro   < dim_coda(coda) && coda[destro].peso   < coda[minimo].peso   ) minimo = destro;
    if(minimo == posizione) return;
    scambia(coda,posizione,minimo);
    min_heapify(coda,minimo);
}

void build_min_heap(elem_priorita* coda){
    for(int i=dim_coda(coda)/2; i>0; --i)
        min_heapify(coda,i);
}

coda_priorita inizializza_coda (int dimensioni_max){
    dimensioni_max++;
    coda_priorita coda= new elem_priorita[dimensioni_max];
    dim_coda_set(coda,0); //setta le dimensioni della coda
    return coda;
}








elem_priorita estrai_minimo(elem_priorita* coda){
    coda[1]= coda[dim_coda(coda)];
}

elem_priorita inserisci(elem_priorita* coda, float key, int informazione){
    
}

elem_priorita cambia_chiave(elem_priorita* &coda){

}
