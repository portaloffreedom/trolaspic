#include <iostream>
#include <list>
#include <cmath>
#include "priority_queue.h"
#include "grafo.h"
using namespace std;

float StimaDistanza(NodoMappa now,NodoMappa &nodeGoal )
{
	float xd = fabs(float(((float)now.x - (float)nodeGoal.x)));
	float yd = fabs(float(((float)now.y - (float)nodeGoal.y)));

	return xd + yd;
}

CodaPriorita* Cerca_Percorso(CodaPriorita inizio,CodaPriorita fine){
    
};