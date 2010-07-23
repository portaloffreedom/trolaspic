/**
 * @file creazione_interfaccia.h Contiene l'interfaccia pubblica delle funzioni presenti nel file creazione_interfaccia.cpp
 *
 */

#ifndef CREAZIONE_INTERFACCIA_H
#define	CREAZIONE_INTERFACCIA_H

#include <gtk/gtk.h>
#include "main.h"
/** Crea la finestra principale con tutti gli oggetti
 *
 * @return una struttura contenente tutti i puntatoti ai GtkWidget da utlizzare
 * nel main (per collegare i segnali giusti).
 */
passaggio_t *crea_finestra_principale ();

/** Finestra di diaologo
 *
 * Funzione che crea la finestra di dialogo con due pulsanti (annulla, ok)
 * che sono già collegati associati ed un testo che prende come parametro in
 * entrata. Inoltre aggiunge sempre una immagine con punto interrogativo e il
 * label: Continua?
 * Non c'è neanche una g_signal_connect.
 * Non è ridimensionabile.
 *
 * @param GtkWidget* window: finestra da cui dipende
 * @param const gchar* testo: testo che deve esporre la finestra di dialogo
 * @return GtkWidget* : il puntatore alla finestra
 */
GtkWidget *crea_finestra_dialogo (GtkWidget* window, const gchar *testo);

/** Crea la finestra di dialogo contenente le info del programma
 *
 * @param GtkWidget* window: finestra da cui dipende
 * @param const gchar *testo: testo da mettere nell'info
 * @return Il Widget del dialogo
 */
GtkWidget *crea_finestra_info (GtkWidget* window, const gchar* testo);

/** Crea la finestra di dialogo per far partire la ricerca
 * \n da completare
 *
 * @param window 
 * @param limite_nodi
 * @return alcuni passaggi XD
 */
//passaggio_t2 *crea_finestra_richiesta_percorso (GtkWidget* window, int limite_nodi);

/** Crea la finestra che avvisa che avvisa che nessuna mappa è stata caricata
 *
 * @param finestra parent
 * @return puntatore al dialogo creato
 */
GtkWidget *crea_finestra_avviso(GtkWidget* parent, const gchar* testo);

#endif	/* CREAZIONE_INTERFACCIA_H */

