#include <gtk/gtk.h>
#include <cairo/cairo.h>
#include <iostream>
#include <cmath>
#include "main.h"
#include "grafo.h"
#include "pila.h"

extern nodo* GRAPH;

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

    DBG(cout<<"stringa: "<<stringa<<endl)
    

    distruggi_pila_char(pila);
    return stringa;
}

void cairo_disegna (const gchar *filename){

    //**************************************************************************
    // IMPOSTO IL NOME DEL FILE COME *.png
    //**************************************************************************
    int i;
    for (i=0; filename[i]!='\0';i++) {
        //DBG(cout<<':'<<i<<'_'<<filename[i]<<endl)
    }
    DBG(cout<<endl)

    char *filename_png= new char[i];
    filename_png[i--]='\0';
    filename_png[i--]='g';
    filename_png[i--]='n';
    filename_png[i--]='p';
    //filename_map[--i]='m';
    for (; i>=0;i--){
        filename_png[i]=filename[i];
    }
    DBG(cout<<filename<<endl);
    DBG(cout<<filename_png<<endl);

    //**************************************************************************
    //Crep la superficie di lavoro
    DBG(cout<<"Prova a disegnare con CAIRO\n");
    cairo_surface_t *superficie = cairo_image_surface_create_from_png(filename_png);
    cairo_t *cr = cairo_create(superficie);
    double X = GRAPH[0].x;
    double Y = GRAPH[0].y;
    cairo_scale (cr, GRAPH[0].x, GRAPH[0].y);

    //Imposto il colore del pennello, larghezza delle linee
    cairo_set_source_rgb (cr, 1, 1, 0); //giallo
    cairo_set_line_width (cr, 0.015);

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

            GRAPH[i].adiacente.push_back(adiacente);
            //- FINE ESTRAZIONE ------------------------------------------------

            //fai la linea fino all'adiacenza
            cairo_line_to(cr, coo_adiacenza_x, coo_adiacenza_y);
            //spara il disegno
            cairo_stroke(cr);
        }
    }

    //Settaggio dimensione, colore e tipo dei font
    cairo_set_font_size (cr, 0.05);
    cairo_set_source_rgb (cr, 1, 0.5, 0.0); //arancio
    cairo_select_font_face (cr, "Georgia", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);

    //Parte da inserire per stampare il nome del nodo
    for (int i=1; i<=dim_grafo(); i++){

        double coo_x = GRAPH[i].x/X;
        double coo_y = GRAPH[i].y/Y;
             
        cairo_move_to(cr, coo_x, coo_y);
        cairo_show_text(cr, get_text_from_int(i));
    }



    //STAMPA SU FILE E DISTRUGGI
    cairo_surface_write_to_png (superficie, "prova.png");
    cairo_destroy (cr);
    cairo_surface_destroy(superficie);
    DBG(cout<<"Fine disegno con CAIRO\n");

    return;
}