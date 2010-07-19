/* 
 * File:   priorita.h
 * Author: matteo
 *
 * Created on 19 luglio 2010, 18.56
 */

#ifndef PRIORITA_H
#define	PRIORITA_H

struct elem_priorita {
    int posizione;
    float peso;
    elem_priorita* S_figlio;
    elem_priorita* D_figlio;
    elem_priorita* padre;
};

elem_priorita estrai_minimo(elem_priorita* &coda);
elem_priorita inserisci(elem_priorita* &coda, float peso, int direzione);
elem_priorita cambia_chiave(elem_priorita* &coda);


#endif	/* PRIORITA_H */

