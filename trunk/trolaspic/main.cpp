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
 * \n
 * \n \section funz Funzionamento di base
 * \n Il programma carica una mappa in formato png e il suo corrispettivo in map, crea i percorsi e il collegamento dei nodi
 * e permette di selezionare i nodi di inizio e di arrivo per calcolarne il percorso più corto o quello che impiega meno tempo.
 * \n I sensi unici vengondo calcolati ma non segnati sulla mappa, ma sono visibili dal file png.
 * \n \subsection map Gestione della mappa
 * \n Il programma gestisce le mappe come una coppia di file .png e .map chiamati con lo stesso nome. Il formato del file map è univoco e dalla formattazione obbligata.
 * \n ecco un esempio del formato file:
 * \n
 * \n \p risoluzione_x x \p risoluzione_y # la risoluzione dell'immagine png allegata al file.
 * \n Nodi_totali  # i nodi totali contenuti nella mappa
 * \n  NUMNODO ( Coord_x Coord_y ) n: numeronodiadiacenti
 * \n  ---( numnodoadiac distanza_km tempo_sec )                                           # L'arco è una retta fra i 2 nodi
 * \n  ---( numnodoadiac distanza_km tempo_sec ) { B coord_x1 coord_y1 coord_x2 coord_y2 } # L'arco è una curva di bezier
 * \n  ---( numnodoadiac distanza_km tempo_sec ) { R coord_x1 coord_y1 coord_x2 coord_y2 } # L'arco è una retta spezzata
 * \n  # questo è un commento
 * \n  ---$ # questa è la fine del nodo e delle sue adiacenze
 * \n
 * \n Le seguenti funzioni servono per il caricamento della mappa:
 *
 * \n ::carica_mappa
 * \n Vedi anche:
 * \n - grafo.cpp
 * \n
 * \n \subsubsection graph Gestione del grafo creato dalla mappa
 * \n Il caricamento del file (vedi \ref map) crea un grafo che può essere gestito
 * \n con delle semplici funzioni:
 * \n ::distruggi_grafo
 * \n ::dim_grafo
 * \n ::reset_graph
 * \n Il grafo viene gestito principalmente da Dijkstra e dal caricamento file.
 * \n Vedi anche:
 * \n - ::dijkstra
 * \n - \ref pathfinder
 * \n - pathfinder.cpp : File dove sono contenute tutte le funzioni relative al calcolo del percorso.
 * \n
 * \n \subsection draw Gestione dell'interfaccia
 * \n Per disegnare l'interfaccia il programma usa CAIRO e GTK+ 2.0.
 * \n Le funzioni seguenti servono per gestire molti punti disegno del programma:
 * \n ::cairo_disegna \a gestisce l'area dove verrà disegnato il percorso
 * \n ::cairo_disegna_percorso \a disegna il percorso sulla mappa
 * \n ::crea_finestra_dialogo \a crea una finestra di dialogo
 * \n ::crea_finestra_info \a crea la finestra informazioni programma
 * \n ::crea_finestra_principale \a crea la finestra principale del programma
 * \n ::mostra_info \a visualizza la finestra delle informazioni
 * \n ::get_text_from_int \a trasforma un intero in testo per poterlo usare con CAIRO
 * \n
 * \n Vedi anche:
 * \n - creazione_interfaccia.cpp
 * \n - g_callback.cpp
 * \n - gestione_drawing_area.cpp
 * \n
 * \n \subsection pathfinder Ricerca del percorso
 * \n La ricerca del percorso viene fatta usando il pratico algoritmo Dijkstra per il calcolo dei cammini minimi da sorgente unica in un grafo.
 * \n Le funzioni pubbliche da usare sono le seguenti:
 * \n ::dijkstra \a Calcola il percorso minimo secondo l'algoritmo dijkstra
 * \n ::getPath \a Ricostruisce il percorso e resetta il grafo per poterlo usare un'altra volta.
 * \n Vedi anche:
 * \n - pathfinder.cpp
 * \n --------------------------------------------------------------------------
 * \n Vedi anche:
 * \n - \ref using



 * @page using Using trolaspic
 * \n  L'utilizzo di Trolaspic è molto semplice. Carica mappe scritte in un formato speciale.map con l'immagine relativa.
 * \n Selezione il nodo da dove vuoi partire e il nodo dove vuoi arrivare, premendo calcola il risultato verrà visualizzato a schermo.
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
