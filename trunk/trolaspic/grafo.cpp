#include "grafo.h"
#include <iostream>
using namespace std;

#include <fstream>
#include <stdlib.h>

using namespace std;

const int white = 0;
const int gray = 1;
const int black = 2;

struct adj_node **G;

/* La struttura dati (array) p serve nell'implementazione
   delle due funzioni fisrt_neighbor e next_neighbor. Ogni singola posizione
   p[u] "conserva" memoria del nodo restuito dalla chiamata precedente.
   Si tratta di una delle tante possibili implementazioni. */

struct adj_node **p;

/* first_neighbor(u,w) inizia la scansione della lista di adiacenza del
 * nodo u, restituendo il nodo (che per il chiamante è semplicemente
 * un numero intero) che rappresenta il primo vicino di u. */

int first_neighbor(int node, float &w) {
  if (G[node] == 0) return 0;
  p[node] = G[node];
  w = G[node]->weight;
  return G[node]->node;
}

/* next_neighbor(u,w) deve essere chiamata dopo first_neighbor(u,w). Restituisce
 * ad ogni chiamata il vicino successivo di u nella lista di adiacenza. */

int next_neighbor(int node, float &w) {
  p[node] = p[node]->next;  //MODIFICA ALLA STRUTTURA G??
  if (p[node] == 0) return 0;
  w = p[node]->weight;
  return p[node]->node;
}

/* Funzione che aggiunge l'arco orientato (u,v) alla lista di adiacenza del
 * nodo u (aggiunge in testa alla lista). L'arco ha peso w. */

void add_arc(int u, int v, float w) {
  struct adj_node* t = new adj_node;
  t->node = v;
  t->weight = w;
  t->next = G[u];
  G[u] = t;
}

/* Funzione che aggiunge l'arco non orientato (u,v) alle liste
 * di adiacenza di u e v. */
void add_edge(int u, int v, float w) {
  add_arc(u,v,w);
  add_arc(v,u,w);
}

/* Funzione che costruisce la rappresentazione mediante liste di
 * adiacenza di un grafo non orientato letto da file. Se il
 * parametro weighted e' presente ed e' diverso da 0 il grafo e'
 * pesato ed il file deve specificare, oltre alla coppia di nodi,
 * anche il peso del relativo arco. */

int g_build(ifstream &g, void add(int a, int b, float w), int weighted = 1) {
  int n;
  g >> n;  //leggo il numero di nodi
  G = new adj_node*[n+1];
  p = new adj_node*[n+1];
  for (int i=1; i<=n; i++) {
    G[i] = 0;  //indicazione di fine lista
  }
  int v1,v2;
  if (weighted) {
    float w;
    while (g >> v1 >> v2 >> w) {
      add(v1,v2,w);
     }
  } else {
    while (g >> v1 >> v2) {
      add(v1,v2,1.0);
    }
  }
  return n;
}

/* Interfaccia per la funzione g_build. Costruisce un grafo non
   orientato, la cui descrizione e' letta da file.
*/
int graph(ifstream &g, int weighted) {
  return g_build(g,add_edge,weighted);
}

/* Interfaccia per la funzione g_build. Costruisce un grafo
   orientato, la cui descrizione e' letta da file.
*/
int digraph(ifstream &g, int weighted = 1) {
  return g_build(g,add_arc,weighted);
}

