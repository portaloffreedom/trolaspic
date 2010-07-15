/* 
 * File:   grafo.h
 * Author: stengun
 *
 * Created on 9 luglio 2010, 14.13
 */

#ifndef GRAFO_H
#define	GRAFO_H
enum tipo_nodo{ strada,
                incrocio,
                strada_senza_uscita,
                senso_unico,
                autostrada,
};

struct NodoMappa {
    int x;
    int y;
    tipo_nodo tipologia;
    float lunghezza;
    float vel_max;
};

#define GraphType NodoMappa

void Riempi_grafo();

#endif	/* GRAFO_H */

