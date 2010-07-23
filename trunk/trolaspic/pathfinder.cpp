/**
 * @file pathfinder.cpp Contiene tutte le funzioni che servono per trovare la strada più corta
 * fra un punto di inizio e uno di fine. Implementa Dijkstra con la funzione ::dijkstra e
 * ricostruisce il cammino usando ::endPath.
 * @author Roberto
 */

#include <iostream>
#include "pathfinder.h"
#include <limits>
#include <queue>
using namespace std;


extern nodo* GRAPH;
static const double INFINITO = numeric_limits<double>::max();

/** Resetta il grafo con i valori standard. 
 * Viene chiamata da ::dijkstra e da ::endPath dopo aver trovato il percorso da seguire
 */
void reset_graph(void){
    for(int i=1;i<=dim_grafo();i++){
        GRAPH[i].padre = -1;
        GRAPH[i].visitato = bianco;
        GRAPH[i].peso = INFINITO;
    }
};


/** Dato un arco, restituisce i suoi kilometri.
 * La funzione è di appoggio a ::dijkstra e viene usata solo da passare
 * come parametro puntatore a una funzione.
 * @param arco : l'arco di cui leggere i kilometri
 */
double leggi_peso_km(arco arco){
    return arco.kilometri;
};

/** Dato un arco, restituisce il tempo che occore per percorrerlo.
 * La funzione è di appoggio a ::dijkstra e viene usata solo da passare
 * come parametro puntatore a una funzione.
 * @param arco : l'arco di cui leggere il tempo
 */
double leggi_peso_tempo(arco arco){
    return arco.secondi;
};

/**
 * Algoritmo Dijkstra modificato per trovare la strada minima fra
 * \n due punti di un grafo orientato.
 * @param start : Nodo da cui vogliamo iniziare la ricerca
 * @param fine : Nodo a cui vogliamo arrivare partendo da Start.
 * @param leggi_peso_arco : La funzione da usare per prelevare il peso di un arco.
 * \n e' necessario per la differenza del percorso calcolato in base al tempo o alla distanza
 *
 * @return Ritorna il nodo finale se il grafo ha trovato la strada con successo
 * \n altrimenti restituisce il nodo iniziale
 */

int dijkstra(const int start,const int fine,double leggi_peso_arco(arco arco))
{
    priority_queue<pair<double,int> > queue;
    pair <double,int> nodotmp;

  int indexnode;

  GRAPH[start].peso = 0;
  GRAPH[start].visitato = grigio;
  /* Inserisco nella coda il nodo di inizio e il suo peso*/
  queue.push(pair<double,int>(GRAPH[start].peso/* il peso del nodo*/, start /* il nodo da cui partire*/));

  adiacenza templist;
  /* Finche' la coda e' piena processo tutti i nodi adiacenti a questo
   * che hanno la priorita' maggiore */
  while(!queue.empty())
  {
    nodotmp = queue.top(); // Prelevo il nodo dalla coda (sono sicuro che non e' vuota)
    queue.pop();
    if(nodotmp.second == 0) return start;
    indexnode = nodotmp.second; //l'indice del nodo
    if(indexnode == fine){

        return fine; //altri controlli
    }
    //-------
    if (GRAPH[indexnode].visitato == grigio)
    {    //se il nodo non e' stato visitato mai
      GRAPH[indexnode].visitato = nero;  //marcalo come visitato

      for (int j = 1; j<=GRAPH[indexnode].size_list; j++)
      {    //per ogni vicino che non e' stato visitato inseriscilo nella coda
          // Salvo il nodo e il peso
      templist = GRAPH[indexnode].adiacente.front();
      GRAPH[indexnode].adiacente.pop_front();
          if        (!( GRAPH[templist.nodo].visitato == nero)
                        && (leggi_peso_arco(templist) > 0.00000001)
                        && (GRAPH[indexnode].peso + leggi_peso_arco(templist)) < GRAPH[templist.nodo].peso)
          {

            GRAPH[templist.nodo].peso = GRAPH[indexnode].peso + leggi_peso_arco(templist); // Aggiorna il peso del nodo
            GRAPH[templist.nodo].padre = indexnode;    // aggiorna il padre del nodo
            //il peso lo metto in negativo perche' questa e' una coda di max priorita'
                GRAPH[templist.nodo].visitato = grigio;
                queue.push(pair<double,int>(-GRAPH[templist.nodo].peso, templist.nodo)); //aggiungilo alla coda

          }
          GRAPH[indexnode].adiacente.push_back(templist);
      }
    }
  }
  reset_graph();
  return start;
}

/** Ricostruisci il tragitto inizio/fine.
 * Crea una lista dei nodi trovati dentro GRAPH[0].adiacenza.
 * 
 * @param end Dato un nodo, segue tutti i suoi parent fino ad arrivare al nodo start.
 */
void getPath(int end) {
    GRAPH[0].size_list = 0;
    if(!GRAPH[0].adiacente.empty()) GRAPH[0].adiacente.clear();
    cout << end << " "; // DEPRECATED
    adiacenza temp;
    temp.nodo = end;
    while (GRAPH[temp.nodo].padre != -1) { //quando trovi il nodo senza padre hai trovato l'inizio
        cout << GRAPH[temp.nodo].padre << " "; // DEPRECATED (solo debug serve)
        GRAPH[0].adiacente.push_front(temp);
        GRAPH[0].size_list++;
        temp.nodo = GRAPH[temp.nodo].padre; // end adesso e' il padre del vecchio end (cioe' del nodo precedente)
    }
    GRAPH[0].adiacente.push_front(temp);
    GRAPH[0].size_list++;
    cout << endl; // DEPRECATED (solo per debug serve)
reset_graph();
}
