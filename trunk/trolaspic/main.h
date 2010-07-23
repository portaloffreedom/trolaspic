/**
 * @file main.h Contiene i dati fondamentali necessari a tutti i modoli del programma.
 * Ogni modulo del programma deve avere incluso questo file.
 * Contiene la versione del file, gli enumerati e gli struct fondamentali.
 *
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

#define VERSION "1.2.2 RC"

/** Stabilisce se il calcolo del percorso deve essere fatto considerando il tempo di percorrenza o la lunghezza della strada. */
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
    /** Puntatore al widget che contiene l'immagine */
    GtkWidget* image;
    /** Puntatore al PixBuffer che deve essere caricato dentro il Widget Immagine */
    GdkPixbuf* sfondo;
    /** Intero che memorizza quanti nodi ci sono caricati nel grafo. Serve alla
     * finestra di dialogo delle richiesta di calcolo del percorso per limitare
     * la scelta dei nodi */
    int massimo_numero_nodi;
    /** Puntatore al label che intitola l'interfaccia di calcolo del percorso */
    GtkWidget* domanda_calcola;
    /** Puntatore alla scatola che contiene gli oggetti per il calcolo del percorso*/
    GtkWidget* scatola_calcola;
    /** Puntatore allo spin della partenza */
    GtkWidget* spin_partenza;
    /** Puntatore allo spin dell'arrivo */
    GtkWidget* spin_arrivo;
    /** Puntatore al radio-pulsante che sceglie di calcolare il percorso per distanza */
    GtkWidget* radio_distanza;
    /** Puntatore al radio-pulsante che sceglie di calcolare il percorso per tempo */
    GtkWidget* radio_tempo;
    /** Puntatore al pulsante che fa partire il calcolo del percorso*/
    GtkWidget* pulsante_calcola;
    /** Variabile utilizzata per memorizzarci quale percorso verrà utilizzato
     * nel calcolare la strada più breve */
    tipo_calcolo t_calcolo;
};


#endif	/* MAIN_H */

