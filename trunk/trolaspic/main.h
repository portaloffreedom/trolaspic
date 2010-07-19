/* 
 * File:   main.h
 * Author: matteo
 *
 * Created on 8 luglio 2010, 18.50
 */

#ifndef MAIN_H
#define	MAIN_H
#include <gtk/gtk.h>
#include <list>
using namespace std;

#ifdef DEBUG
    #define DBG(A) A;
#else
    #define DBG(A)
#endif

#ifndef DEBUG_MATTEO
    #define PERCORSO "."
#else
    #define PERCORSO "./NetBeansProjects/trolaspic_code/trunk/trolaspic"
#endif

#define VERSION "0.0.20a"


struct passaggio_t {
    GtkWidget* finestra;
    GtkWidget* info_i;
    GtkWidget* esci_i;
    GtkWidget* carica_i;
    GtkWidget* calcola_i;
    GtkWidget* image;
    GtkWidget* statusbar;
    gint statusbar_id;
};


//#define finestra     elem0
//#define esci_i       elem1
//#define carica_i     elem2
//#define calcola_i    elem3
//#define image        elem4



#ifdef DEBUG_mMATTEO
//referenza per il la vera dichiarazione sotto
struct archi;
struct nodo;
struct lista_archi;

typedef archi strade;
typedef lista_archi lista_strade;
typedef nodo incrocio;


typedef nodo incrocio;
struct nodo {
    /** Coordinate dell'incrocio*/
    int x;
    int y;
    
    /** Tipologia di incrocio */
    t_incrocio tipo_incrocio;

    /** Lista di adiacenza delle strade a cui si accede all'incrocio */
    lista_strade* elem_lista;

    /** Numero di elementi nella lista di adiacenza*/
    int num_elem_lista;
};

typedef archi strade;
struct archi {
    /** nome della via */
    char* nome;

    /** Incrocio a cui punta l'arco */
    incrocio* direzione;

    /** Lunghezza in m o Km della strada */
    double lunghezza;

    /** moltiplicativo -> maggiore di uno è più pesante la strada / minore di
     * uno è più leggero */
    double scorribilita;


    //tipo di curvatura della strada
};


typedef lista_archi lista_strade;
struct lista_archi {

    /** Strada associata a questo elemento della lista */
    strade* strada;
    
    /** A che angolo di rotazione è questa strada.
     * \n Partendo da Nord rotando in senso orario
     * \n (serve alla funzione che disegna le strade, forse.
     * può anche servire per dare penalità alle strade più lontane nella rotatoria);
     */
    double rotazione;
};

#elif DEBUG_ROB
//Nuovo metodo per la creazione dei nodi
enum colour_t {bianco,grigio,nero};

/** Struct che rappresenta gli archi fra un nodo e l'altro
 */
struct adiacenza{
    /** L'indice del nodo nel grafo
     * Questo indice viene usato per prelevare il nodo dal grafo
     * e non dalla lista.
     */
    int nodo;

    /** Il peso dell'arco fra il nodo chiamante e il nodo indicato.
     */
    float peso;

    /** Il prossimo nodo adiacente. NULL se non ci sono altri nodi.
     */
    list<adiacenza> adiacente;
};

/** Struct per la rappresentazione dei nodi di cui e' composto il grafo
 */
struct nodo {
    /** Coordinata orizzontale del nodo sulla mappa
     */
    int x;
    /** Coordinata Verticale del nodo sulla mappa
     */
    int y;

    /** Colore da impostare secondo làalgoritmo dijkstra.
     * \n Bianco se il nodo non e' mai stato visitato
     * \n Grigio se il nodo e' stato visitato ma i suoi archi non sono stati tutti rilassati
     * \n Nero se il nodo e' stato visitato e ha gli archi tutti rilassati
     */
    colour_t visitato;

    /** Tipo di incrocio che rappreenta questo nodo.
     * \n Rotatoria
     * \n Incrocio senza semaforo
     * \n Incrocio con semaforo
     * \n semplice strada (utile se rappresentiamo una strada come l'unione di tanti nodi)
     */
    t_incrocio tipo;

    /** Quanto pesa passare da questo nodo.
     * \n Questo peso e' usato da Dijkstra e non ha niente a che fare
     * \n con la distanza delle strade
     */
    float peso;

    /** Questo parametro serve a ricostruire il tragitto dopo aver usato dijkstra*/
    int padre;

    /** Tutti i nodi che e' possibile raggiungere da questo
     */
    list<adiacenza> adiacente;
};

#endif

#endif	/* MAIN_H */

