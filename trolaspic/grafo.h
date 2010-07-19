/* 
 * File:   grafo.h
 * Author: stengun
 *
 * Created on 9 luglio 2010, 14.13
 */

#ifndef GRAFO_H
#define	GRAFO_H
#include <fstream>
#include "main.h"

using namespace std;

enum colour_t {bianco,grigio,nero};
enum t_incrocio {
    rotatoria,          //r
    incrocio_normale,   //n
    incrocio_semafori,  //s
    strada              //
};

/** Struct che rappresenta gli archi fra un nodo e l'altro
 */
struct adiacenza{
    /** L'indice del nodo nel grafo
     * Questo indice viene usato per prelevare il nodo dal grafo
     * e non dalla lista.
     */
    int nodo;

    /** Il peso dell'arco fra il nodo chiamante e il nodo indicato.*/
    float kilometri;
    float secondi;
    
};
typedef adiacenza arco;

/** Struct per la rappresentazione dei nodi di cui e' composto il grafo
 */
struct nodo {
    /** Coordinata orizzontale del nodo sulla mappa */
    int x;
    /** Coordinata Verticale del nodo sulla mappa */
    int y;

    /** Tipo di incrocio che rappreenta questo nodo.
     * \n Rotatoria
     * \n Incrocio senza semaforo
     * \n Incrocio con semaforo
     * \n semplice strada (utile se rappresentiamo una strada come l'unione di tanti nodi)
     */
    t_incrocio tipo;

    /** Tutti i nodi che e' possibile raggiungere da questo */
    list<adiacenza> adiacente;

    /** Quanto è grande la lista di adiacenza */
    int size_list;



    //ROBA CHE SERVE SOLO PER LA RICERCA ---------------------------------------
    /** Colore da impostare secondo l'algoritmo dijkstra.
     * \n Bianco se il nodo non e' mai stato visitato
     * \n Grigio se il nodo e' stato visitato ma i suoi archi non sono stati tutti rilassati
     * \n Nero se il nodo e' stato visitato e ha gli archi tutti rilassati
     */
    colour_t visitato;

    /** Quanto pesa passare da questo nodo.
     * \n Questo peso e' usato da Dijkstra e non ha niente a che fare
     * \n con la distanza delle strade
     */
    float peso;

    /** Questo parametro serve a ricostruire il tragitto dopo aver usato dijkstra*/
    int padre;
};

/** @param GRAFO Il grafo e' rappresentato come una lista di adiacenza.
 * nella posizione 0 viene inserita la grandezza dell'array che contiene il grafo
 * e precisamente nelle variabili x e y. peso viene posto a zero e la lista di adiacenza
 * non contiene nessun elemento.
 */

//void graph_loader(GtkWidget* widget,ifstream &file);
void carica_mappa(const char *filename);

#endif	/* GRAFO_H */

