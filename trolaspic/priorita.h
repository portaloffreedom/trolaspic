/* 
 * File:   priorita.h
 * Author: matteo
 *
 * Created on 19 luglio 2010, 18.56
 */

#ifndef PRIORITA_H
#define	PRIORITA_H
typedef int nome_nodo;
struct elem_priorita {
    nome_nodo nodo;
    double peso;
};
typedef elem_priorita* coda_priorita;

/** Va chiamata per creare la coda di priorità
 *
 * @param dimensioni_max le dimensioni massime di elementi nella coda
 * @return la coda di priorità
 */
coda_priorita inizializza_coda (int dimensioni_max);

/** Estrae il valore minimo della coda (eliminato dalla coda)
 *
 * @param coda : la coda ritornata dall'inizializza_coda
 * @return l'elemento estratto
 */
elem_priorita estrai_minimo(coda_priorita coda);

/** Inserisce un elemento nella coda (non controlla se ci potrebbe essere overflow
 * ->causato da troppi elementi nella coda)
 *
 * @param coda : riferimento alla coda da utilizzare
 * @param peso : peso
 * @param nome_nodo :
 */
void inserisci(coda_priorita coda,double peso,nome_nodo nome_nodo);
/** Abbassa la priorità (verrà estratta prima) dell'elemento "nome_nodo" riassegnandogli
 * la chiave "nuovo_peso"
 *
 * @param coda sulla quale si vuole operare
 * @param nome_nodo che si vuole modificare
 * @param nuovo_peso che si vuole cambiare (deve essere per forza più basso del primo)
 * @return true-> operazione conclusa con successo / false-> operazione fallita
 */
bool cambia_chiave(coda_priorita coda, nome_nodo quale_nodo, double nuovo_peso);

/** Funzione per controllare se la funzione è vuota
 *
 * @param coda da esaminare
 * @return vero se vuota, falso se c'è almeno un elemento
 */
bool coda_vuota(coda_priorita coda);

/** Corrispettivo del decostruttore delle classi. Va chiamato per deallocare la
 * memoria occupata dalla coda.
 *
 * @param coda da eliminare
 */
void elimina_coda (coda_priorita coda);

#ifdef DEBUG
void stampaheap(elem_priorita* coda);
#endif

#endif	/* PRIORITA_H */

