/*
 * File:   main.cpp
 * Author: matteo
 *
 * Created on 6 luglio 2010, 17.16
 */

#include <cstdlib>
#include <iostream>
#include <gtk/gtk.h>
#include "procedura_installazione.h"
using namespace std;

#if DEBUG
#define DBG(A) {A;}
#define NDBG(B)
#else
#define DBG(A)
#define NDBG(B) {B;}
#endif

struct passaggio_t {
    GtkWidget* window;
    GtkWidget* barra1;
    GtkWidget* barra2;
    GtkWidget* scatola;
    GtkWidget* culo;
};


static gboolean delete_event()
{
    cout<<"delete event occurred\n";
    return TRUE;
}




void response_dialogo (GtkWidget *dialogo, gint response_id, passaggio_t *passaggio)
{
    DBG(cout<<"porco dio!!!!!!!!!!!!!!!\n";)
    switch (response_id){
        case GTK_RESPONSE_ACCEPT:
            DBG(cout<<"adesso vai avanti\n";)
            gtk_widget_hide(dialogo);

            /*
            gtk_widget_show_now(passaggio->culo);
            gtk_widget_show_now(passaggio->barra1);
            gtk_widget_show_now(passaggio->barra2);
            gtk_widget_show_now(passaggio->scatola);
             */
            gtk_widget_show_now(passaggio->window);
            //procedura_di_installazione(passaggio->barra1, passaggio->barra2);
            DBG(cout<<"procedura terminata correttamente\n")
            break;


        default:
            cerr<<"come cazzo hai fatto ad arrivare qui?????????????\n";
        case GTK_RESPONSE_REJECT:
            gtk_main_quit();
            break;
    }
}

/*
 *
 */
int main (int argc, char** argv)
{
    gtk_init (&argc, &argv);

    //--------------------------------------------------------------------------
    GtkWidget *window= gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Nautilus Elementary");
    g_signal_connect (window, "delete-event", G_CALLBACK (delete_event), NULL);

    GtkWidget *scatola= gtk_vbox_new(FALSE,0); //non omogeneo - spacing 0
    gtk_container_add (GTK_CONTAINER (window), scatola);


    GtkWidget *culo= gtk_label_new("Cosa stai facendo?? non riesci ancora ad installare u.u");
    GtkWidget *barra1= gtk_progress_bar_new();
    GtkWidget *barra2= gtk_progress_bar_new();

    gtk_box_pack_start (GTK_BOX(scatola), culo,   TRUE,  FALSE, 0);
    gtk_box_pack_start (GTK_BOX(scatola), barra1, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX(scatola), barra2, FALSE, FALSE, 0);

    /*
    gtk_widget_show_now(scatola);
    gtk_widget_show_now(culo);
    gtk_widget_show_now(barra1);
    gtk_widget_show_now(barra2);
     */


    passaggio_t *passaggio= new passaggio_t();
    passaggio->window=window;
    passaggio->scatola=scatola;
    passaggio->culo=culo;
    passaggio->barra1=barra1;
    passaggio->barra2=barra2;



    //--------------------------------------------------------------------------
    //creazione finestra di dialogo
    GtkWidget *dialogo= gtk_dialog_new_with_buttons ("Nautilus Elementary", NULL, GTK_DIALOG_MODAL, GTK_STOCK_CANCEL, GTK_RESPONSE_REJECT,GTK_STOCK_OK, GTK_RESPONSE_ACCEPT, NULL);

    GtkWidget *content_area= gtk_dialog_get_content_area(GTK_DIALOG(dialogo));
    g_signal_connect (dialogo, "response", G_CALLBACK(response_dialogo), passaggio);


    GtkWidget *scatola_dialogo_o = gtk_hbox_new(FALSE,15);
    gtk_container_add(GTK_CONTAINER(content_area), scatola_dialogo_o);

    GtkWidget *immagine = gtk_image_new_from_stock(GTK_STOCK_DIALOG_QUESTION, GTK_ICON_SIZE_DIALOG);
    gtk_box_pack_start (GTK_BOX(scatola_dialogo_o), immagine, TRUE, FALSE, 0);

    GtkWidget *scatola_dialogo_v = gtk_vbox_new(FALSE,5);
    gtk_box_pack_start (GTK_BOX(scatola_dialogo_o), scatola_dialogo_v, TRUE, FALSE, 0);

    const char avviso_t[]= "Vuoi installare Nautilus Elementary?\n"
                                "(serve una connessione ad internet per continuare)";
    GtkWidget *avviso= gtk_label_new(avviso_t);
    gtk_box_pack_start (GTK_BOX(scatola_dialogo_v), avviso, TRUE, FALSE, 3);

    GtkWidget *continua= gtk_label_new("Continua?");
    gtk_box_pack_start (GTK_BOX(scatola_dialogo_v), continua, TRUE, FALSE, 3);
    gtk_misc_set_alignment(GTK_MISC(continua), 0,0);


    gtk_window_set_resizable (GTK_WINDOW(dialogo), FALSE);

    gtk_widget_show_all(dialogo);
    //--------------------------------------------------------------------------


    g_signal_connect_after(window, "show",G_CALLBACK(procedura_di_installazione), passaggio);
    //--------------------------------------------------------------------------
    //g_signal_connect (dialogo, GTK_RESPONSE_ACCEPT, G_CALLBACK(ok_comincia), NULL);
    //g_signal_connect (dialogo, GTK_RESPONSE_REJECT, G_CALLBACK(gtk_main_quit), NULL);

    //creazione finestra di avanzamento






    //aggiornare repo
    //sudo add-apt-repository ppa:am-monkeyd/nautilus-elementary-ppa
    //sudo apt-get update && sudo apt-get upgrade


    //nautilus-q


    //cd #this should take you to your home folder
    //wget http://gnaag.k2city.eu/nautilus-breadcrumbs-hack.tar.gz
    //tar -xvf nautilus-breadcrumbs-hack.tar.gz

    //...

    gtk_main();
    return 0;
}

