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

bool mappa_caricata=false;


int main(int argc, char** argv) {
    gtk_init(&argc, &argv);


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
