#include <gtk/gtk.h>
typedef struct
{
    gint x;
    gint y;
}RECT_POINTER;
void draw_start(GtkWidget *draw,GdkEventButton *event,RECT_POINTER *rect)
{
    switch(event->button)
    {
        case 1:
            gdk_window_clear(draw->window);
            rect->x=(gint)event->x;
            rect->y=(gint)event->y;
            break;
    }
}
void draw_end(GtkWidget *draw,GdkEventButton *event,RECT_POINTER *rect)
{
    GdkGC *gc;
    GdkColor color;
    gint x,y,width,height;
    x=rect->x;
    y=rect->y;
    width=event->x-rect->x;
    height=event->y-rect->y;
    switch(event->button)
    {
        case 1:
            gc=gdk_gc_new(draw->window);
            color.blue=0;
            color.green=0;
            color.red=0xffff;
            gdk_gc_set_rgb_fg_color(gc,&color);
            if(rect->x>event->x)
            {
                x=event->x;
                width=rect->x-event->x;
            }
            if(rect->y>event->y)
            {
                y=event->y;
                height=rect->y-event->y;
            }
            gdk_draw_rectangle(draw->window,gc,TRUE,x,y,width,height);
            break;
    }
}

int test_draw(int argc,char **argv)
{
    GtkWidget *win;
    GtkWidget *draw;
    RECT_POINTER rect;
    gtk_init(&argc,&argv);
    win=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(win),GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(win),"delete_event",G_CALLBACK(gtk_main_quit),NULL);
    draw=gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(win),draw);
    gtk_widget_add_events(draw,GDK_BUTTON_PRESS_MASK);
    gtk_widget_add_events(draw,GDK_BUTTON_RELEASE_MASK);
    g_signal_connect(G_OBJECT(draw),"button_press_event",G_CALLBACK(draw_start),&rect);
    g_signal_connect(G_OBJECT(draw),"button_release_event",G_CALLBACK(draw_end),&rect);
    gtk_widget_show_all(win);
    gtk_main();
    return 0;
}
