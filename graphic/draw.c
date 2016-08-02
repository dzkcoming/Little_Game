#include <stdio.h>
#include <gtk/gtk.h>

void start_game(void);
void game_about(void);
static void image_play(GtkWidget *frame, const char *url, int size_x, int size_y, int x, int y);

static const char *src_image[2] = {"resource/main_surface.png", "resource/about.jpg"};

GtkWidget *window, *frame;
GtkWidget *exit_button, *ack_button;
GtkWidget *image;

#define WINDOW_X 400
#define WINDOW_Y 400

void test(void)
{
	int argc = 0;
	char **argv = NULL;

	gtk_init(&argc, &argv); //初始化很多东西，暂时不清楚
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	if (window == NULL) {
		printf("window new failed\n");
		return ;
	}
	gtk_widget_set_usize(window, WINDOW_X, WINDOW_Y);
	gtk_widget_set_uposition(window, 100, 100);
	gtk_window_set_title(GTK_WINDOW(window), "五子棋");

	frame = gtk_fixed_new();
	if (frame == NULL) {
		// free
		printf("fixed new failed\n");
		goto show;
	}
	gtk_container_add(GTK_CONTAINER(window), frame);

	/* 背景图片 */
	image_play(frame, src_image[0], WINDOW_X, WINDOW_Y, 0, 0);

	/* button */
	ack_button  = gtk_button_new_with_label("开始游戏");
	exit_button = gtk_button_new_with_label("  关于  ");
	if (exit_button == NULL || ack_button == NULL) {
		// free
		printf("exit_button new failed\n");
		goto show;
	}
	gtk_widget_set_size_request( ack_button, 150, 80);
	gtk_widget_set_size_request(exit_button, 150, 80);

	gtk_fixed_put(GTK_FIXED(frame),  ack_button, 130,  80);
	gtk_fixed_put(GTK_FIXED(frame), exit_button, 130, 180);

	g_signal_connect(     window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect( ack_button, "clicked", G_CALLBACK(start_game), NULL);
	g_signal_connect(exit_button, "clicked", G_CALLBACK(game_about), NULL);

show:
	gtk_widget_show_all(window);
	gtk_main();

	return ;
}

void start_game(void)
{
	gtk_container_remove(GTK_CONTAINER(window), frame);

	// 画棋盘
	GdkPixmap *pixmap = NULL;
	GdkGC *gc;

	gc = gdk_gc_new(window->window);
	pixmap = gdk_pixmap_new(window->window,
			WINDOW_X,
			WINDOW_Y,
			-1);
	gdk_draw_rectangle (pixmap,
			gc,
			TRUE,
			0, 0,
			WINDOW_X,
			WINDOW_Y);
	gtk_widget_show_all(window);
}


static const char *about_title = "关   于";
static const char *about_content = "作者: 窦中康\n\n源码地址: https://github.com/dzkcoming/Little_Game\n\n加入我们: 来吧，加入我们的队伍";

void game_about(void)
{
	gtk_container_remove(GTK_CONTAINER(window), frame);

	GtkWidget *fixed;
	GtkWidget *label_title, *label_content;
	fixed = gtk_fixed_new();
	if (fixed == NULL) {
		printf("fixed new failed\n");
	}
	gtk_container_add(GTK_CONTAINER(window), fixed);

	image_play(fixed, src_image[1], WINDOW_X, WINDOW_Y, 0, 0);

	label_title   = gtk_label_new(about_title);
	label_content = gtk_label_new(about_content);
	gtk_fixed_put(GTK_FIXED(fixed),   label_title,  180, 0);
	gtk_fixed_put(GTK_FIXED(fixed), label_content, 0, 80);


	gtk_widget_show_all(window);
}

static void image_play(GtkWidget *frame, const char *url, int size_x, int size_y, int x, int y)
{
	//5.通过GdkPixbuf来写该图片大小
	//5.1创建pixbuf，需要占用资源，使用完需要释放
	GdkPixbuf *src = gdk_pixbuf_new_from_file(url, NULL);
	//5.2修改图片大小
	GdkPixbuf *dst = gdk_pixbuf_scale_simple(src, size_x, size_y, GDK_INTERP_BILINEAR);
	GtkWidget *image = gtk_image_new_from_pixbuf(dst);
	//5.3pixbuf使用完需要释放其中资源
	g_object_unref(src);
	g_object_unref(dst);

	gtk_fixed_put(GTK_FIXED(frame), image, 0, 0);
}
