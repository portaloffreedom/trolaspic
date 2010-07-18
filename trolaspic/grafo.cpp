#include "grafo.h"
#include <iostream>
using namespace std;

#ifdef DEBUG_ROB
const float INFINITO = numeric_limits<float>::max();

/**
 * @function preleva_nodo usa uno stream di input per leggere il nodo da inserire
 * nel grafo
 * @param file lo stream input da dove leggere le proprieta' del nodo
 * @param x riferimento dove scrivere la coordinata x del nodo
 * @param y riferimento dove scrivere la coordinata y del nodo
 * @return Restituisce -1 se non c'e' altro da prelevare, altrimenti da l'indice del nodo
 */
int preleva_nodo(ifstream &file,int &x,int &y);

/**
 * @function preleva_adiacenze viene usato per prendere le adiacenze di un nodo.
 * preleva sia le adiacenze che il loro peso relativo. In sostanza, prende tutti
 * i dati che servono per creare l'arco
 * @param file stream di input da dove leggere i dati.
 * @param peso passato per riferimento, scrive il peso dell'arco
 * @return restituisce il nodo adiacente, zero altrimenti.
 */
int preleva_adiacenze(ifstream &file,float &peso);

/**
 * @function aggiungi_adiacenza Viene usata per costruire un'adiacenza fra due nodi.
 * costruisce nella pratica un grafo orientato.
 * @param nod il nodo a cui dobbiamo aggiungere l'adiacenza
 * @param adj il nodo da aggiungere all'adiacenza del primo.
 * @param peso il peso associato all'arco
 */
void aggiungi_adiacenza(int nod,int adj,float peso){
    adiacenza* temp;
    temp = new adiacenza;
    temp->nodo = adj;
    temp->peso = peso;
    GRAFO[nod]->adiacente.push_back(temp);
};

/**
 * @function graph_builder Termina la costruzione del grafo inserendo tutti i
 * colori dei nodi come bianchi.
 */
void graph_builder(ifstream &file){
    int x = 0;
    int y = 0;
    int node = preleva_nodo(file,x,y);
    while(node > 0){
        GRAFO[node]->x = x;
        GRAFO[node]->y = y;
        GRAFO[node]->visitato = bianco;
        GRAFO[node]->padre = -1;
        GRAFO[node]->peso = INFINITO;

        adiacenza adj;
        adj.nodo = preleva_adiacenze(file,adj.peso);
        while(adj.nodo > 0){
            GRAFO[node]->adiacente.push_back(adj);
            adj.nodo = preleva_adiacenze(file,adj.peso);
        }
        node = preleva_nodo(file,x,y);
    }
};


/**
 * @function graph_loader Carica il grafo da file e lo costruisce per essere usato con dijkstra
 * @param widget Usato per le GTK
 * @param file Uno stream input da dove leggere i dati del grafo
 */
void graph_loader(GtkWidget* widget,ifstream &file){
    if(GRAFO != 0) delete[] GRAFO;
    int grandezza;
    //Preleva dal file la grandezza, crea con questa un grafo grande "grandezza + 1"
    // ....... inserire il codice qui
    GRAFO = new nodo[grandezza + 1];
    //scrivi la grandezza nella posizione 0, in x e y. Poni peso = 0
    // ..... inserire il codice qui
    graph_builder(file);
};
#endif