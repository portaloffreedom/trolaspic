#include <iostream>
#include "pathfinder.h"
#include <limits>
using namespace std;
/*
//Usa l'algoritmo di Dijkstra per trovare la distanza.

// 1  function Dijkstra(Graph, source):
// 2      for each vertex v in Graph:           // Initializations
// 3          dist[v] := infinity               // Unknown distance function from source to v
// 4          previous[v] := undefined          // Previous node in optimal path from source
// 5      dist[source] := 0                     // Distance from source to source
// 6      Q := the set of all nodes in Graph
//        S := empty sequence
//        // All nodes in the graph are unoptimized - thus are in Q
// 7      while Q is not empty:                 // The main loop
// 8          u := vertex in Q with smallest dist[]
//            if u := target:
                  //3  while previous[u] is defined:
                  //4      insert u at the beginning of S
                  //5      u := previous[u]
                  //   break
// 9          if dist[u] = infinity:            // non ho trovato un tragitto da inizio e fine
//10              break                         // all remaining vertices are inaccessible from source
//11          remove u from Q
//12          for each neighbor v of u:         // where v has not yet been removed from Q.
//13              alt := dist[u] + dist_between(u, v)
//14              if alt < dist[v]:             // Relax (u,v,a)
//15                  dist[v] := alt
//16                  previous[v] := u
//17      return S
 *
//  Iterazione per trovare il tragitto
//1  S := empty sequence
//2  u := target
//3  while previous[u] is defined:
//4      insert u at the beginning of S
//5      u := previous[u]
 *  */

static const double INFINITO = numeric_limits<double>::max();
extern nodo* GRAPH;

#ifdef DEBUG_ROB

void reset_graph(void){
    for(int i=1;i<=GRAPH[0].x;i++){
        GRAPH[i].padre = -1;
        GRAPH[i].visitato = bianco;
        GRAPH[i].peso = INFINITO;
    }
};

double leggi_peso_km(arco arco){
    return arco.kilometri;
};

double leggi_peso_tempo(arco arco){
    return arco.secondi;
};

/**
 * @function Algoritmo Dijkstra modificato per trovare la strada minima fra
 * due punti di un grafo orientato.
 * @param start : Nodo da cui vogliamo iniziare la ricerca
 * @param fine : Nodo a cui vogliamo arrivare partendo da Start.
 */

int dijkstra(const int start,const int fine,double leggi_peso_arco(arco arco))
{
  coda_priorita queue; // Crea una coda di paia nodo/peso
  queue = inizializza_coda(dim_grafo());
  elem_priorita nodotmp;   //crea una variabile temporanea di tipo nodo/peso.
                            //accessibili con nodotmp.first e nodotmp.second
  int indexnode;
//  /* Questo for e' inutile visto che tutto viene fatto quando e' inizializzato il grafo*/
//  for (int i=1; i<=total; i++) {
//    distances[i] = MAXINT;
//    father[i] = -1;
//    visit[i] = false;
//  }                             // DEPRECATED
  
  GRAPH[start].peso = 0;
  GRAPH[start].visitato = grigio;
  /* Inserisco nella coda il nodo di inizio e il suo peso*/
  inserisci(queue,GRAPH[start].peso/* il peso del nodo*/, start /* il nodo da cui partire*/);

  adiacenza templist;
  /* Finche' la coda e' piena processo tutti i nodi adiacenti a questo
   * che hanno la priorita' maggiore */
  while(!coda_vuota(queue))
  {
    nodotmp = estrai_minimo(queue); // Prelevo il nodo dalla coda (sono sicuro che non e' vuota)
    if(nodotmp.nodo == 0) return start;
    indexnode = nodotmp.nodo; //l'indice del nodo
    if(indexnode == fine){
        
        return fine; //altri controlli
    }
    //-------
    if (GRAPH[indexnode].visitato != nero)
    {    //se il nodo non e' stato visitato mai
      GRAPH[indexnode].visitato = nero;  //marcalo come visitato

      for (int j = 0; j<GRAPH[indexnode].size_list; j++)
      {    //per ogni vicino che non e' stato visitato inseriscilo nella coda
          // Salvo il nodo e il peso
      templist = GRAPH[indexnode].adiacente.front();
      GRAPH[indexnode].adiacente.pop_front();
          if        (!( GRAPH[templist.nodo].visitato == nero)
                        && (leggi_peso_arco(templist) > 0)
                        && (GRAPH[indexnode].peso + leggi_peso_arco(templist)) < GRAPH[templist.nodo].peso)
          {

            GRAPH[templist.nodo].peso = GRAPH[indexnode].peso + leggi_peso_arco(templist); // Aggiorna il peso del nodo
            GRAPH[templist.nodo].padre = indexnode;    // aggiorna il padre del nodo
            //il peso lo metto in negativo perche' questa e' una coda di max priorita'
            if( GRAPH[templist.nodo].visitato == grigio )
                cambia_chiave(queue,templist.nodo,GRAPH[templist.nodo].peso);
            else{
                GRAPH[templist.nodo].visitato = grigio;
                inserisci(queue,GRAPH[templist.nodo].peso, templist.nodo); //aggiungilo alla coda
            }
            
          }
          GRAPH[indexnode].adiacente.push_back(templist);
      }

    }

  }
  elimina_coda(queue);
  return start;
}

// Ricostruisci il tragitto inizio/fine partendo dalla fine
// Il nuovo concetto sara' quello di creare una lista di nodi che formano il tragitto cosi'
// da poter ricaricare il grafo e tenere quindi i nodi trovati.
void getPath(int end) {
  cout << end << " "; // DEPRECATED
  while (GRAPH[end].padre != -1) { //quando trovi il nodo senza padre hai trovato l'inizio
    cout << GRAPH[end].padre << " "; // DEPRECATED (solo debug serve)
    end = GRAPH[end].padre; // end adesso e' il padre del vecchio end (cioe' del nodo precedente)
  }
  cout << endl; // DEPRECATED (solo per debug serve)
  reset_graph();
}
#endif