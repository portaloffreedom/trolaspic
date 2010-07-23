/**
 * @file pila.h Interfaccia del modulo della pila (stack) di char
 *
 * @author: matteo
 *
 */

#ifndef PILA_H
#define	PILA_H

/** Struct che è utilizzata come contenitore della pila */
struct pila_ch{
    /** Puntatore ad un array di caratteri (l'array è effettivamente la pila) */
    char* pila;
    /** Variabile che memorizza quanto la pila sia realmente occupata */
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

