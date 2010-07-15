/* 
 * File:   g_callback.h
 * Author: matteo
 *
 * Created on 8 luglio 2010, 19.00
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

#endif	/* G_CALLBACK_H */

