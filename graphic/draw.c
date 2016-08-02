#include <stdio.h>
#include <gtk/gtk.h>

void start_game(void);
void game_about(void);

void test(void)
{
	GtkWidget *window, *frame;
	GtkWidget *exit_button, *ack_button;

	int argc = 0;
	char **argv = NULL;

	gtk_init(&argc, &argv); //初始化很多东西，暂时不清楚
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	if (window == NULL) {
		printf("window new failed\n");
		return ;
	}
	gtk_widget_set_usize(window, 400, 400);
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
//	gtk_image_new_from_file();

	/* 标签，设置文本信息 */
//	GtkWidget *label;
//	label = gtk_label_new("1、开始游戏\n2、关于");
//	//gtk_label_set_text(label, "lala");
//	gtk_fixed_put(GTK_FIXED(frame), label, 150, 100);

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
	;
}

void game_about(void)
{
	;
}
