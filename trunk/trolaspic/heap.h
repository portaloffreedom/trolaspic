/* 
 * File:   heap.h
 * Author: stengun
 *
 * Created on 8 luglio 2010, 18.52
 */

#ifdef DEBUG_ROB

#ifndef HEAP_H
#define	HEAP_H
#include "main.h"
#include "priority_queue.h"

const int MAX_HEAP_DIM = 1024000;

#ifdef DEBUG
void stampaheap(CodaPriorita* Array);
#endif

void scambia(CodaPriorita* Array,int a, int b);
CodaPriorita parent(CodaPriorita i);
CodaPriorita left(CodaPriorita i);
CodaPriorita right(CodaPriorita i);
void min_heapify(CodaPriorita* Array,CodaPriorita i);
void build_min_heap(CodaPriorita* Array);
#endif	/* HEAP_H */

#endif