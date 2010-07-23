/**
 * @file g_callback.h Contiene le funzioni pubbliche per il file g_callback.cpp
 */

#ifndef G_CALLBACK_H
#define	G_CALLBACK_H

#include <gtk/gtk.h>
#include "main.h"

gboolean delete_event_window(GtkWidget* window, GdkEvent* evento ,GtkWidget* dialogo);
gboolean delete_event(GtkWidget* oggetto);
void response_dialogo (GtkWidget *finestra);
void response_carica (passaggio_t *window);
void mostra_info (GtkWidget* finestra);
void response_calcola (passaggio_t *window);
void set_tempo (passaggio_t *dialogo);
void set_distanza (passaggio_t *dialogo);

#endif	/* G_CALLBACK_H */

