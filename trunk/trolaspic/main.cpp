/**
 * @mainpage TROLASPIC - Trovami LA Strada PIu' Corta
 * \n Manuale di utilizzo di TROLASPIC
 * \n - @subpage Intro
 * \n - @subpage using
 * \n @author Badabing inc


 
 * @page Intro Introduzione a Trolaspic
 * \n Trolaspic è un programma open source molto semplice per trovare la distanza minima fra dei punti di passaggio.
 * \n Il suo punto di forza risiede nella semplicità del programma stesso, non difficile e facilmente comprensibile.
 * \n Può essere usato per svariati tipi di soluzioni, come la ricerca di percorsi in mappe stradali.
 * \n Il metodo utilizzato per la ricerca del percorso più breve è quello dell'algoritmo Dijkstra. L'algoritmo Dijkstra opera solo su grafi con archi che hanno pesi positivi.
 * \n \section funz Funzionamento di base
 * \n
 * \n \subsection map Gestione della mappa
 * \n funzione ::carica_mappa : spiegazione funzione
 * \n funzione ::leggi_prox_char : Spiegazione funzione
 * \n funzione ::leggi_prox_double : Spiegazione funzione
 * \n funzione ::leggi_prox_int : spiegazione funzione
 * \n funzione ::imposta_segmentazione : spiegazione funzione
 * \n \subsubsection graph Gestione del grafo creato dalla mappa
 * \n funzione ::distruggi_grafo
 * \n funzione ::dim_grafo
 * \n funzione ::reset_graph

 * \n \subsection draw Gestione dell'interfaccia
 * \n funzione ::cairo_disegna
 * \n funzione ::cairo_disegna_percorso
 * \n funzione ::crea_finestra_dialogo
 * \n funzione ::crea_finestra_info
 * \n funzione ::crea_finestra_principale
 * \n funzione ::mostra_info
 * \n funzione ::get_text_from_int trasforma un intero in testo per poterlo usare con CAIRO

 * \n \subsection pathfinder Ricerca del percorso
 * \n funzione ::dijkstra
 * \n funzione ::getPath

 * \n Vedi anche:
 * \n - \ref using



 * @page using Using trolaspic
 * \n  L'utilizzo di Trolaspic è molto semplice. Carica mappe scritte in un formato speciale.map con l'immagine relativa.
 * \n Clicca sul nodo dove vuoi partire e sul nodo dove vuoi arrivare, premendo calcola il risultato verrà visualizzato a schermo.
 * \n Vedi anche:
 * \n - \ref Intro
 * \n - \ref map

 */

#include <gtk/gtk.h>
#include <iostream>
#include "main.h"
#include "creazione_interfaccia.h"
#include "gestione_drawing_area.h"
#include "g_callback.h"

using namespace std;

//bool mappa_caricata=false;


int main(int argc, char** argv) {
    gtk_init(&argc, &argv);


    //**************************************************************************
    passaggio_t *window= crea_finestra_principale();
    gtk_widget_show(window->finestra);


    g_signal_connect_swapped (window->info_i,   "activate",      G_CALLBACK (mostra_info),      window->finestra );
    g_signal_connect_swapped (window->esci_i,   "activate",      G_CALLBACK (response_dialogo), window->finestra );
    g_signal_connect_swapped (window->carica_i, "activate",      G_CALLBACK (response_carica),  window           );
    g_signal_connect         (window->finestra, "delete-event",  G_CALLBACK (response_dialogo), window->finestra );
    g_signal_connect_swapped (window->radio_distanza, "clicked", G_CALLBACK (set_distanza),     window           );
    g_signal_connect_swapped (window->radio_tempo,    "clicked", G_CALLBACK (set_tempo),        window           );
    g_signal_connect_swapped (window->pulsante_calcola, "clicked",G_CALLBACK(response_calcola), window           );

    //**************************************************************************


    gtk_main();
    delete[] window;
    return 0;
}

/**
 * @file main.cpp
 *
 * File che contiene il ciclo principale del programma.
 *
 *
 */
