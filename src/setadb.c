#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<gtk/gtk.h>

const char *str_path;
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

void btnset_clicked(GtkWidget *widget, gpointer *data)
{
	if ((access(str_path,X_OK))==0)
	{
	char cmd[255];
	strcat(cmd,"echo  \" export ADB=");
	strcat(cmd,str_path);
	strcat(cmd,"\nexport PATH=$PATH:ADB \" >> $HOME\/.bashrc");
	system(cmd);
	system("source $HOME\/.bashrc");
	}
	else
	{
	printf("Adb is unavalible\n");
	}
}

int main(int argc, char *argv[])
{
	GtkWidget *wd_main;
	GtkWidget *btn_set, *btn_fselect;
	GtkWidget *tbl_main;
	gtk_init(&argc,&argv);
	wd_main=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(wd_main),40);
	gtk_window_set_title(GTK_WINDOW(wd_main),"Setup ADB");
	btn_set=gtk_button_new_with_label("Set Adb");
	btn_fselect=gtk_button_new_with_label("Find Adb");
	tbl_main=gtk_table_new(2,1,FALSE);
	gtk_container_add(GTK_CONTAINER(wd_main),tbl_main);
	gtk_table_attach(GTK_TABLE(tbl_main), btn_fselect, 0,1,0,1,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),0,0);
	gtk_table_attach(GTK_TABLE(tbl_main), btn_set, 0,1,1,2,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),0,0);
	g_signal_connect(GTK_OBJECT(wd_main),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	g_signal_connect(GTK_OBJECT(btn_fselect),"clicked",G_CALLBACK(btnfselect_clicked),(gpointer) wd_main);
	g_signal_connect(GTK_OBJECT(btn_set),"clicked",G_CALLBACK(btnset_clicked),(gpointer) wd_main);
	gtk_widget_show_all(wd_main);
	gtk_main();
	return 0; 
}
