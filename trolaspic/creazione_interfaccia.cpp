#include <iostream>
#include <fstream>
#include <gtk/gtk.h>
#include "main.h"
//#include "g_callback.h"
#include "gestione_drawing_area.h"
using namespace std;


passaggio_t *crea_finestra_principale (){
    GtkWidget *window=  gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "TROLASPIC");
    gtk_window_set_position (GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_icon_from_file (GTK_WINDOW(window), PERCORSO"/ContainerRed-icon_piccola.png", NULL);

    GtkWidget *scatola1= gtk_vbox_new(FALSE,0);
    gtk_container_add (GTK_CONTAINER (window), scatola1);

    //creazione dei menu *******************************************************
    GtkWidget *barra_menu= gtk_menu_bar_new();
    gtk_box_pack_start(GTK_BOX(scatola1),barra_menu, FALSE, FALSE, 0);
    GtkWidget *programma_barra = gtk_menu_item_new_with_label("Programma");
    GtkWidget *mappa_barra     = gtk_menu_item_new_with_label("Mappa");
    GtkWidget *percorso_barra  = gtk_menu_item_new_with_label("Percorso");

    gtk_menu_shell_append (GTK_MENU_SHELL (barra_menu), programma_barra);
    gtk_menu_shell_append (GTK_MENU_SHELL (barra_menu), mappa_barra);
    gtk_menu_shell_append (GTK_MENU_SHELL (barra_menu), percorso_barra);

    gtk_widget_show(programma_barra);
    gtk_widget_show(mappa_barra);
    gtk_widget_show(percorso_barra);
    gtk_widget_show(barra_menu);

    GtkWidget *programma_menu = gtk_menu_new ();
    GtkWidget *mappa_menu     = gtk_menu_new ();
    GtkWidget *percorso_menu  = gtk_menu_new ();

    gtk_menu_item_set_submenu (GTK_MENU_ITEM (programma_barra), programma_menu);
    gtk_menu_item_set_submenu (GTK_MENU_ITEM (mappa_barra), mappa_menu);
    gtk_menu_item_set_submenu (GTK_MENU_ITEM (percorso_barra), percorso_menu);

    //menu: Programma *** -> programma_menu
    GtkWidget *info_item = gtk_menu_item_new_with_label("Info");
    gtk_menu_shell_append (GTK_MENU_SHELL (programma_menu), info_item);
    gtk_widget_show(info_item);
    GtkWidget *esci_item = gtk_menu_item_new_with_label("Esci");
    gtk_menu_shell_append (GTK_MENU_SHELL (programma_menu), esci_item);
    gtk_widget_show(esci_item);
    
    //menu: Mappa *** -> mappa_menu
    GtkWidget *carica_item = gtk_menu_item_new_with_label("Carica Mappa");
    gtk_menu_shell_append (GTK_MENU_SHELL (mappa_menu), carica_item);
    gtk_widget_show(carica_item);

    //menu: Percorso *** -> percorso_menu
    GtkWidget *calcola_item = gtk_menu_item_new_with_label("Calcola Percorso");
    gtk_menu_shell_append (GTK_MENU_SHELL (percorso_menu), calcola_item);
    gtk_widget_show(calcola_item);


    GtkWidget* Image= gtk_image_new();  //_from_file("/home/matteo/NetBeansProjects/trolaspic~subversion/trolaspic/modena.png");
    gtk_box_pack_start (GTK_BOX(scatola1),Image, TRUE, TRUE, 0);
    gtk_widget_show(Image);


    //**************************************************************************
    //**** THE DRAWING AREA ****************************************************
    //**************************************************************************

    /*
    GtkWidget *disegno = crea_drawing_area (500, 100);
    gtk_box_pack_start (GTK_BOX(scatola1),disegno, TRUE, TRUE, 0);

    gtk_widget_show(disegno);*/
    //**************************************************************************



    gtk_widget_show(scatola1);
    gtk_window_set_default_size (GTK_WINDOW(window),500,300);


    passaggio_t* ritorno= new passaggio_t;
    ritorno->finestra = window;
    ritorno->info_i= info_item;
    ritorno->esci_i = esci_item;
    ritorno->carica_i = carica_item;
    ritorno->calcola_i = calcola_item;
    ritorno->image = Image;
//    ritorno->radio_distanza = ;
//    ritorno->radio_tempo    = ;
    return ritorno;
}

/** Finestra di diaologo
 * 
 * @param window: finestra da cui dipende
 * @param testo: testo che deve esporre la finestra di dialogo
 * @return il puntatore alla finestra
 */
GtkWidget *crea_finestra_dialogo (GtkWidget* window, const gchar* testo){
    GtkWidget *dialogo= gtk_dialog_new_with_buttons ("Sicuro?", GTK_WINDOW(window),
                GTK_DIALOG_MODAL,
                    GTK_STOCK_CANCEL, GTK_RESPONSE_REJECT,GTK_STOCK_OK, GTK_RESPONSE_ACCEPT, NULL);

    GtkWidget *content_area= gtk_dialog_get_content_area(GTK_DIALOG(dialogo));


    GtkWidget *scatola_dialogo_o = gtk_hbox_new(FALSE,15);
    gtk_container_add(GTK_CONTAINER(content_area), scatola_dialogo_o);

    GtkWidget *immagine = gtk_image_new_from_stock(GTK_STOCK_DIALOG_QUESTION, GTK_ICON_SIZE_DIALOG);
    gtk_box_pack_start (GTK_BOX(scatola_dialogo_o), immagine, TRUE, FALSE, 0);

    GtkWidget *scatola_dialogo_v = gtk_vbox_new(FALSE,5);
    gtk_box_pack_start (GTK_BOX(scatola_dialogo_o), scatola_dialogo_v, TRUE, FALSE, 0);

    
    GtkWidget *avviso= gtk_label_new(testo);
    gtk_box_pack_start (GTK_BOX(scatola_dialogo_v), avviso, TRUE, FALSE, 3);

    GtkWidget *continua= gtk_label_new("Continua?");
    gtk_box_pack_start (GTK_BOX(scatola_dialogo_v), continua, TRUE, FALSE, 3);
    gtk_misc_set_alignment(GTK_MISC(continua), 0,0);


    gtk_window_set_resizable (GTK_WINDOW(dialogo), FALSE);

    gtk_widget_show_all(dialogo);

    return dialogo;
}

GtkWidget *crea_finestra_info (GtkWidget* window, const gchar* testo){
    GtkWidget *info = gtk_about_dialog_new ();

    GdkPixbuf *logo_programma= gdk_pixbuf_new_from_file (PERCORSO"/ContainerRed-icon.png", NULL);

    gtk_about_dialog_set_name         (GTK_ABOUT_DIALOG(info), "info");
    gtk_about_dialog_set_program_name (GTK_ABOUT_DIALOG(info), "Trolaspic");
    gtk_about_dialog_set_logo         (GTK_ABOUT_DIALOG(info), logo_programma);
    gtk_about_dialog_set_version      (GTK_ABOUT_DIALOG(info), VERSION);
    gtk_about_dialog_set_comments     (GTK_ABOUT_DIALOG(info), testo);

    return info;
}

passaggio_t2 *crea_finestra_richiesta_percorso (GtkWidget* window, int limite_nodi){
        GtkWidget *dialogo= gtk_dialog_new_with_buttons ("Percorso", GTK_WINDOW(window),
                GTK_DIALOG_MODAL,
                    GTK_STOCK_CANCEL, GTK_RESPONSE_REJECT,GTK_STOCK_OK, GTK_RESPONSE_ACCEPT, NULL);

    GtkWidget *content_area= gtk_dialog_get_content_area(GTK_DIALOG(dialogo));


    GtkWidget *scatola_dialogo_v = gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(content_area), scatola_dialogo_v);

    GtkWidget *titolo= gtk_label_new("Quale Percorso vuoi fare?");
    gtk_box_pack_start (GTK_BOX(scatola_dialogo_v), titolo, TRUE, TRUE, 0);

    //creazione scatola per richiesta partenza
    GtkWidget *scatola_partenza = gtk_hbox_new(FALSE,11);
    gtk_box_pack_start (GTK_BOX(scatola_dialogo_v), scatola_partenza, TRUE, TRUE, 5);

    GtkWidget *label_partenza= gtk_label_new("Partenza");
    gtk_box_pack_start (GTK_BOX(scatola_partenza), label_partenza, FALSE, FALSE, 0);

    GtkObject *partenza_spin_adjustament = gtk_adjustment_new(
                                                1, //gdouble value,
                                                1, //gdouble lower,
                                                static_cast<gdouble>(limite_nodi),
                                                1,
                                                5,
                                                NULL );
    GtkWidget *partenza_SpinButton = gtk_spin_button_new( GTK_ADJUSTMENT(partenza_spin_adjustament), 0,0 );
    gtk_box_pack_start (GTK_BOX(scatola_partenza), partenza_SpinButton, TRUE, TRUE, 0);

    //creazione scatola per richiesta arrivo
    GtkWidget *scatola_arrivo   = gtk_hbox_new(FALSE,30);
    gtk_box_pack_start (GTK_BOX(scatola_dialogo_v), scatola_arrivo  , TRUE, TRUE, 5);
    
    GtkWidget *label_arrivo= gtk_label_new("Arrivo");
    gtk_box_pack_start (GTK_BOX(scatola_arrivo)  , label_arrivo  , FALSE, FALSE, 0);

    GtkObject *arrivo_spin_adjustament = gtk_adjustment_new(
                                                1, //gdouble value,
                                                1, //gdouble lower,
                                                static_cast<gdouble>(limite_nodi),
                                                1,
                                                5,
                                                NULL );
    GtkWidget *arrivo_SpinButton = gtk_spin_button_new( GTK_ADJUSTMENT(arrivo_spin_adjustament), 0,0 );
    gtk_box_pack_start (GTK_BOX(scatola_arrivo)  , arrivo_SpinButton  , TRUE, TRUE, 0);


    //--------------------------------------------------------------------------

    GtkWidget *label_radio = gtk_label_new("Quale Percorso vuoi fare?");
    gtk_box_pack_start (GTK_BOX(scatola_dialogo_v), label_radio  , TRUE, TRUE, 0);


    GtkWidget *scatola_radio_button   = gtk_hbox_new(FALSE,10);
    gtk_box_pack_start (GTK_BOX(scatola_dialogo_v), scatola_radio_button  , TRUE, TRUE, 5);

    GtkWidget *r_button_distanza = gtk_radio_button_new_with_label (NULL, "Distanza");
    gtk_box_pack_start (GTK_BOX(scatola_radio_button), r_button_distanza  , TRUE, TRUE, 0);
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON (r_button_distanza),true );

    GtkWidget *r_button_tempo = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (r_button_distanza),"Tempo");
    gtk_box_pack_start (GTK_BOX(scatola_radio_button), r_button_tempo  , TRUE, TRUE, 0);


    //--------------------------------------------------------------------------






    //--------------------------------------------------------------------------

    gtk_window_set_resizable (GTK_WINDOW(dialogo), FALSE);

    gtk_widget_show(scatola_dialogo_v);
    gtk_widget_show(titolo);
    gtk_widget_show(scatola_partenza);
    gtk_widget_show(label_partenza);
    gtk_widget_show(partenza_SpinButton);
    gtk_widget_show(scatola_arrivo);
    gtk_widget_show(label_arrivo);
    gtk_widget_show(arrivo_SpinButton);
    gtk_widget_show(label_radio);
    gtk_widget_show(scatola_radio_button);
    gtk_widget_show(r_button_distanza);
    gtk_widget_show(r_button_tempo);

    passaggio_t2 *passaggio = new passaggio_t2 ;
    passaggio-> finestra       = dialogo;
    passaggio-> partenza_t     = partenza_SpinButton;
    passaggio-> arrivo_t       = arrivo_SpinButton;
    passaggio-> radio_distanza = r_button_distanza;
    passaggio-> radio_tempo    = r_button_tempo;
    passaggio-> t_calcolo      = per_distanza;

    return passaggio;
}

GtkWidget *crea_finestra_avviso(GtkWidget* parent, const gchar* testo){

    GtkWidget* dialogo = gtk_message_dialog_new (GTK_WINDOW(parent),
                                                 GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_OK,
                                                 "ATTENZIONE!", NULL);
    gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialogo),
            testo, NULL);

    return dialogo;
}
