#include "main.h"
#include <iostream>
using namespace std;

#ifdef DEBUG_ROB
/** Il grafo e' rappresentato come una lista di adiacenza.
 * nella posizione 0 viene inserita la grandezza dell'array che contiene il grafo
 * e precisamente nelle variabili x e y. peso viene posto a zero e la lista di adiacenza
 * non contiene nessun elemento.
 */
nodo* GRAFO;

/**
 * @function aggiungi_adiacenza Viene usata per costruire un'adiacenza fra due nodi.
 * @param nod il nodo a cui dobbiamo aggiungere l'adiacenza
 * @param adj il nodo da aggiungere all'adiacenza del primo.
 */
void aggiungi_adiacenza(int nod,int adj,float peso){
    adiacenza* temp;
    temp = new adiacenza;
    temp.nodo = adj;
    temp.peso = peso;
    GRAFO[nod]->adiacente.push_back(temp);
};

/**
 * @function graph_builder Termina la costruzione del grafo inserendo tutti i
 * \n colori dei nodi come bianchi.
 */
void graph_builder(){

};


/**
 * @function graph_loader Carica il grafo da file e lo costruisce per essere usato
 * \n con dijkstra
 * @param widget Usato per le GTK
 * @param file Uno stream input da dove leggere i dati del grafo
 * @return Un puntatore al grafo appena creato.
 */
nodo* graph_loader(GtkWidget* widget,ifstream &file){

};
#endif