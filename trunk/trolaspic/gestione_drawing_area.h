/* 
 * File:   gestione_drawing_area.h
 * Author: matteo
 *
 * Created on 12 luglio 2010, 15.32
 */

#ifndef GESTIONE_DRAWING_AREA_H
#define	GESTIONE_DRAWING_AREA_H

//GtkWidget *crea_drawing_area (int larghezza, int altezza);
void cairo_disegna (GdkPixbuf* sfondo);
void cairo_disegna_percorso (GdkPixbuf* sfondo);

#endif	/* GESTIONE_DRAWING_AREA_H */
