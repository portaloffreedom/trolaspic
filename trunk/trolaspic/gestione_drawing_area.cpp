#include <gtk/gtk.h>
#include <cairo/cairo.h>
#include <iostream>
#include "main.h"
#include "grafo.h"

extern nodo* GRAPH;

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
    DBG(cout<<filename_map<<endl);

    //**************************************************************************

    DBG(cout<<"Prova a disegnare con CAIRO\n");
    cairo_surface_t *superfice = cairo_image_surface_create_from_png(filename_png);
    cairo_t *cr = cairo_create(superfice);

    cairo_scale (cr, GRAPH[0].x, GRAPH[0].y);

    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_move_to(cr, 0,0);
    cairo_line_to(cr, 1,1);
    cairo_move_to(cr, 1,0);
    cairo_line_to(cr, 0,1);
    cairo_set_line_width (cr, 0.02);
    cairo_stroke(cr);

    cairo_surface_write_to_png (superfice, "prova.png");
    cairo_destroy (cr);
    cairo_surface_destroy(superfice);
    DBG(cout<<"Fine disegno con CAIRO\n");

    return;
}