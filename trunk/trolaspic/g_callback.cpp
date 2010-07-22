#include <gtk/gtk.h>
#include <iostream>
#include <fstream>
#include "main.h"
#include "creazione_interfaccia.h"
#include "gestione_drawing_area.h"
#include "pathfinder.h"
#include "grafo.h"
using namespace std;

/**
 * Impedisci la distruzine dell'oggetto window
 *
 * @param window l'oggetto di cui impedire la distruzione
 * @param evento non utilizzato (serve solo per chiamarlo con le funzioni)
 * @param dialogo finestra di dialogo da mostrare
 * @return TRUE se non devo distruggere la finestra, FALSE altrimenti
 */
gboolean delete_event_window(GtkWidget* window, GdkEvent* evento,GtkWidget* dialogo){
    DBG(cout<<"delete event occurred on Widget "<<window<<endl)
    gtk_widget_show(dialogo);
    return TRUE;
}

/**
 * Crea la finestra di conferma uscita
 * @param finestra Il puntatore alla finestra chiamante
 */
void response_dialogo (GtkWidget* finestra){
    GtkWidget * dialogo= crea_finestra_dialogo (finestra,"Sei sicuro di volere uscire?");
    
    switch (gtk_dialog_run (GTK_DIALOG (dialogo))) {

        case GTK_RESPONSE_ACCEPT:
            gtk_main_quit();

        default:
            gtk_widget_destroy (dialogo);
    }
}

/**
 * Funzione che parte premendo il pulsante Carica mappa.
 * Prepara il grafo dal file .map allegato effettuando i controlli necessari.
 * Se tutto è andato a buon fine allora viene chiamata la funzione per disegnare
 * i tracciati dei percorsi con CAIRO.
 * @param window puntatore alla struct contenente tutti i puntatori della finestra principale.
 */
void response_carica (passaggio_t *window){
    GtkWidget * dialogo= gtk_file_chooser_dialog_new    ("Carica una mappa", GTK_WINDOW(window->finestra), GTK_FILE_CHOOSER_ACTION_OPEN,
                                                          GTK_STOCK_CANCEL, GTK_RESPONSE_REJECT,
                                                          GTK_STOCK_OK, GTK_RESPONSE_ACCEPT,
                                                         NULL);
    switch (gtk_dialog_run (GTK_DIALOG (dialogo))) {

        case GTK_RESPONSE_ACCEPT:{
            const char *filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialogo));
            DBG(cout<<"Nome del file: "<<filename<<endl);

            //******************************************************************
            //*** CARICAMENTO DELL'IMMAGINE DELLA MAPPA ************************
            //******************************************************************

            GError *errore = NULL;
            GdkPixbuf *immagine_mappa= gdk_pixbuf_new_from_file (filename, &errore);
            gdk_pixbuf_unref (window->sfondo);
            window->sfondo = immagine_mappa;
            gtk_image_set_from_pixbuf (GTK_IMAGE(window->image), immagine_mappa);

            if (errore != NULL){
                cerr<<"Errore nel caricamento dell'immagine!\n"
                        "prova a caricare il file giusto\n";
                delete[] filename;
                gtk_widget_destroy (dialogo);
                return;
            }

            g_error_free (errore);
            
            //**Alternativa, caricamento direttamente da file
            //gtk_image_set_from_file ((GTK_IMAGE(window->image), filename);
            
            //******************************************************************
            //*** CARICAMENTO DEI NODI DELLA MAPPA (.MAP) **********************
            //******************************************************************
            window->massimo_numero_nodi = carica_mappa(filename);
            //******************************************************************

            DBG(cout<<"Sto per chiamare le librerie CAIRO\n")
            cairo_disegna(immagine_mappa);


            //mappa_caricata= true;
            g_signal_handler_unblock( window->calcola_i, window->calcola_id );
            g_signal_handler_block( window->calcola_i, window->errore_id );
            delete[] filename;
        }
        default:
            gtk_widget_destroy (dialogo);
    }
    return;
}

/**
 * Se collegato ad un segnale "delete_event" impedisce che l'oggetto venga distrutto
 * @param oggetto : Puntatore all'oggetto che si tenta di distruggere
 * @return TRUE se l'oggetto non va distrutto, FALSE altrimenti.
 */
gboolean delete_event(GtkWidget* oggetto){
    DBG(cout<<"delete event occurred on Widget "<<oggetto<<endl)
    return TRUE;
}

/**
 * Mostra la finestra "informazioni".
 * @param finestra Il puntatore alla finestra principale.
 */
void mostra_info (GtkWidget* finestra){
    const gchar testo[]=
                    "Trovami la strada più corta\n"
                    "\n"
                    "Un programma creato dalla Badabing Inc.\n"
                    "Roberto Benfatto\t(Sten Gun)\n"
                    "Matteo De Carlo\t(Portaloffreedom)";


    GtkWidget* info = crea_finestra_info (finestra,testo);
//    gtk_show_about_dialog (NULL,
//                       "program-name", "ExampleCode",
//                       "logo",
//                       "title", "About ExampleCode",
//                       NULL,
//                       NULL);

    gtk_dialog_run (GTK_DIALOG (info));
    gtk_widget_destroy(info);
    return;
}

/**
 * Callback collegato ai pulsanti "radiobutton" per decidere se effettuare
 * la ricerca per distanza
 * @param dialogo Puntatore alla struct contenente i puntatori alla finestra di dialogo associata.
 */
void set_distanza (passaggio_t2 *dialogo){
    dialogo->t_calcolo = per_distanza;
}

/**
 * Callback collegato ai pulsanti "radiobutton" per decidere se effettuare
 * la ricerca per tempo
 * @param dialogo Puntatore alla struct contenente i puntatori alla finestra di dialogo associata.
 */
void set_tempo (passaggio_t2 *dialogo){
    dialogo->t_calcolo = per_tempo;
}

/**
 * Funzione chiamata dal menu "calcola percorso".
 * Mostra la finestra di dialogo per la scelta dei nodi di inizio e fine del percorso,
 * chiama la funzione ::djikstra con i nodi scelti e, TODO : se il percorso non esiste allora
 * lo segnala all'utente tramite una finestra di dialogo.
 * @param window Puntatore ad una struct contenente tutti i puntatori gtkwidget della finestra principale.
 */
void response_calcola (passaggio_t *window){
    passaggio_t2 *dialogo = crea_finestra_richiesta_percorso (window->finestra, window->massimo_numero_nodi);
    g_signal_connect_swapped (dialogo->radio_distanza, "clicked", G_CALLBACK(set_distanza), dialogo);
    g_signal_connect_swapped (dialogo->radio_tempo,    "clicked", G_CALLBACK(set_tempo),    dialogo);

    cairo_disegna(window->sfondo);
    switch (gtk_dialog_run (GTK_DIALOG (dialogo->finestra))) {

        case GTK_RESPONSE_ACCEPT: {
            gint nome_partenza = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(dialogo->partenza_t ));
            gint nome_arrivo = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(dialogo->arrivo_t ));
            DBG(cout<<"partenza: "<<nome_partenza<<endl)
            DBG(cout<<"arrivo:   "<<nome_arrivo  <<endl)

            DBG(cout<<"tipo di scelta: ";)
            switch (dialogo->t_calcolo){
                case per_tempo:
                    DBG(cout<<"per tempo\n";)
                    getPath(dijkstra(nome_partenza,nome_arrivo,leggi_peso_tempo));
                    cairo_disegna_percorso (window->sfondo);
                    gtk_image_set_from_pixbuf (GTK_IMAGE(window->image), window->sfondo);
                    break;
                case per_distanza:
                    DBG(cout<<"per distanza\n";)
                    getPath(dijkstra(nome_partenza,nome_arrivo,leggi_peso_km));
                    cairo_disegna_percorso (window->sfondo);
                    gtk_image_set_from_pixbuf (GTK_IMAGE(window->image), window->sfondo);
                    break;
                default:
                    cerr<<"Selta non inizializzata! O.o\n";
                    break;
            }
        }
        default:
            gtk_widget_destroy (dialogo->finestra);
            delete[] dialogo;
    }
    return;
}

/**
 * La funzione è legata al pulsante calcola quando non è stata caricata nessuna mappa.
 * @param finestra_principale Puntatore alla finestra principale
 */
void response_non_calcola (GtkWidget* finestra_principale){
    GtkWidget *dialogo = crea_finestra_non_carica(finestra_principale);
    gtk_dialog_run (GTK_DIALOG (dialogo));
    gtk_widget_destroy (dialogo);
    return;
}