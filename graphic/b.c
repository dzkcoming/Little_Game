#include <gtk/gtk.h>

static void destroy( GtkWidget *widget, gpointer data )
{
	gtk_main_quit ();
}
static gboolean
my_expose( GtkWidget      *da,
		GdkEventExpose *event,
		gpointer        data )
{
	GdkGC *gc1, *gc2, *gc;  /*gc1为矩形，gc2为文字*/
	GdkColor color;
	gc1 = gdk_gc_new( da->window );
	color.red = 30000;
	color.green = 0;
	color.blue = 30000;
	gdk_gc_set_rgb_fg_color(gc1, &color );
	gc2 = gdk_gc_new( da->window );
	color.red = 65535;
	color.green = 0;
	color.blue = 65535;
	gdk_gc_set_rgb_fg_color( gc2, &color );
	gc = gc1;
	gdk_draw_rectangle( da->window,
			gc,
			TRUE,//fill or not
			5, 5, 100, 100 );  /*（分别是越大则向右移动、越大则向下移、越大则向右扩大、越大则向下扩大）*/
	gc = gc2;
	gdk_draw_arc( da->window,
			gc,
			FALSE, //don't fill
			105, 5, 100, 100, 0, 60 * 64 );
	/*（分别是越大则向右移动、越大则向下移、越大则向右扩大、越大则向下扩大、0不知道代表什么、弧线弧度）*/

	PangoLayout *layout =
		gtk_widget_create_pango_layout( da, "I'm a demon\nfrom hell.\nhahaha." );
	PangoFontDescription *fontdesc =
		pango_font_description_from_string( "Luxi Mono 12" );
	pango_layout_set_font_description( layout, fontdesc );
	gdk_draw_layout( da->window,
			gc1,
			5, 105, layout );
	pango_font_description_free( fontdesc );
	g_object_unref( layout );

	g_object_unref( G_OBJECT(gc1) );
	g_object_unref( G_OBJECT(gc2) );

	return TRUE;
}
int new_test( int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *da; //drawing area
	gtk_init (&argc, &argv);
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	g_signal_connect( G_OBJECT (window), "destroy",
			G_CALLBACK (destroy), NULL );

	da = gtk_drawing_area_new ();
	/* set a minimum size */
	gtk_widget_set_size_request( da, 300, 300 );
	gtk_container_add( GTK_CONTAINER(window), da );
	g_signal_connect( da, "expose_event",
			G_CALLBACK(my_expose), NULL );

	gtk_widget_show_all( window ); //simply show all widgets
	gtk_main();

	return 0;
}
