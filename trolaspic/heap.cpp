#include <iostream>
using namespace std;
#include "heap.h"
#include "main.h"

#ifdef DEBUG
void stampaheap(CodaPriorita* Array){
    for(int riga=1, i=1;i<Array[0];riga++){
        for(int limite=(1<<riga);i<Array[0] && i<limite;i++)
            cout<<Array[i]<<' '<<flush;
        cout<<endl;
    }
}
#endif

void scambia(CodaPriorita* Array,int a, int b){
    CodaPriorita temp = Array[a];
    Array[a] = Array[b];
    Array[b] = temp;
};

CodaPriorita parent(CodaPriorita i){
    return i/2;
};

CodaPriorita left(CodaPriorita i){
    return 2*i;
};

CodaPriorita right(CodaPriorita i){
    return (2*i)+1;
};

void min_heapify(CodaPriorita* Array,CodaPriorita i){
    CodaPriorita lefto = left(i);
    CodaPriorita righto = right(i);
    CodaPriorita minimo = i;
    if(lefto < Array[0] && Array[lefto] < Array[minimo]) minimo = lefto;
    if(righto < Array[0] && Array[righto] < Array[minimo]) minimo = righto;
    if(minimo == i) return;
    scambia(Array,i,minimo);
    min_heapify(Array,minimo);
};

void build_min_heap(CodaPriorita* Array){
    for(CodaPriorita i=Array[0]/2;i>0;--i) min_heapify(Array,i);
};

