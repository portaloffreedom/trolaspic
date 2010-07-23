#include "pila.h"

pila_char crea_pila_char(int max_elem){

    pila_char pila = new pila_ch;
    pila->ultimo_elem=0;
    pila->pila= new char[max_elem];
    return pila;
}

void push_pila_char(pila_char pila, char carattere){
    pila->ultimo_elem++;
    pila->pila[pila->ultimo_elem]=carattere;
    return;
}

char pop_pila_char(pila_char pila){
    char carattere = pila->pila[pila->ultimo_elem];
    pila->ultimo_elem--;
    return carattere;
}

void distruggi_pila_char(pila_char pila){
    delete[] pila->pila;
    delete[] pila;
    return;
}