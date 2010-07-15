#include <gtk/gtk.h>
#include "main.h"

/* Backing pixmap for drawing area */
static GdkPixmap *pixmap = NULL;

/* Create a new backing pixmap of the appropriate size */
static gboolean configure_event( GtkWidget *widget, GdkEventConfigure *event ) {
  if (pixmap)
    g_object_unref(pixmap);

  pixmap = gdk_pixmap_new(widget->window,
			  widget->allocation.width,
			  widget->allocation.height,
			  -1);
  gdk_draw_rectangle (pixmap,
		      widget->style->white_gc,
		      TRUE,
		      0, 0,
		      widget->allocation.width,
		      widget->allocation.height);

  return TRUE;
}

/* Draw a rectangle on the screen */
static void draw_brush (GtkWidget *widget, gdouble x, gdouble y)
{
  GdkRectangle update_rect;

  update_rect.x = x - 5;
  update_rect.y = y - 5;
  update_rect.width = 10;
  update_rect.height = 10;
  gdk_draw_rectangle (pixmap,
  		      widget->style->black_gc,
  		      TRUE,
		      update_rect.x, update_rect.y,
		      update_rect.width, update_rect.height);
  gtk_widget_queue_draw_area (widget,
                              update_rect.x, update_rect.y,
		              update_rect.width, update_rect.height);
}

/* Redraw the screen from the backing pixmap */
static gboolean expose_event( GtkWidget *widget, GdkEventExpose *event ) {
  gdk_draw_drawable(widget->window,
		    widget->style->fg_gc[gtk_widget_get_state (widget)],
		    pixmap,
		    event->area.x, event->area.y,
		    event->area.x, event->area.y,
		    event->area.width, event->area.height);

  return FALSE;
}

gboolean button_press_event( GtkWidget *widget, GdkEventButton *event ) {
  if (event->button == 1 && pixmap != NULL)
      draw_brush (widget, event->x, event->y);

  return TRUE;
}

gboolean motion_notify_event( GtkWidget *widget, GdkEventMotion *event ) {
  int x, y;
  GdkModifierType state;

  if (event->is_hint)
    gdk_window_get_pointer (event->window, &x, &y, &state);
  else
    {
      x = event->x;
      y = event->y;
      //state = event->state;
    }

  if (state & GDK_BUTTON1_MASK && pixmap != NULL)
    draw_brush (widget, x, y);

  return TRUE;
}

void input_dialog_destroy (GtkWidget *w, gpointer data) {
  *((GtkWidget **)data) = NULL;
}

void create_input_dialog () {
  static GtkWidget *inputd = NULL;

  if (!inputd)
    {
      inputd = gtk_input_dialog_new();

      gtk_signal_connect (GTK_OBJECT(inputd), "destroy",
			  (GtkSignalFunc)input_dialog_destroy, &inputd);
      gtk_signal_connect_object (GTK_OBJECT(GTK_INPUT_DIALOG(inputd)->close_button),
				 "clicked",
				 (GtkSignalFunc)gtk_widget_hide,
				 GTK_OBJECT(inputd));
      gtk_widget_hide ( GTK_INPUT_DIALOG(inputd)->save_button);

      gtk_widget_show (inputd);
    }
  else
    {
      if (!gtk_widget_get_mapped(inputd))
	gtk_widget_show(inputd);
      else
	gdk_window_raise(inputd->window);
    }
}

GtkWidget *crea_drawing_area (int larghezza, int altezza){

    GtkWidget* area_disegno = gtk_drawing_area_new ();

    //da una dimensione alla drawing_area (widget, larghezza, altezza)
    gtk_drawing_area_size (GTK_DRAWING_AREA(area_disegno), larghezza, altezza);

    gtk_signal_connect (GTK_OBJECT (area_disegno), "expose_event",        (GtkSignalFunc) expose_event, NULL);
    gtk_signal_connect (GTK_OBJECT (area_disegno), "configure_event",     (GtkSignalFunc) configure_event, NULL);
    gtk_signal_connect (GTK_OBJECT (area_disegno), "motion_notify_event", (GtkSignalFunc) motion_notify_event, NULL);
    gtk_signal_connect (GTK_OBJECT (area_disegno), "button_press_event",  (GtkSignalFunc) button_press_event, NULL);



    return area_disegno;
}