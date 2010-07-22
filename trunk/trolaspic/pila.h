/* 
 * File:   pila.h
 * Author: matteo
 *
 * Created on 22 luglio 2010, 12.21
 */

#ifndef PILA_H
#define	PILA_H

struct pila_ch{
    char* pila;
    int ultimo_elem;
};
typedef pila_ch* pila_char;

/** Costruttore per la pila
 *
 * @param max_elem massimo numero di elementi da inserire nella pila
 * @return l'"oggetto" pila
 */
pila_char crea_pila_char(int max_elem);
/** Decostruttore per la pila
 *
 * @param pila "oggetto" da distruggere
 */
void distruggi_pila_char(pila_char pila);

/** Pusha un carattere dentro alla pila (attenzione, non ci sono controlli se viene superata la dimensione massima della pila)
 *
 * @param pila pila su cui si lavora
 * @param carattere elemento da pushare
 */
void push_pila_char(pila_char pila, char carattere);
/** Poppa un elemento dalla pila (Attenzione non fa controlli se vengono poppati più elemnti di quanti ce ne siano)
 *
 * @param pila pila su cui lavorare
 * @return carattere estratto dalla pila
 */
char pop_pila_char(pila_char pila);

#endif	/* PILA_H */

