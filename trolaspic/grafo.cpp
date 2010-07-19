#include "main.h"
#include "grafo.h"
#include <iostream>
#include <fstream>
#include <limits>
using namespace std;

nodo* GRAPH = 0;





const int MAX_LUNGH_STRINGA= 30;
const int MAX_SALTO= 500;

/** Serve per nascondere alla funzione i commenti nello stream
 *
 * @param stream sorgente da cui prelevare il carattere
 * @return l'intero prelevato dallo stream
 */
int leggi_prox_int(ifstream &source){
    int numero;
    char carattere;
    while (true)
    {
        source>>carattere;
        if (carattere=='#'){
            /*
            while (carattere!='\n'){
                source>>carattere;
                cout<<':'<<carattere
            }*/
            source.ignore(MAX_SALTO,'\n');
        }
        else {
        int posizione = source.tellg();
        source.seekg(--posizione);
        source>>numero;
        return  numero;
        }
    }
}
/** Serve per nascondere alla funzione i commenti nello stream
 *
 * @param stream sorgente da cui prelevare il carattere
 * @return il float prelevato dallo stream
 */
int leggi_prox_float(ifstream &source){
    float numero;
    char carattere;
    while (true)
    {
        source>>carattere;
        if (carattere=='#'){
            /*
            while (carattere!='\n'){
                source>>carattere;
                cout<<':'<<carattere
            }*/
            source.ignore(MAX_SALTO,'\n');
        }
        else {
        int posizione = source.tellg();
        source.seekg(--posizione);
        source>>numero;
        return  numero;
        }
    }
}

/** Serve per nascondere alla funzione i commenti nello stream
 *
 * @param stream sorgente da cui prelevare il carattere
 * @return il carattere prelevato dallo stream
 */
char leggi_prox_char(ifstream &source){
    char carattere;
    while (true)
    {
        source>>carattere;
        if (carattere=='#'){
            /*
            while (carattere!='\n'){
                source>>carattere;
                cout<<':'<<carattere
            }*/
            source.ignore(MAX_SALTO,'\n');
        }
        else return carattere;
    }
}

/** Serve per nascondere alla funzione i commenti nello stream
 *
 * @param stream sorgente da cui prelevare il carattere
 * @return il la stringa prelevata dallo stream
 */
char *leggi_prox_stringa(ifstream &source){
    char *stringa = new char[MAX_LUNGH_STRINGA];
    char carattere;
    while (true)
    {
        source>>carattere;
        if (carattere=='#'){
            /*
            while (carattere!='\n'){
                source>>carattere;
                cout<<':'<<carattere
            }*/
            source.ignore(MAX_SALTO,'\n');
        }
        else {
        int posizione = source.tellg();
        source.seekg(--posizione);
        source>>stringa;
        return  stringa;
        }
    }
}

/** Carica dal file .map e crea il grafo.
 * \n Elimina da solo la vecchia mappa se esistente.
 *
 * @param nome del file (trasforma da solo in .map)
 */
void carica_mappa(const char *filename)
{

    int i;
    for (i=0; filename[i]!='\0';i++) {
        //DBG(cout<<':'<<i<<'_'<<filename[i]<<endl)
    }
    DBG(cout<<endl)
    /*for (; filename[i]!='.'; i--){
        DBG(cout<<':'<<i<<'_'<<filename[i]<<endl)
    }*/

    char *filename_map= new char[i];
    filename_map[i--]='\0';
    filename_map[i--]='p';
    filename_map[i--]='a';
    filename_map[i--]='m';
    //filename_map[--i]='m';
    for (; i>=0;i--){
        filename_map[i]=filename[i];
    }
    DBG(cout<<filename<<endl);
    DBG(cout<<filename_map<<endl);



    ifstream mappa (filename_map);
    if (!mappa) {
        cerr<<"File "<<filename_map<<" non aperto correttamente\n";
        return;
    }
    
    //Distruggi l'array dei nodi precendente
    //distruggi_liste
    //delete[] GRAPH;

    const int numero_nodi = leggi_prox_int(mappa);
    GRAPH = new nodo[numero_nodi+1];

     for (int i=0; i<=12; i++){
        //Lettura del numero dell'incrocio
        int nome_incrocio= leggi_prox_int(mappa);
        //Lettura delle coordinate del nodo
        mappa.ignore(MAX_SALTO,'(');
        GRAPH[nome_incrocio].x= leggi_prox_int(mappa);
        GRAPH[nome_incrocio].y= leggi_prox_int(mappa);

        //Lettura del tipo di incrocio
        mappa.ignore(MAX_SALTO,')');
        char tipo_incrocio_char= leggi_prox_char(mappa);
        t_incrocio tipo_incrocio;
        switch (tipo_incrocio_char){
            case 's':
                tipo_incrocio= incrocio_semafori;
                break;
            case 'r':
                tipo_incrocio= rotatoria;
                break;
            default:
                cerr<<"\nErrore nella lettura del tipo di icrocio numero "<<nome_incrocio<<
                        "\nIncrocio settato come normale.\n";
            case 'n':
                tipo_incrocio= incrocio_normale;
        }
        GRAPH[nome_incrocio].tipo = tipo_incrocio;

        //--(lettura quanti archi collegati)--
        mappa.ignore(MAX_SALTO,':');
        const int quanti_archi= leggi_prox_int (mappa);
        GRAPH[nome_incrocio].size_list= quanti_archi;

        //lettura di tutte le adiacenze
        for (int i=0; i<quanti_archi; i++){
            mappa.ignore(MAX_SALTO,'(');
            int direzione_strada= leggi_prox_int(mappa);
            if (direzione_strada == 0)
                continue;
            
            arco arco;
            arco.nodo= direzione_strada;
            arco.kilometri= leggi_prox_float(mappa);
            arco.secondi  = leggi_prox_float(mappa);

            GRAPH[nome_incrocio].adiacente.push_back(arco);
            
        }
        mappa.ignore(MAX_SALTO,'$');

     }

    /*
    incrocio* lista_incroci= new incrocio[numero_nodi+1];

    for (int i=0; i<=numero_nodi; i++){

        //Lettura del numero dell'incrocio;
        int nome_incrocio= leggi_prox_int(mappa);

        //Lettura delle coordinate del nodo
        mappa.ignore(MAX_SALTO,'(');
        lista_incroci[nome_incrocio].x= leggi_prox_int(mappa);
        lista_incroci[nome_incrocio].y= leggi_prox_int(mappa);

        //Lettura del tipo di incrocio
        mappa.ignore(MAX_SALTO,')');
        char tipo_incrocio_char= leggi_prox_char(mappa);
        t_incrocio tipo_incrocio;
        switch (tipo_incrocio_char){
            case 's':
                tipo_incrocio= incrocio_semafori;
                break;
            case 'r':
                tipo_incrocio= rotatoria;
                break;
            default:
                cerr<<"\nErrore nella lettura del tipo di icrocio numero "<<nome_incrocio<<
                        "\nIncrocio settato come normale.\n";
            case 'n':
                tipo_incrocio= incrocio_normale;
        }
        lista_incroci[nome_incrocio].tipo_incrocio = tipo_incrocio;



        //--(lettura quanti archi collegati)--
        mappa.ignore(MAX_SALTO,':');
        const int quanti_archi= leggi_prox_int (mappa);
        lista_incroci[nome_incrocio].num_elem_lista= quanti_archi;
        //Lettura dei vari archi collegati
        lista_strade* lista_adiacenze= new lista_strade[quanti_archi];
        lista_incroci[nome_incrocio].elem_lista= lista_adiacenze;
        for (int i=0; i<quanti_archi;i++){
            lista_adiacenze[i].strada= new strade;
            mappa.ignore(MAX_SALTO,'(');
            int direzione_strada= leggi_prox_int(mappa);
            lista_adiacenze[i].strada->direzione= &lista_incroci[direzione_strada];
            mappa.ignore(MAX_SALTO,')');
        }

        //lista_incroci[nome_incrocio]
     *

    }*/


    delete[] filename_map;
    mappa.close();
}










#ifdef DEBUG_ROB0
const float INFINITO = numeric_limits<float>::max();

/**
 * @function preleva_nodo usa uno stream di input per leggere il nodo da inserire
 * nel grafo
 * @param file lo stream input da dove leggere le proprieta' del nodo
 * @param x riferimento dove scrivere la coordinata x del nodo
 * @param y riferimento dove scrivere la coordinata y del nodo
 * @return Restituisce -1 se non c'e' altro da prelevare, altrimenti da l'indice del nodo
 */
int preleva_nodo(ifstream &file,int &x,int &y){

};

/**
 * @function preleva_adiacenze viene usato per prendere le adiacenze di un nodo.
 * preleva sia le adiacenze che il loro peso relativo. In sostanza, prende tutti
 * i dati che servono per creare l'arco
 * @param file stream di input da dove leggere i dati.
 * @param peso passato per riferimento, scrive il peso dell'arco
 * @return restituisce il nodo adiacente, zero altrimenti.
 */
int preleva_adiacenze(ifstream &file,float &peso);

/**
 * @function aggiungi_adiacenza Viene usata per costruire un'adiacenza fra due nodi.
 * costruisce nella pratica un grafo orientato.
 * @param nod il nodo a cui dobbiamo aggiungere l'adiacenza
 * @param adj il nodo da aggiungere all'adiacenza del primo.
 * @param peso il peso associato all'arco
 */
void aggiungi_adiacenza(int nod,int adj,float peso){
    adiacenza* temp;
    temp = new adiacenza;
    temp->nodo = adj;
    temp->peso = peso;
    GRAPH[nod].adiacente.push_back(*temp);
};

/**
 * @function graph_builder Termina la costruzione del grafo inserendo tutti i
 * colori dei nodi come bianchi.
 */
void graph_builder(ifstream &file){
    int x = 0;
    int y = 0;
    int node = preleva_nodo(file,x,y);
    while(node > 0){
        GRAPH[node].x = x;
        GRAPH[node].y = y;
        GRAPH[node].visitato = bianco;
        GRAPH[node].padre = -1;
        GRAPH[node].peso = INFINITO;

        adiacenza adj;
        adj.nodo = preleva_adiacenze(file,adj.peso);
        while(adj.nodo > 0){
            GRAPH[node].adiacente.push_back(adj);
            adj.nodo = preleva_adiacenze(file,adj.peso);
        }
        node = preleva_nodo(file,x,y);
    }
};


/**
 * @function graph_loader Carica il grafo da file e lo costruisce per essere usato con dijkstra
 * @param widget Usato per le GTK
 * @param file Uno stream input da dove leggere i dati del grafo
 */
void graph_loader(GtkWidget* widget,ifstream &file){
    if(GRAPH != 0) delete[] GRAPH;
    int grandezza;
    //Preleva dal file la grandezza, crea con questa un grafo grande "grandezza + 1"
    // ....... inserire il codice qui
    GRAPH = new nodo[grandezza + 1];
    //scrivi la grandezza nella posizione 0, in x e y. Poni peso = 0
    // ..... inserire il codice qui
    graph_builder(file);
};
#endif