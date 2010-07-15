/* 
 * File:   creazione_interfaccia.h
 * Author: matteo
 *
 * Created on 8 luglio 2010, 18.48
 */

#ifndef CREAZIONE_INTERFACCIA_H
#define	CREAZIONE_INTERFACCIA_H

#include <gtk/gtk.h>
#include "main.h"

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

GtkWidget *crea_finestra_info (GtkWidget* window, const gchar* testo);

#endif	/* CREAZIONE_INTERFACCIA_H */

