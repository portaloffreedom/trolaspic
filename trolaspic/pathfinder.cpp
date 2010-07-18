#include <iostream>
#include <cmath>
#include <queue>
#include <algorithm>
#include "grafo.h"
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

#ifdef DEBUG_ROB

/**
 * @function Algoritmo Dijkstra modificato per trovare la strada minima fra
 * due punti di un grafo orientato.
 * @param start : Nodo da cui vogliamo iniziare la ricerca
 * @param fine : Nodo a cui vogliamo arrivare partendo da Start.
 */
int dijkstra(const int start,const int fine)
{
  priority_queue<pair<float,int> > queue; // Crea una coda di paia nodo/peso
  pair <float,int> nodotmp;   //crea una variabile temporanea di tipo nodo/peso.
                            //accessibili con nodotmp.first e nodotmp.second
  int indexnode, j, temp; //contatori??
  float temppeso;
//  /* Questo for e' inutile visto che tutto viene fatto quando e' inizializzato il grafo*/
//  for (int i=1; i<=total; i++) {
//    distances[i] = MAXINT;
//    father[i] = -1;
//    visit[i] = false;
//  }                             // DEPRECATED

  GRAFO[start]->peso = 0;

  /* Inserisco nella coda il nodo di inizio e il suo peso*/
  queue.push(pair <float,int> (GRAFO[start]->peso/* il peso del nodo*/, start /* il nodo da cui partire*/));

  adiacenza* templist;
  /* Finche' la coda e' piena processo tutti i nodi adiacenti a questo*/
  while(!queue.empty())
  {
    nodotmp = queue.top(); // Prelevo il nodo dalla coda (sono sicuro che non e' vuota)
    queue.pop();

    if(indexnode == fine) return fine;
    indexnode = nodotmp.second; //l'indice del nodo
    if (!(GRAFO[indexnode]->visitato == bianco))
    {    //se il nodo non e' stato visitato
      GRAFO[indexnode]->visitato = nero;  //marcalo come visitato
      templist = GRAFO[indexnode]->adiacente.begin();
      for (j = 0; j<GRAFO[indexnode]->adiacente.size(); j++)
      {    //per ogni vicino che non e' stato visitato inseriscilo nella coda
          // Salvo il nodo e il peso
          temp = (templist + j)->nodo;
          temppeso = (templist + j)->peso;

          if        (!( GRAFO[temp]->visitato == bianco)
                        && temppeso > 0
                        && GRAFO[indexnode]->peso + temppeso < GRAFO[temp]->peso)
          {
            GRAFO[temp]->peso = GRAFO[indexnode]->peso + temppeso; // Aggiorna il peso del nodo
            GRAFO[temp]->padre = indexnode;    // aggiorna il padre del nodo
            queue.push(pair <float,int>(-GRAFO[temp]->peso, temp)); //aggiungilo alla coda
          }
      }

    }

  }
  return start;
}

// Ricostruisci il tragitto inizio/fine partendo dalla fine
// Il nuovo concetto sara' quello di creare una lista di nodi che formano il tragitto cosi'
// da poter ricaricare il grafo e tenere quindi i nodi trovati.
void getPath(int end) {
  cout << end << " "; // DEPRECATED
  while (GRAFO[end]->padre > -1) { //quando trovi il nodo senza padre hai trovato l'inizio
    cout << GRAFO[end]->padre << " "; // DEPRECATED (solo debug serve)
    end = GRAFO[end]->padre; // end adesso e' il padre del vecchio end (cioe' del nodo precedente)
  }
  cout << endl; // DEPRECATED (solo per debug serve)
}

/*
int main()
{
   int a, b, c;
   int tedges;
   memset(graph, 0, sizeof(graph));
   cin >> total >> tedges;
   for (int i=0; i<tedges; i++) {
     cin >> a >> b >> c;
     graph[a][b] = c;
   }
   for(int i=1; i<=total; i++) {
      for(int j=1; j<=total; j++)
         printf("%d ", graph[i][j]);
      printf("\n");
   }
   dijkstra(1);
   getPath(3);

//   for (int i=1; i<=total; i++) {
//     dijkstra(i);
//     for(int i=1; i<=total; i++)
//        cout << distances[i] << " ";
//     cout << endl;
//     for(int i=1; i<=total; i++)
//        cout << father[i] << " ";
//     cout << endl;
//     getPath(5);
//   }
   return 0;
}*/

#endif