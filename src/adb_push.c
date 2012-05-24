#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<gtk/gtk.h>

char *str_path;
GtkWidget *wd_fselect;

void OpenFile(GtkWidget *widget,gpointer *data)
{
	str_path=gtk_file_selection_get_filename(GTK_FILE_SELECTION(wd_fselect));
	g_print("%s\n",gtk_file_selection_get_filename(GTK_FILE_SELECTION(wd_fselect)));
	printf("%s\n",str_path);
}

void btnfselect_clicked(GtkWidget *widget, gpointer *data)
{
	wd_fselect=gtk_file_selection_new("Select File");
	gtk_file_selection_set_filename(GTK_FILE_SELECTION(wd_fselect),"*.*");
	gtk_widget_show(wd_fselect);
	g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(wd_fselect)->ok_button),"clicked",GTK_SIGNAL_FUNC(OpenFile),NULL);
}

void btnpush_clicked(GtkWidget *widget, gpointer *data)
{
	char cmd[255];
	strcat(cmd,"adb push ");
	strcat(cmd, str_path);
	strcat(cmd," /sdcard/ ");
	//printf("%s\n",cmd);
	system(cmd);
}
int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	GtkWidget *wd_main;
	GtkWidget *btn_fselect, *btn_push;
	GtkWidget *tbl_main;
	wd_main=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(wd_main,100,300);
	btn_fselect=gtk_button_new_with_label("Select File");
	btn_push=gtk_button_new_with_label("Push!");
	tbl_main=gtk_table_new(2,1,TRUE);
	gtk_container_add(GTK_CONTAINER(wd_main),tbl_main);
	g_signal_connect(G_OBJECT(btn_fselect),"clicked",G_CALLBACK(btnfselect_clicked),(gpointer) wd_main);
	g_signal_connect(G_OBJECT(btn_push),"clicked",G_CALLBACK(btnpush_clicked),(gpointer) wd_main);
	g_signal_connect(G_OBJECT(wd_main),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_table_attach(GTK_TABLE(tbl_main),btn_fselect,0,1,0,1,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),0,0);
	gtk_table_attach(GTK_TABLE(tbl_main),btn_push,0,1,1,2,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),0,0);
	gtk_widget_show_all(wd_main);
	gtk_main();
	return 0;
}

