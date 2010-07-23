/**
 * @file grafo.h Interfaccia per le funzioni pubbliche necessarie a manipolare il grafo.
 * Referenzia le funzioni di grafo.cpp
 * 
 */

#ifndef GRAFO_H
#define	GRAFO_H
#include <fstream>
#include "main.h"

using namespace std;
/** enumerato per i colori della visita */
enum colour_t {bianco,grigio,nero};
/** enumerato per la tipoligia di incrocio */
enum t_incrocio {
    rotatoria,          //r
    incrocio_normale,   //n
    incrocio_semafori,  //s
    strada              //
};

/** enumerato per la tipologia di segmentazione utilizzata per disegnare l'arco*/
enum tipo_segmentazione {
    nessuna,
    rette,
    bezier
};

/** Struct che rappresenta gli archi fra un nodo e l'altro.
 * L'arco indica il nodo, il tempo che impieghi a percorrerlo e la distanza che percorri. */
struct adiacenza{
    /** L'indice del nodo nel grafo
     * Questo indice viene usato per prelevare il nodo dal grafo
     * e non dalla lista.*/
    int nodo;

    /** Il peso dell'arco fra il nodo chiamante e il nodo indicato in kilometri.*/
    double kilometri;
    /** Il peso dell'arco fra il nodo chiamante e il nodo indicato in secondi.*/
    double secondi;

    /** dice se usare la segmentazione a rette o a curve bezier*/
    tipo_segmentazione segmentazione;

    /** oridnata punto 1*/
    int x1;
    /** ascissa punto 1*/
    int y1;

    /** oridnata punto 2*/
    int x2;
    /** ascissa punto 2*/
    int y2;
    
};
typedef adiacenza arco;

/** Struct per la rappresentazione dei nodi di cui e' composto il grafo.
 * Il nodo del grafo è indicato con due coordinate che lo identificano univocamente sulla mappa */
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
    double peso;

    /** Questo parametro serve a ricostruire il tragitto dopo aver usato dijkstra*/
    int padre;
};

extern nodo* GRAPH;

int carica_mappa(const char *filename);

int dim_grafo(void);


#endif	/* GRAFO_H */

