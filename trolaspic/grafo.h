/* 
 * File:   grafo.h
 * Author: stengun
 *
 * Created on 9 luglio 2010, 14.13
 */

#ifndef GRAFO_H
#define	GRAFO_H
struct adj_node {
  int node;
  float weight;
  struct adj_node* next;
};

#endif	/* GRAFO_H */

