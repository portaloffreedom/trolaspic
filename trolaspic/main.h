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

#define VERSION "0.8.1a - Fillix"

enum tipo_calcolo {
    per_tempo,
    per_distanza
};

struct passaggio_t {
    GtkWidget* finestra;
    GtkWidget* info_i;
    GtkWidget* esci_i;
    GtkWidget* carica_i;
    GtkWidget* calcola_i;
    GtkWidget* image;
    GtkWidget* radio_distanza;
    GtkWidget* radio_tempo;
    int massimo_numero_nodi;
    gulong calcola_id;
    gulong errore_id;
};

struct passaggio_t2 {
    GtkWidget* finestra;
    GtkWidget* radio_distanza;
    GtkWidget* radio_tempo;
    GtkWidget* partenza_t;
    GtkWidget* arrivo_t;
    tipo_calcolo t_calcolo;
};


#endif	/* MAIN_H */

