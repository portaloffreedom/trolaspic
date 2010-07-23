/**
 * @file g_callback.cpp Contiene tutte le funzioni da associare agli eventi.
 */

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

/** Mostra una finestra di avviso con il testo scelto
 *
 * @param finestra_principale puntatore alla finestra principale
 * @param testo testo che deve mostrare la finestra di avviso
 */
void finestra_di_avviso (GtkWidget* finestra_principale, const gchar *testo){
    GtkWidget *dialogo = crea_finestra_avviso(finestra_principale,testo);
    gtk_dialog_run (GTK_DIALOG (dialogo));
    gtk_widget_destroy (dialogo);
    return;
}

/** Mostra la barra inferiore dove immettere il percorso da calcolare
 *
 * @param window struttura dei puntatori di tutte le cose utili
 */
void mostra_calcola_percorso (passaggio_t *window){
    gtk_widget_show(window->domanda_calcola);
    gtk_widget_show(window->scatola_calcola);
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
            //*** CONTROLLO CHE IL FILE DA CARICARE SIA IN PNG *****************
            //******************************************************************
            int i;
            bool errore_png =false;
            for (i=0; filename[i]!='\0';i++);
            if (filename[--i]!= 'g') errore_png= true;
            if (filename[--i]!= 'n') errore_png= true;
            if (filename[--i]!= 'p') errore_png= true;

            if (errore_png){
                finestra_di_avviso(dialogo,"Solo i file *.png sono validi" );
                delete[] filename;
                gtk_widget_destroy (dialogo);
                return;
            }
            //******************************************************************
            //*** CARICAMENTO DEI NODI DELLA MAPPA (.MAP) **********************
            //******************************************************************
            window->massimo_numero_nodi = carica_mappa(filename);
            if (window->massimo_numero_nodi == 0){
                finestra_di_avviso(dialogo,"Errore nel caricamento della mappa!\n"
                        "prova a caricare il file giusto\n" );
                delete[] filename;
                gtk_widget_destroy (dialogo);
                return;
            }

            //******************************************************************
            //*** CARICAMENTO DELL'IMMAGINE DELLA MAPPA ************************
            //******************************************************************

            GError *errore = NULL;
            GdkPixbuf *immagine_mappa= gdk_pixbuf_new_from_file (filename, &errore);
            if (errore != NULL){
                const char ERRORE[]="Errore nel caricamento dell'immagine!\n"
                        "prova a caricare il file giusto\n";
                cerr<<ERRORE<<endl;
                finestra_di_avviso(dialogo,ERRORE );
                delete[] filename;
                gtk_widget_destroy (dialogo);
                return;
            }
            if (errore!=0) gdk_pixbuf_unref (window->sfondo);

            gtk_spin_button_set_range(GTK_SPIN_BUTTON(window->spin_partenza), 1, dim_grafo());
            gtk_spin_button_set_range(GTK_SPIN_BUTTON(window->spin_arrivo)  , 1, dim_grafo());
            mostra_calcola_percorso(window);
           


            window->sfondo = immagine_mappa;
            if (errore!=0) g_error_free (errore);
            
            DBG(cout<<"Sto per chiamare le librerie CAIRO\n")
            cairo_disegna(immagine_mappa);
            
            gtk_image_set_from_pixbuf (GTK_IMAGE(window->image), immagine_mappa);


            delete[] filename;
        }
        default:
            gtk_widget_destroy (dialogo);
    }
    return;
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
void set_distanza (passaggio_t *dialogo){
    dialogo->t_calcolo = per_distanza;
}

/**
 * Callback collegato ai pulsanti "radiobutton" per decidere se effettuare
 * la ricerca per tempo
 * @param dialogo Puntatore alla struct contenente i puntatori alla finestra di dialogo associata.
 */
void set_tempo (passaggio_t *dialogo){
    dialogo->t_calcolo = per_tempo;
}

/** Funzione che calcola il percorso dato un inizio e una fine e ne disegna il
 * tracciato sulla mappa
 *
 * @param window struttura contenente i puntatori ai widget della finestra principale
 * @param dialogo puntatore alla finestra di dialogo per il calcolo del percorso
 * @param nome_partenza nome del nodo di partenza
 * @param nome_arrivo nome del nodo di arrivo
 * @param leggi_peso funzione con cui prelevare il peso dagli archi
 */
void calcola_percorso (passaggio_t *window, GtkWidget* dialogo, int nome_partenza, int nome_arrivo, double leggi_peso(arco)){
    if (nome_arrivo == nome_partenza){
        finestra_di_avviso (dialogo, "I punti di inizio e di arrivo sono uguali");
        return;
    }
    int end = dijkstra(nome_partenza,nome_arrivo,leggi_peso);
    getPath(end);
    if (end == nome_partenza){
        finestra_di_avviso (dialogo, "Non è possibile trovare un percorso tra questi punti");
        return;
    }
    cairo_disegna_percorso (window->sfondo);
    gtk_image_set_from_pixbuf (GTK_IMAGE(window->image), window->sfondo);
    return;
}

/**
 * Funzione chiamata dal menu "calcola percorso".
 * Mostra la finestra di dialogo per la scelta dei nodi di inizio e fine del percorso,
 * chiama la funzione ::djikstra con i nodi scelti e, TODO : se il percorso non esiste allora
 * lo segnala all'utente tramite una finestra di dialogo.
 * @param window Puntatore ad una struct contenente tutti i puntatori gtkwidget della finestra principale.
 */
void response_calcola (passaggio_t *window){

   

    cairo_disegna(window->sfondo);

    gint nome_partenza = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(window->spin_partenza ));
    gint nome_arrivo =   gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(window->spin_arrivo   ));
    DBG(cout<<"partenza: "<<nome_partenza<<endl)
    DBG(cout<<"arrivo:   "<<nome_arrivo  <<endl)

    DBG(cout<<"tipo di scelta: ";)
    switch (window->t_calcolo){
        case per_tempo:
            calcola_percorso (window, window->finestra, nome_partenza,nome_arrivo, leggi_peso_tempo);
            break;
        case per_distanza:
            calcola_percorso (window, window->finestra, nome_partenza,nome_arrivo, leggi_peso_km);
            break;
        default:
            cerr<<"Scelta non inizializzata! O.o\n";
            break;
    }
    return;
}