#include <gtk/gtk.h>
#include <iostream>
#include <fstream>
#include "main.h"
#include "creazione_interfaccia.h"
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

            carica_mappa(filename);

            //******************************************************************

            gtk_statusbar_push( GTK_STATUSBAR(window->statusbar), window->statusbar_id, "mappa aperta con successo" );
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

void mostra_info (GtkWidget* finestra)
{
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