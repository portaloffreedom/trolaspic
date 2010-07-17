#include <iostream>
#include <list>
#include <cmath>
#include <queue>
#include "main.h"
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
//  Iterazione per trovare il tragitto
//1  S := empty sequence
//2  u := target
//3  while previous[u] is defined:
//4      insert u at the beginning of S
//5      u := previous[u]
 *  */
#ifdef DEBUG_ROB
#define MAXINT (int)(pow(2,31)-1)
#define MAX 100


int graph[MAX][MAX];
int total;


int distances[MAX];
int father[MAX];
bool visit[MAX];

void dijkstra(int start)
{
  priority_queue<pair<int,int> > queue;
  pair <int,int> nodotmp;
  int i, j;

  for (int i=1; i<=total; i++) {
    distances[i] = MAXINT;
    father[i] = -1;
    visit[i] = false;
  }

  distances[start] = 0;
  queue.push(pair <int,int> (distances[start], start));

  while(!queue.empty()) {
    nodotmp = queue.top();
    queue.pop();
    i = nodotmp.second;
    if (!visit[i]) {
      visit[i] = true;
      for (j = 1; j<=total; j++)
        if (!visit[j] && graph[i][j] > 0 && distances[i] + graph[i][j] < distances[j]) {
          distances[j] = distances[i] + graph[i][j];
          father[j] = i;
          queue.push(pair <int,int>(-distances[j], j));
        }
    }
  }
}


void getPath(int end) {
  cout << end << " ";
  while (father[end]!= -1) {
    cout << father[end] << " ";
    end = father[end];
  }
  cout << endl;
}

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

   /*for (int i=1; i<=total; i++) {
     dijkstra(i);
     for(int i=1; i<=total; i++)
        cout << distances[i] << " ";
     cout << endl;
     for(int i=1; i<=total; i++)
        cout << father[i] << " ";
     cout << endl;
     getPath(5);
   }*/
   return 0;
}
#endif