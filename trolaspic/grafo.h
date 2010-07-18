/* 
 * File:   grafo.h
 * Author: stengun
 *
 * Created on 9 luglio 2010, 14.13
 */

#ifndef GRAFO_H
#define	GRAFO_H
#include <fstream>
#include "main.h"

using namespace std;
/** @param GRAFO Il grafo e' rappresentato come una lista di adiacenza.
 * nella posizione 0 viene inserita la grandezza dell'array che contiene il grafo
 * e precisamente nelle variabili x e y. peso viene posto a zero e la lista di adiacenza
 * non contiene nessun elemento.
 */

void graph_loader(GtkWidget* widget,ifstream &file);

#endif	/* GRAFO_H */

