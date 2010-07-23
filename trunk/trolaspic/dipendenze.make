creazione_interfaccia.o: creazione_interfaccia.cpp main.h \
 gestione_drawing_area.h
g_callback.o: g_callback.cpp main.h creazione_interfaccia.h \
 gestione_drawing_area.h pathfinder.h grafo.h
gestione_drawing_area.o: gestione_drawing_area.cpp main.h grafo.h pila.h
grafo.o: grafo.cpp main.h grafo.h
main.o: main.cpp main.h creazione_interfaccia.h gestione_drawing_area.h \
 g_callback.h
pathfinder.o: pathfinder.cpp pathfinder.h grafo.h main.h
pila.o: pila.cpp pila.h
