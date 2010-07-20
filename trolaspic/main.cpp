/*
 * File:   main.cpp
 * Author: matteo
 *
 * Created on 7 luglio 2010, 19.59
 */

#include <gtk/gtk.h>
#include <iostream>
#include "main.h"
#include "creazione_interfaccia.h"
#include "gestione_drawing_area.h"
#include "g_callback.h"

#ifdef DEBUG_MATTEO
#include "priorita.h"
#endif

using namespace std;


int main(int argc, char** argv) {
    gtk_init(&argc, &argv);
#ifdef DEBUG_MATTEO
    const int dimensioni_coda = 30;
    coda_priorita coda = inizializza_coda (dimensioni_coda);

    inserisci (coda, 3.5,  5 );
    inserisci (coda, 4.6,  6 );
    inserisci (coda, 5.7,  5 );
    inserisci (coda, 2.8,  5 );
    inserisci (coda, 3.9,  5 );
    inserisci (coda, 4.1,  1 );
    inserisci (coda, 65.12, 12);
    inserisci (coda, 3.13, 13);
    inserisci (coda, 324.14, 14);

    stampaheap (coda);

    elem_priorita elemento;
    elemento= estrai_minimo(coda);
    cout<<"nome_nodo: "<<elemento.nodo<<" - peso: "<<elemento.peso<<endl;
    elemento= estrai_minimo(coda);
    cout<<"nome_nodo: "<<elemento.nodo<<" - peso: "<<elemento.peso<<endl;
    elemento= estrai_minimo(coda);
    cout<<"nome_nodo: "<<elemento.nodo<<" - peso: "<<elemento.peso<<endl;
    elemento= estrai_minimo(coda);
    cout<<"nome_nodo: "<<elemento.nodo<<" - peso: "<<elemento.peso<<endl;
    elemento= estrai_minimo(coda);
    cout<<"nome_nodo: "<<elemento.nodo<<" - peso: "<<elemento.peso<<endl;
    elemento= estrai_minimo(coda);
    cout<<"nome_nodo: "<<elemento.nodo<<" - peso: "<<elemento.peso<<endl;

    elimina_coda (coda);
#endif

    //**************************************************************************
    passaggio_t *window= crea_finestra_principale();
    gtk_widget_show(window->finestra);


    g_signal_connect_swapped (window->info_i, "activate", G_CALLBACK(mostra_info), window->finestra);
    g_signal_connect_swapped (window->esci_i, "activate", G_CALLBACK (response_dialogo), window->finestra);
    g_signal_connect_swapped (window->carica_i, "activate", G_CALLBACK (response_carica), window);
    g_signal_connect_swapped (window->calcola_i, "activate", G_CALLBACK (response_calcola), window);
    g_signal_connect (window->finestra, "delete-event", G_CALLBACK (response_dialogo), window->finestra);
    //**************************************************************************


    gtk_main();
    delete[] window;
    return 0;
}
