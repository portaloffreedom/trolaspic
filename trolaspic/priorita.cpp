#include <iostream>
#include "priorita.h"
#include <limits>
#include <cstring>
using namespace std;

//Implementazione del min-heap

const double INFINITO = numeric_limits<double>::max();

int parent(int i){
    return i/2;
}
int left  (int i){
    return (2*i);
}
int right (int i){
    return (2*i)+1;
}

void scambia(coda_priorita coda,int a, int b){
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
    if(coda[0].nodo == 0) return;
    coda[0].nodo--;
}

#ifdef DEBUG
void stampaheap(elem_priorita* coda){
    for(int riga=1, i=1; i<=dim_coda(coda) ;riga++){
        for(int limite=(1<<riga);i<=dim_coda(coda) && i<limite;i++)
            cout<<coda[i].peso<<'\t'<<flush;
        cout<<endl;
    }
}
#endif

void min_heapifizza(elem_priorita* coda,int posizione){
    int sinistro = left (posizione);
    int destro   = right(posizione);
    int minimo   =       posizione;
    
    if(sinistro < dim_coda(coda) && coda[sinistro].peso < coda[minimo].peso) minimo = sinistro;
    if(destro   < dim_coda(coda) && coda[destro].peso   < coda[minimo].peso   ) minimo = destro;
    if(minimo == posizione) return;
    scambia(coda,posizione,minimo);
    min_heapifizza(coda,minimo);
}

void build_min_heap(elem_priorita* coda){
    for(int i=dim_coda(coda)/2; i>0; i--)
        min_heapifizza(coda,i);
}

coda_priorita inizializza_coda (int dimensioni_max){
    dimensioni_max++;
    coda_priorita coda= new elem_priorita[dimensioni_max];
    memset(coda,NULL,dimensioni_max);
    dim_coda_set(coda,0); //setta le dimensioni della coda
    return coda;
}

void elimina_coda (coda_priorita coda){
    delete[] coda;
    return;
};


elem_priorita estrai_minimo(coda_priorita coda){
    elem_priorita minimo;
    minimo.nodo = 0;
    minimo.peso = 0;
    if(coda[0].nodo == 0) return minimo;
    minimo.nodo = coda[1].nodo;
    minimo.peso = coda[1].peso;
    coda[1]= coda[dim_coda(coda)];
    dim_coda_decrease(coda);
    min_heapifizza(coda,1);
    return minimo;
}

bool diminuisci_chiave(coda_priorita coda, int pos, double nuovo_peso, nome_nodo quale_nodo){
    if (nuovo_peso > coda[pos].peso){
        cerr<<"errore, operazione di cambio chiave di "<<quale_nodo<<" non corretta(chiave nuova"
                " maggiore di quella vecchia)\n";
        return false;
    }
    coda[pos].peso = nuovo_peso;
    while (pos>1 && coda[parent(pos)].peso > coda[pos].peso){
        scambia(coda, pos, parent(pos));
        pos= parent(pos);
    }
    return true;
}

int find (coda_priorita coda, nome_nodo nome){
    for (int i=1; i<=dim_coda(coda); i++){
        if (coda[i].nodo = nome)
            return i;
    }
    return -1;
    //tentativo (inutile) di fare la ricerca ricorsiva
    /*if (i < dim_coda(coda)){
        if (coda[i].nodo = nome)
            return nome;
            
        int pos_s = find(coda, nome_nodo nome, int left(i));
        if (pos_s == -1){
            int pos_d = find(coda, nome_nodo nome, int right(i));
            return pos_d;
        }
        else return pos_s;
        
    }
    else return -1;*/
}

bool cambia_chiave(coda_priorita coda, nome_nodo quale_nodo, double nuovo_peso){
    int pos= find (coda, quale_nodo);
    if (pos==-1){
        cerr<<"chiave da diminuire non trovata\n";
        return false;
    }
    return diminuisci_chiave(coda, pos, nuovo_peso, quale_nodo);
}

void inserisci(elem_priorita* coda, double key, nome_nodo nome){
    dim_coda_increase(coda);
    coda[dim_coda(coda)].peso = INFINITO;
    coda[dim_coda(coda)].nodo = nome;
    coda[dim_coda(coda)].nodo= nome;
    diminuisci_chiave(coda, dim_coda(coda), key, nome);
}

bool coda_vuota(coda_priorita coda) {
    if (dim_coda(coda)==0)  return true;
                            return false;
}