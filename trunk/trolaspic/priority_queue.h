/* 
 * File:   priority_queue.h
 * Author: stengun
 *
 * Created on 8 luglio 2010, 18.52
 */

#ifndef PRIORITY_QUEUE_H
#define	PRIORITY_QUEUE_H
#include "heap.h"

CodaPriorita* costrcoda(int grandezza);
CodaPriorita minimum(CodaPriorita* Array);
CodaPriorita extract_min(CodaPriorita* Array);
void decrease_key(CodaPriorita* Array,int i,CodaPriorita key);
void insert(CodaPriorita* Array,CodaPriorita key);

#endif	/* PRIORITY_QUEUE_H */

