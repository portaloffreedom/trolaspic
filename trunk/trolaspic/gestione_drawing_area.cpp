/**
 * @file gestione_drawing_area.cpp Modulo per usare le funzioni delle librerie CAIRO.
 *
 */

#include <gtk/gtk.h>
#include <cairo/cairo.h>
#include <iostream>
#include <cmath>
#include "main.h"
#include "grafo.h"
#include "pila.h"

extern nodo* GRAPH;
/**Costante che definisce lo spessore delle linee disegnate da cairo*/
static const double DIM_LINEE = 0.013;
/**Costante che definisce la dimensione dei font disegnati da cairo*/
static const double DIM_FONT  = 0.03;

/** Funzione che trasforma un intero (di massimo 5 cifre) in una stringa di caratteri
 * attenzione! la stringa è allocata in maniera dinamica, quindi bisogna deallocarla dopo avere utilizzato questa funzione
 *
 * @param numero
 * @return
 */
char *get_text_from_int(int numero){
    int i;
    pila_char pila = crea_pila_char(6);
    char* stringa = new char[6];

    for (i=0; i<6 && numero!=0; i++){
        push_pila_char(pila, static_cast<char>('0'+(numero%10)));
        numero/=10;
    }
    stringa[i]='\0';
    for (int j=0; j<i; j++){
        stringa[j]=pop_pila_char(pila);
    }
    

    distruggi_pila_char(pila);
    return stringa;
}

void cairo_disegna (GdkPixbuf *sfondo){

    //Crep la superficie di lavoro
    DBG(cout<<"Prova a disegnare con CAIRO\n");
    //cairo_surface_t *superficie = cairo_image_surface_create_from_png(filename_png);
    cairo_surface_t *superficie = cairo_image_surface_create_for_data(gdk_pixbuf_get_pixels(sfondo), CAIRO_FORMAT_RGB24, GRAPH[0].x, GRAPH[0].y, gdk_pixbuf_get_rowstride(sfondo));
    cairo_t *cr = cairo_create(superficie);
    double X = GRAPH[0].x;
    double Y = GRAPH[0].y;
    cairo_scale (cr, GRAPH[0].x, GRAPH[0].y);

    //Imposto il colore del pennello, larghezza delle linee
    cairo_set_source_rgb (cr, 0, 1, 1); //giallo
    cairo_set_line_width (cr, DIM_LINEE);

    //Ciclo per tutti i nodi
    for (int i=1; i<=dim_grafo(); i++){

        //coordinate del nodo in analisi formulate in "precentuale"
        double coo_x = GRAPH[i].x/X;
        double coo_y = GRAPH[i].y/Y;

        //Disegna un Cerchiolino attorno al punto
        //(disegna un arco da 0 a 2pi_greco e lo riempie)
        cairo_arc (cr,coo_x,coo_y,0.015,0,M_PI*2);
        cairo_fill (cr);



        
        for (int j=0; j<GRAPH[i].size_list; j++){
            //muoviti nelle coordinate del punto da analizzare
            cairo_move_to(cr, coo_x, coo_y);


            //ESTRAI LE COORDINATE DELL'ADIACENZA-------------------------------
            adiacenza adiacente = GRAPH[i].adiacente.front();
            GRAPH[i].adiacente.pop_front();
            
            double coo_adiacenza_x = GRAPH[adiacente.nodo].x/X;
            double coo_adiacenza_y = GRAPH[adiacente.nodo].y/Y;
            double x1 = adiacente.x1/X;
            double y1 = adiacente.y1/Y;
            double x2 = adiacente.x2/X;
            double y2 = adiacente.y2/Y;

           
            //- FINE ESTRAZIONE ------------------------------------------------

            //fai la linea fino all'adiacenza
            switch (adiacente.segmentazione){
                case bezier:
                    cairo_curve_to(cr, x1, y1, x2, y2, coo_adiacenza_x, coo_adiacenza_y);
                    break;
                case rette:
                    cairo_line_to(cr, x1, y1);
                    cairo_line_to(cr, x2, y2);
                case nessuna:
                    cairo_line_to(cr, coo_adiacenza_x, coo_adiacenza_y);
                    break;
                default:
                    cerr<<"lettura tipo di segmentazione del nodo "<<i
                            <<"verso il nodo "<<adiacente.nodo<<" non corretta, settata su normale\n";
                    cairo_line_to(cr, coo_adiacenza_x, coo_adiacenza_y);
                    break;

            }
            //spara il disegno
            cairo_stroke(cr);
            GRAPH[i].adiacente.push_back(adiacente);
        }
    }

    //Settaggio dimensione, colore e tipo dei font
    cairo_set_font_size (cr, DIM_FONT);
    cairo_set_source_rgb (cr, 1, 0.5, 0.0); //light blue
    cairo_select_font_face (cr, "Georgia", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);

    //Parte da inserire per stampare il nome del nodo
    for (int i=1; i<=dim_grafo(); i++){

        double coo_x = (GRAPH[i].x/X)-0.01;
        double coo_y = (GRAPH[i].y/Y);
             
        cairo_move_to(cr, coo_x, coo_y);
        cairo_show_text(cr, get_text_from_int(i));
    }



    //STAMPA SU FILE E DISTRUGGI
    //cairo_surface_write_to_png (superficie, "prova.png");
    cairo_destroy (cr);
    cairo_surface_destroy(superficie);
    DBG(cout<<"Fine disegno con CAIRO\n");

    return;
}

void cairo_disegna_percorso (GdkPixbuf* sfondo){
    cairo_surface_t *superficie = cairo_image_surface_create_for_data(gdk_pixbuf_get_pixels(sfondo), CAIRO_FORMAT_RGB24, GRAPH[0].x, GRAPH[0].y, gdk_pixbuf_get_rowstride(sfondo));
    cairo_t *cr = cairo_create(superficie);
    double X = GRAPH[0].x;
    double Y = GRAPH[0].y;
    cairo_scale (cr, GRAPH[0].x, GRAPH[0].y);

    //Imposta larghezza linee
    cairo_set_line_width (cr, DIM_LINEE);
    //Settaggio dimensione e tipo dei font
    cairo_set_font_size (cr, DIM_FONT);
    cairo_select_font_face (cr, "Georgia", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    int prec=0;


    for (int i=GRAPH[0].size_list; i>0 ;i--){

        adiacenza nodo = GRAPH[0].adiacente.front();
        GRAPH[0].adiacente.pop_front();

        //GRAPH[0].size_list--;

        //coordinate del nodo in analisi formulate in "precentuale"
        double coo_x = GRAPH[nodo.nodo].x/X;
        double coo_y = GRAPH[nodo.nodo].y/Y;

        //Disegna un Cerchiolino attorno al punto
        //(disegna un arco da 0 a 2pi_greco e lo riempie)
        cairo_set_source_rgb (cr, 0, 0.5, 1); //light blue
        cairo_arc (cr,coo_x,coo_y,0.015,0,M_PI*2);
        cairo_fill (cr);


        if (i!=1){
            adiacenza successivo = GRAPH[0].adiacente.front();
            adiacenza arco_successivo = GRAPH[nodo.nodo].adiacente.front();

            while (arco_successivo.nodo != successivo.nodo){
                GRAPH[nodo.nodo].adiacente.pop_front();
                GRAPH[nodo.nodo].adiacente.push_back(arco_successivo);
                arco_successivo = GRAPH[nodo.nodo].adiacente.front();
            }

            double coo_x_succ = GRAPH[arco_successivo.nodo].x/X;
            double coo_y_succ = GRAPH[arco_successivo.nodo].y/Y;

            double x1 = arco_successivo.x1/X;
            double y1 = arco_successivo.y1/Y;
            double x2 = arco_successivo.x2/X;
            double y2 = arco_successivo.y2/Y;

            cairo_move_to(cr, coo_x, coo_y);


            switch (arco_successivo.segmentazione){
                case bezier:
                    cairo_curve_to(cr, x1, y1, x2, y2, coo_x_succ, coo_y_succ);
                    break;
                case rette:
                    cairo_line_to(cr, x1, y1);
                    cairo_line_to(cr, x2, y2);
                case nessuna:
                    cairo_line_to(cr, coo_x_succ, coo_y_succ);
                    break;
                default:
                    cerr<<"lettura tipo di segmentazione del nodo "<<i
                            <<"verso il nodo "<<arco_successivo.nodo<<" non corretta, settata su normale\n";
                    cairo_line_to(cr, coo_x_succ, coo_y_succ);
                    break;

            }
            cairo_stroke(cr);
        }

        cairo_set_source_rgb (cr, 1, 0.5, 0.0); //light blue
        cairo_move_to(cr, coo_x-0.01, coo_y);
        cairo_show_text(cr, get_text_from_int(nodo.nodo));


    }
    
    GRAPH[0].size_list=0;

}