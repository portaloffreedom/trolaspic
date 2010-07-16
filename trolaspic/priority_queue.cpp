#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include "heap.h"
using namespace std;


CodaPriorita minimum(CodaPriorita* Array){
    return Array[1];
};

CodaPriorita extract_min(CodaPriorita* Array){
    if(Array[0]<1){
        cerr<<"Heap Underflow\n";
        return 0;
    }
    CodaPriorita min = Array[1];
    Array[1] = Array[Array[0]-1];
    Array[0]--;
    min_heapify(Array,1);
    return min;
};

void decrease_key(CodaPriorita* Array,int i,CodaPriorita key){
    if(key.f_score < Array[i].f_score){
        cerr<<"La chiave e' piu' grande di quella corrente\n";
        return;
    }
    Array[i].f_score = key.f_score;
    while(i>1 && Array[parent(i)].f_score > Array[i].f_score){
        CodaPriorita parente = parent(i);
        scambia(Array,i,parente);
        i = parente;
    }
};

void insert(CodaPriorita* Array,CodaPriorita key){
    //aumenta i controlli
    if(Array[0]==MAX_HEAP_DIM){
        cerr<<"non posso inserire - heap out of range\n";
        return;
    }
    Array[0]++;
    Array[Array[0]].f_score = numeric_limits<int>::max();
    decrease_key(Array,Array[0],key);
};

CodaPriorita* costrcoda(){
    srand(time(0));
    CodaPriorita* coda = new CodaPriorita[MAX_HEAP_DIM];
    coda[0]=0;
    return coda;
};