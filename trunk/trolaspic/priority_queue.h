/* 
 * File:   priority_queue.h
 * Author: stengun
 *
 * Created on 8 luglio 2010, 18.52
 */

#ifndef PRIORITY_QUEUE_H
#define	PRIORITY_QUEUE_H
#include "heap.h"
#include "main.h"

#ifdef DEBUG_ROB0
enum stato_t {  inizio,
                visitato,
                fine,
                non_visitato
};

struct elemento_coda{
    stato_t stato;
    incrocio* nodografo;
    int h_score;
    int g_score;
    int f_score;
};

typedef nodo CodaPriorita;

CodaPriorita* costrcoda(int grandezza);
CodaPriorita minimum(CodaPriorita* Array);
CodaPriorita extract_min(CodaPriorita* Array);
void decrease_key(CodaPriorita* Array,int i,CodaPriorita key);
void insert(CodaPriorita* Array,CodaPriorita key);
#endif

#endif	/* PRIORITY_QUEUE_H */

