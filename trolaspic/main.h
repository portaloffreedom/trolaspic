/* 
 * File:   main.h
 * Author: matteo
 *
 * Created on 8 luglio 2010, 18.50
 */

#ifndef MAIN_H
#define	MAIN_H
#include <gtk/gtk.h>

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

#define VERSION "0.0.19a"

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

enum t_incrocio {
    rotatoria,          //r
    incrocio_normale,   //n
    incrocio_semafori   //s
};


//referenza per il la vera dichiarazione sotto
struct archi;
struct nodo;
struct lista_archi;

typedef archi strade;
typedef lista_archi lista_strade;
typedef nodo incrocio;


typedef nodo incrocio;
struct nodo {
    /** Tipologia di incrocio */
    t_incrocio tipo_incrocio;

    /** Lista di adiacenza delle strade a cui si accede all'incrocio */
    lista_strade elem_lista[];

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

    /** Velocità massima o media di percorrenza della strada (m/s oppure Km/h) */
    double velocita;


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

#endif	/* MAIN_H */

