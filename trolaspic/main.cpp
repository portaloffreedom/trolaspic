/**
 * @mainpage TROLASPIC - Trovami LA Strada PIu' Corta
 * \n Manuale di utilizzo di TROLASPIC
 * \n - @subpage Intro
 * \n - @subpage using
 * \n @author Badabing inc
 *
 * @page Intro Introduzione a Trolaspic
 * \n Trolaspic è un programma open source molto semplice per trovare la distanza minima fra dei punti di passaggio.
 * \n Il suo punto di forza risiede nella semplicità del programma stesso, non difficile e facilmente comprensibile.
 * \n Può essere usato per svariati tipi di soluzioni, come la ricerca di percorsi in mappe stradali.
 * \n Il metodo utilizzato per la ricerca del percorso più breve è quello dell'algoritmo Dijkstra. L'algoritmo Dijkstra opera solo su grafi con archi che hanno pesi positivi.
 * \n Vedi anche:
 * \n - \ref using
 * @page using Using trolaspic
 * \n  L'utilizzo di Trolaspic è molto semplice. Carica mappe scritte in un formato speciale.map con l'immagine relativa.
 * \n Clicca sul nodo dove vuoi partire e sul nodo dove vuoi arrivare, premendo calcola il risultato verrà visualizzato a schermo.
 * \n Vedi anche:
 * \n - \ref Intro
 *
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


    g_signal_connect_swapped (window->info_i,   "activate",     G_CALLBACK (mostra_info),      window->finestra);
    g_signal_connect_swapped (window->esci_i,   "activate",     G_CALLBACK (response_dialogo), window->finestra);
    g_signal_connect_swapped (window->carica_i, "activate",     G_CALLBACK (response_carica),  window          );
    g_signal_connect         (window->finestra, "delete-event", G_CALLBACK (response_dialogo), window->finestra);
//    g_signal_connect_swapped (window->radio_distanza, "clicked", G_CALLBACK(set_distanza), dialogo);
//    g_signal_connect_swapped (window->radio_tempo,    "clicked", G_CALLBACK(set_tempo),    dialogo);

    window->calcola_id =
        g_signal_connect_swapped (window->calcola_i, "activate", G_CALLBACK (response_calcola), window);
    window->errore_id  =
        g_signal_connect_swapped (window->calcola_i, "activate", G_CALLBACK (response_non_calcola), window->finestra);

    g_signal_handler_block( window->calcola_i, window->calcola_id);

    //**************************************************************************


    gtk_main();
    delete[] window;
    return 0;
}
