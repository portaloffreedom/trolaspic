/**
 * @file gestione_drawing_area.h Header contenente l'interfaccia pubblica delle funzioni CAIRO.
 * Referenzia tutte le funzioni pubbliche gestione_drawing_area.cpp
 *
 */

#ifndef GESTIONE_DRAWING_AREA_H
#define	GESTIONE_DRAWING_AREA_H

/** Funzione che carica dal grafo i nodi li disegna (assieme a tutti gli archi)
 * sopra al GdkPixbuf (che verrà caricato nella finestra principale). Utilizza
 * le librerie grafiche 2D cairo.
 * 
 * @param sfondo Buffer dell'immagine di fondo che deve essere modificata
 */
void cairo_disegna (GdkPixbuf* sfondo);
/** Funzione che prende il buffer dell'immagine della mappa e colora il percorso
 * da seguire di arancione.
 *
 * @param sfondo Buffer dell'immagine di fondo che deve essere modificata
 */
void cairo_disegna_percorso (GdkPixbuf* sfondo);

#endif	/* GESTIONE_DRAWING_AREA_H */

