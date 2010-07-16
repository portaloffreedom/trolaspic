#include <iostream>
#include <list>
#include <cmath>
#include "priority_queue.h"
#include "main.h"
using namespace std;

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
//  Iterazione per trovare il tragitto
//1  S := empty sequence
//2  u := target
//3  while previous[u] is defined:
//4      insert u at the beginning of S
//5      u := previous[u]

int* dijkstra();