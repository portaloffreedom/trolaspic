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

#define VERSION "0.2.1a - Fillix"


struct passaggio_t {
    GtkWidget* finestra;
    GtkWidget* info_i;
    GtkWidget* esci_i;
    GtkWidget* carica_i;
    GtkWidget* calcola_i;
    GtkWidget* image;
    GtkWidget* statusbar;
    gint statusbar_id;
    int massimo_numero_nodi;
};

#define partenza_t info_i
#define arrivo_t esci_i

#endif	/* MAIN_H */

