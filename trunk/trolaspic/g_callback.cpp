#include <gtk/gtk.h>
#include <iostream>
#include <fstream>
#include "main.h"
#include "creazione_interfaccia.h"
#include "pathfinder.h"
#include "grafo.h"
using namespace std;


gboolean delete_event_window(GtkWidget* window, GdkEvent* evento,GtkWidget* dialogo)
{
    DBG(cout<<"delete event occurred on Widget "<<window<<endl)
    gtk_widget_show(dialogo);
    return TRUE;
}

void response_dialogo (GtkWidget* finestra)
{
    GtkWidget * dialogo= crea_finestra_dialogo (finestra,"Sei sicuro di volere uscire?");
    
    switch (gtk_dialog_run (GTK_DIALOG (dialogo))) {

        case GTK_RESPONSE_ACCEPT:
            gtk_main_quit();

        default:
            gtk_widget_destroy (dialogo);
    }
}

void response_carica (passaggio_t *window)
{
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

            GdkPixbuf *immagine_mappa= gdk_pixbuf_new_from_file (filename, NULL);
            gtk_image_set_from_pixbuf (GTK_IMAGE(window->image), immagine_mappa);
            
            //**Alternativa, caricamento direttamente da file
            //gtk_image_set_from_file ((GTK_IMAGE(window->image), filename);

            
            //******************************************************************
            //*** CARICAMENTO DEI NODI DELLA MAPPA (.MAP) **********************
            //******************************************************************
            window->massimo_numero_nodi = carica_mappa(filename);
            //******************************************************************

            gtk_statusbar_push( GTK_STATUSBAR(window->statusbar), window->statusbar_id, "mappa aperta con successo" );
            //mappa_caricata= true;
            g_signal_handler_unblock( window->calcola_i, window->calcola_id );
            g_signal_handler_block( window->calcola_i, window->errore_id );
            delete[] filename;
        }
        default:
            gtk_widget_destroy (dialogo);
    }
}


gboolean delete_event(GtkWidget* oggetto)
{
    DBG(cout<<"delete event occurred on Widget "<<oggetto<<endl)
    return TRUE;
}

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


void set_distanza (passaggio_t2 *dialogo){
    dialogo->t_calcolo = per_distanza;
}

void set_tempo (passaggio_t2 *dialogo){
    dialogo->t_calcolo = per_tempo;
}

void response_calcola (passaggio_t *window){
    passaggio_t2 *dialogo = crea_finestra_richiesta_percorso (window->finestra, window->massimo_numero_nodi);
    g_signal_connect_swapped (dialogo->radio_distanza, "clicked", G_CALLBACK(set_distanza), dialogo);
    g_signal_connect_swapped (dialogo->radio_tempo,    "clicked", G_CALLBACK(set_tempo), dialogo);

    switch (gtk_dialog_run (GTK_DIALOG (dialogo->finestra))) {

        case GTK_RESPONSE_ACCEPT: {
            gint nome_partenza = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(dialogo->partenza_t ));
            gint nome_arrivo = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(dialogo->arrivo_t ));
            DBG(cout<<"partenza: "<<nome_partenza<<endl)
            DBG(cout<<"arrivo:   "<<nome_arrivo  <<endl)

            cout<<"tipo di scelta: ";
            switch (dialogo->t_calcolo){
                case per_tempo:
                    DBG(cout<<"per tempo\n";)
                    getPath(dijkstra(nome_partenza,nome_arrivo,leggi_peso_tempo));
                    break;
                case per_distanza:
                    DBG(cout<<"per distanza\n";)
                    getPath(dijkstra(nome_partenza,nome_arrivo,leggi_peso_km));
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

void response_non_calcola (GtkWidget* finestra_principale){
    GtkWidget *dialogo = crea_finestra_non_carica(finestra_principale);
    gtk_dialog_run (GTK_DIALOG (dialogo));
    gtk_widget_destroy (dialogo);
    return;
}