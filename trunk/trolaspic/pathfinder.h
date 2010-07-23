/**
 * @file pathfinder.h
 * Header contenente l'interfaccia alle funzioni contenute in pathfinder.cpp.
 * Questo header viene incluso per abilitare l'utilizzo di dijkstra.
 * @author Roberto
 */

#ifndef PATHFINDER_H
#define	PATHFINDER_H

#include "grafo.h"

double leggi_peso_tempo(arco arco);
double leggi_peso_km(arco arco);
void getPath(int end);
int dijkstra(const int start,const int fine,double leggi_peso_arco(arco arco));


#endif	/* PATHFINDER_H */

