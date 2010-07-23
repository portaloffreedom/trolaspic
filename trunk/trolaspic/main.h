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

#define VERSION "1.1.0b"

enum tipo_calcolo {
    per_tempo,
    per_distanza
};

/** Struct per contenere tutti i puntatori dei widget e degli oggetti creati
 * nella finestra principale e necessari alle altre funzioni */
struct passaggio_t {
    /** Puntatore alla finestra principale */
    GtkWidget* finestra;
    /** Puntatore al menu item info nel menu programma */
    GtkWidget* info_i;
    /** Puntatore al menu item esci nel menu programma */
    GtkWidget* esci_i;
    /** Puntatore al menu item carica nel menu mappa */
    GtkWidget* carica_i;
    /** Puntatore al menu item calcola nel menu percoso */
    GtkWidget* calcola_i;
    /** Puntatore al widget che contiene l'immagine */
    GtkWidget* image;
    /** Puntatore al PixBuffer che deve essere caricato dentro il Widget Immagine */
    GdkPixbuf* sfondo;
    /** Intero che memorizza quanti nodi ci sono caricati nel grafo. Serve alla
     * finestra di dialogo delle richiesta di calcolo del percorso per limitare
     * la scelta dei nodi */
    int massimo_numero_nodi;
    /** Handler_id per il signal connect della funzione ::response_calcola che
     * serve per potere attivare e disattivera l'handling */
    gulong calcola_id;
    /** Handler_id per il signal connect della funzione ::response_non_calcola che
     * serve per potere attivare e disattivera l'handling */
    gulong errore_id;
};

/** Struct per contenere tutti i puntatori dei widget e delle informazioni create
 * dalla finestra di calcolo percorso e necessarie per avviare il calcolo del
 * percorso */
struct passaggio_t2 {
    /** Puntatore alla finestra di dialogo della scelta del percorso */
    GtkWidget* finestra;
    /** Puntatore al radio-pulsante che sceglie di calcolare il percorso per distanza */
    GtkWidget* radio_distanza;
    /** Puntatore al radio-pulsante che sceglie di calcolare il percorso per tempo */
    GtkWidget* radio_tempo;
    /** Puntatore al widget di scelta dell'indice del nodo di partenza */
    GtkWidget* partenza_t;
    /** Puntatore al widget di scelta dell'indice del nodo di arrivo */
    GtkWidget* arrivo_t;
    /** Variabile utilizzata per memorizzarci quale percorso verrà utilizzato
     * nel calcolare la strada più breve */
    tipo_calcolo t_calcolo;
};


#endif	/* MAIN_H */

