#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<gtk/gtk.h>
static void btnrebootrec_clicked()
{
	system("adb reboot recovery");
}

static void btnrebootbl_clicked()
{
	system("adb reboot bootloader");
}

static void btnreboot_clicked()
{
	system("adb reboot");
}

int main(int argc, char *argv[])
{
	GtkWidget *wd_main;
	GtkWidget *btn_reboot_rec, *btn_reboot_bl, *btn_reboot;
	gtk_init(&argc, &argv);
	wd_main=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(wd_main),"Adb Reboot");
	gtk_container_set_border_width(GTK_CONTAINER(wd_main),40);
	GtkWidget *tbl_main;
	tbl_main=gtk_table_new(3,1,FALSE);
	gtk_container_add(GTK_CONTAINER(wd_main), tbl_main);
	gtk_table_set_row_spacings(GTK_TABLE(tbl_main),10);
	g_signal_connect(G_OBJECT(wd_main), "delete_event", G_CALLBACK(gtk_main_quit), NULL);
	btn_reboot_rec=gtk_button_new_with_label("Reboot Recovery");
	gtk_table_attach(GTK_TABLE(tbl_main), btn_reboot_rec, 0,1,0,1,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),0,0);
	g_signal_connect(G_OBJECT(btn_reboot_rec),"clicked",G_CALLBACK(btnrebootrec_clicked), (gpointer) wd_main); //Recovery
	btn_reboot_bl=gtk_button_new_with_label("Reboot Bootloader");
	gtk_table_attach(GTK_TABLE(tbl_main), btn_reboot_bl, 0,1,1,2,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),0,0);
	g_signal_connect(G_OBJECT(btn_reboot_bl),"clicked",G_CALLBACK(btnrebootbl_clicked),(gpointer) wd_main); //Bootloader
	btn_reboot=gtk_button_new_with_label("Reboot Normally");
	gtk_table_attach(GTK_TABLE(tbl_main), btn_reboot, 0,1,2,3,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),0,0);
	g_signal_connect(G_OBJECT(btn_reboot),"clicked",G_CALLBACK(btnreboot_clicked),(gpointer) wd_main); //Normal
	if((access("/home/stalin/Android/2-Android-SDK-Linux/platform-tools/adb",X_OK))==0)
	{
	gtk_widget_show_all(wd_main);
	}
	else
	{
	printf("Adb is UNAVALIBLE! \n");
	}
	gtk_main();
	return 0;
	
}
