/**
 * @file grafo.cpp Racchiude tutte le funzioni necessarie all'inizializzazione e alla gestione del
 * grafo.
 */


#include "main.h"
#include "grafo.h"
#include <iostream>
#include <fstream>
#include <limits>
using namespace std;
/**
 * La variabile GRAPH è globale, ed è il puntatore che viene usato per contenere l'indirizzo dell'array
 * dove viene memorizzato il grafo.
 * È stato scelto di usare una variabile globale perché esiste un solo grafo caricabile alla volta nel programma, che deve essere disponibile
 * per funzioni come il dijkstra.
 */
nodo* GRAPH = 0;

/**
 * Questa costante sancisce il massimo numero di caratteri che una stringa può contenere.
 */
const int MAX_LUNGH_STRINGA= 30;

/**
 * Questa costante stabilisce quanti caratteri possono esserci al massimo fra i delimitatori del file map.
 */
const int MAX_SALTO= 500;

/**
 * Costante per il massimo valore ammissibile da usare come "infinito" nel grafo.
 */
static const double INFINITO = numeric_limits<double>::max();

/** Distrugge il grafo e ne setta il puntatore a zero.
 * Questa funzione distrugge inoltre le liste di tutti i nodi del grafo,compresa la lista dei nodi della soluzione. */
void distruggi_grafo(){
    if(GRAPH == 0) return;
    int dim = dim_grafo();
    for(int i = dim;i>=0;i--){
        GRAPH[i].adiacente.clear();
    }
    delete[] GRAPH;
    GRAPH = 0;
};

/** Controlla quanto è grande il grafo.
 * @return Restituisce la dimensione del grafo */
int dim_grafo(void){
    return GRAPH[0].padre;
}

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
 * @return il double prelevato dallo stream
 */
double leggi_prox_double(ifstream &source){
    double numero;
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

/** Imposta i valori negli archi per la segmentazione degli archi leggendoli da file
 *
 * @param source sorgente da cui leggere
 * @param arco su cui scrivere
 * @param segmentazione tipo di segmentazione da caricare dal file
 */
void imposta_segmentazione (ifstream &source, arco &arco, tipo_segmentazione segmentazione){
    arco.segmentazione= segmentazione;
    arco.x1=leggi_prox_int(source);
    arco.y1=leggi_prox_int(source);
    arco.x2=leggi_prox_int(source);
    arco.y2=leggi_prox_int(source);

}

/** Dato un file immagine cerca il corrispettivo in .map e se lo trova carica la
 * mappa, altrimenti da errore. 
 * @param nome Il Nome del file da caricare.
 * @return 0 se non riesce a caricare la mappa, altrimenti restituisce il numero di nodi presenti nella mappa.
 * 
 */
int carica_mappa(const char *filename){

    //TRASFORMA IL FILENAME PER CARICARE IL .MAP********************************
    int i;
    for (i=0; filename[i]!='\0';i++);

    char filename_map[i];
    filename_map[i--]='\0';
    filename_map[i--]='p';
    filename_map[i--]='a';
    filename_map[i--]='m';
    for (; i>=0;i--){
        filename_map[i]=filename[i];
    }
    DBG(cout<<filename<<endl);
    DBG(cout<<filename_map<<endl);

    ifstream mappa (filename_map);
    if (!mappa) {
        cerr<<"File "<<filename_map<<" non aperto correttamente\n";
        return 0;
    }
    //**************************************************************************

    distruggi_grafo();
    
    //Distruggi l'array dei nodi precendente
    //distruggi_liste
    //delete[] GRAPH;

    const int dim_x = leggi_prox_int(mappa);
    mappa.ignore(MAX_SALTO,'x');
    const int dim_y = leggi_prox_int(mappa);

    const int numero_nodi = leggi_prox_int(mappa);
    GRAPH = new nodo[numero_nodi+1];
    GRAPH[0].padre = numero_nodi; //imposta le dimensioni del grafo.
                              //leggibile con la funzione "void dim_grafo(void)"
    GRAPH[0].x=dim_x;
    GRAPH[0].y=dim_y;

    DBG(cout<<"Nodo GRAPH[0] inizializzato con successo\n")

     for (int i=1; i<=numero_nodi; i++){
        //Lettura del numero dell'incrocio
        int nome_incrocio= leggi_prox_int(mappa);
        //Lettura delle coordinate del nodo
        mappa.ignore(MAX_SALTO,'(');
        GRAPH[nome_incrocio].x= leggi_prox_int(mappa);
        GRAPH[nome_incrocio].y= leggi_prox_int(mappa);
        GRAPH[nome_incrocio].padre = -1;
        GRAPH[nome_incrocio].visitato = bianco;
        GRAPH[nome_incrocio].peso = INFINITO;

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
                cerr<<"\nErrore nella lettura del tipo di incrocio numero "<<nome_incrocio<<
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
        for (int j=0; j<quanti_archi; j++){
            mappa.ignore(MAX_SALTO,'(');
            int direzione_strada= leggi_prox_int(mappa);
            if (direzione_strada == 0)
                continue;
            
            arco arco;
            arco.nodo= direzione_strada;
            arco.kilometri= leggi_prox_double(mappa);
            arco.secondi  = leggi_prox_double(mappa);

            //CARICAMENTO STRADE PARTICOLARI
            mappa.ignore(MAX_SALTO,')');

            char carattere_arco_speciale = leggi_prox_char(mappa);
            if (carattere_arco_speciale=='{'){
                switch(leggi_prox_char(mappa)){
                    case 'R':
                        imposta_segmentazione(mappa, arco, rette);
                        break;
                    case 'B':
                        imposta_segmentazione(mappa, arco, bezier);
                        break;
                    default:
                        cerr<<"Errore lettura segmentazione\n";
                        arco.segmentazione= nessuna;
                }
            }
            else {
                arco.segmentazione= nessuna;
            }

            //------------------------------

            GRAPH[nome_incrocio].adiacente.push_back(arco);
            
        }
        mappa.ignore(MAX_SALTO,'$');

     }

    
    mappa.close();
    return numero_nodi;
}