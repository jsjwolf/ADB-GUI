/*
 * ADB-GUI
 * By Z.Shang
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<gtk/gtk.h>
#include<string.h>
#include"adb_gui.h"

//Functions Declare 声明函数
		GtkFunction fnc_splash(GtkWidget *widget,gpointer *data); //Splash Controller 启动闪现控制
		GtkFunction fuc_cancel(GtkWidget *widget,gpointer *data); //Callback For Cancel Button Cancel按钮回调
		void btnadbpush_clicked(GtkWidget *widget, gpointer *data);
		void btnadbinstall_clicked(GtkWidget *widget, gpointer *data);
		void btnadbreboot_clicked(GtkWidget *widget, gpointer *data);
		void btnadbreboot_clicked(GtkWidget *widget, gpointer *data);
		void btnadbstart_clicked(GtkWidget *widget, gpointer *data);
		void btnadbstop_clicked(GtkWidget *widget, gpointer *data);
		void btnbackupcontact_clicked(GtkWidget *widget, gpointer *data);
		void btnsetadb_clicked(GtkWidget *widget, gpointer *data);
		void btnquit_clicked(GtkWidget *widget, gpointer *data);
		void fuc_adbpush(GtkWidget *widget,gpointer *data);
		void fuc_adbinstall(GtkWidget *widget,gpointer *data);


//Universal Declare 声明全局变量
		GtkWidget *wd_splash; //Splash Window 闪现屏幕
		GtkWidget *wd_main; //Main Window 主窗体
		GtkWidget *wd_fselect; //File Select Window 文件选择窗口


int main(int argc, char *argv[])
{
		//--------------------------------------------------------
		//Splash Starts 闪现部分开始
		GtkWidget *img_bg;
		gtk_init(&argc,&argv);
		wd_splash=gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_position(GTK_WINDOW(wd_splash),GTK_WIN_POS_CENTER);
		gtk_window_set_default_size(GTK_WINDOW(wd_splash),300,200);
		gtk_window_set_decorated(GTK_WINDOW(wd_splash),FALSE);
		img_bg=gtk_image_new_from_file("splash.png");
		gtk_container_add(GTK_CONTAINER(wd_splash),img_bg);
		gtk_widget_show_all(wd_splash);
		gtk_timeout_add(3000,fnc_splash,wd_splash);
		//Splash Ends 闪现部分结束
		//--------------------------------------------------------
		//--------------------------------------------------------
		//Main Starts 主窗体部分开始
		GtkWidget *btn_adbpush, *btn_adbinstall, *btn_adbreboot, *btn_setadb, *btn_backupcontact;
		GtkWidget *btn_adbstart, *btn_adbstop, *btn_quit;
		GtkWidget *tbl_main, *tbl_top, *tbl_bottom, *tbl_topright;
		GtkWidget *img_logo;
		img_logo=gtk_image_new_from_file ("logo.png");
		wd_main=gtk_window_new(GTK_WINDOW_TOPLEVEL);
		g_signal_connect(G_OBJECT(wd_main),"delete_event",G_CALLBACK(gtk_main_quit),NULL);
		gtk_container_set_border_width(GTK_CONTAINER(wd_main),10);
		gtk_widget_set_size_request(wd_main,600,400);
		gtk_window_set_title (GTK_WINDOW(wd_main),"ADB-GUI");
		gtk_window_set_position(GTK_WINDOW(wd_main),GTK_WIN_POS_CENTER);
		tbl_main=gtk_table_new(2,1,FALSE); //Main Table 主框架
		tbl_top=gtk_table_new(1,2,FALSE); //Top Part 上半部分
		tbl_topright=gtk_table_new(2,2,FALSE); //Top Right Part 右上角
		tbl_bottom=gtk_table_new (3,4,FALSE); //Bottom Part 下半部分
		btn_adbstart=gtk_button_new_with_label ("Start Adb"); //Initialize btn_adbstart 初始化 btn_adbstart
		btn_adbstop=gtk_button_new_with_label ("Stop Adb"); //Initialize btn_adbstop 初始化 btn_adbstop
		g_signal_connect(G_OBJECT(btn_adbstart),"clicked",G_CALLBACK(btnadbstart_clicked),(gpointer) wd_main); //Connect Signal For btn_adbstart
		g_signal_connect(G_OBJECT(btn_adbstop),"clicked",G_CALLBACK(btnadbstop_clicked),(gpointer) wd_main); //Connect Signal For btn_adbstop
		gtk_table_attach (GTK_TABLE(tbl_topright),btn_adbstart,0,1,0,1,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),0,10);
		gtk_table_attach (GTK_TABLE(tbl_topright),btn_adbstop,0,1,1,2,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),0,10);
		gtk_container_add (GTK_CONTAINER(wd_main),tbl_main);
		gtk_table_attach (GTK_TABLE(tbl_main),tbl_top,0,1,0,1,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),0,10);
		gtk_table_attach (GTK_TABLE(tbl_top),img_logo,0,1,0,1,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),0,0);
		gtk_table_attach (GTK_TABLE(tbl_main),tbl_bottom,0,1,1,2,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),0,20);
		gtk_table_attach (GTK_TABLE(tbl_top),tbl_topright,1,2,0,1,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),10,0);
		btn_adbpush=gtk_button_new_with_label("Push"); //Initialize btn_adbpush  初始化 btn_adbpush
		btn_adbinstall=gtk_button_new_with_label ("Install"); //Initialize btn_adbinstall 初始化 btn_adbinstall
		g_signal_connect(G_OBJECT(btn_adbpush),"clicked",G_CALLBACK(btnadbpush_clicked),(gpointer) wd_main); //Connect Signal For btn_adbpush
		g_signal_connect(G_OBJECT(btn_adbinstall),"clicked",G_CALLBACK(btnadbinstall_clicked),(gpointer) wd_main); //Connect Signal For btn_adbinstall
		gtk_table_attach (GTK_TABLE(tbl_bottom),btn_adbpush,0,1,0,1,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),10,10); //Column 1 Row 1 行1列1
		gtk_table_attach (GTK_TABLE(tbl_bottom),btn_adbinstall,0,1,1,2,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),10,10); //Column 1 Row 2 行1列2
		btn_backupcontact=gtk_button_new_with_label("Backup Contact"); //Initialize btn_backupcontact 初始化 btn_backupcontact 
		g_signal_connect(G_OBJECT(btn_backupcontact),"clicked",G_CALLBACK(btnbackupcontact_clicked),(gpointer) wd_main); //Connect Signal For btn_backupcontact
		gtk_table_attach (GTK_TABLE(tbl_bottom),btn_backupcontact,0,1,2,3,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),10,10); //Column 1 Row 3 行1列3
		btn_setadb=gtk_button_new_with_label("Set Adb"); //Initialize btn_setadb 初始化 btn_setadb
		g_signal_connect(G_OBJECT(btn_setadb),"clicked",G_CALLBACK(btnsetadb_clicked),(gpointer) wd_main);
		gtk_table_attach (GTK_TABLE(tbl_bottom),btn_setadb,2,3,2,3,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),10,10);
		btn_quit=gtk_button_new_with_label("Quit");
		gtk_table_attach (GTK_TABLE(tbl_topright),btn_quit,1,2,0,1,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),10,10);
		g_signal_connect(G_OBJECT(btn_quit),"clicked",G_CALLBACK(btnquit_clicked),(gpointer) wd_main);
		
		
		
		gtk_main ();	
		return 0;
}

//Functions: 函数:

GtkFunction fnc_splash(GtkWidget *widget,gpointer *data) //Splash Controller
{
		sleep(3);
		gtk_widget_hide (wd_splash);
		gtk_widget_show_all (wd_main);
		return 0;
}

void btnadbstart_clicked(GtkWidget *widget, gpointer *data) //Adb Start
{
			system("adb start-server");
}

void btnadbstop_clicked(GtkWidget *widget, gpointer *data) //Adb Stop
{
			system("adb kill-server");
}

void btnadbpush_clicked(GtkWidget *widget, gpointer *data)
{
		wd_fselect=gtk_file_selection_new("Select File");
		gtk_file_selection_set_filename(GTK_FILE_SELECTION(wd_fselect),"*.*");
		gtk_widget_show(wd_fselect);
		g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(wd_fselect)->ok_button),"clicked",GTK_SIGNAL_FUNC(fuc_adbpush),NULL);
		g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(wd_fselect)->cancel_button),"clicked",GTK_SIGNAL_FUNC(fuc_cancel),NULL);
}

void btnadbinstall_clicked(GtkWidget *widget, gpointer *data)
{
		wd_fselect=gtk_file_selection_new("Select File");
		gtk_file_selection_set_filename(GTK_FILE_SELECTION(wd_fselect),"*.apk");
		gtk_widget_show(wd_fselect);
		g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(wd_fselect)->ok_button),"clicked",GTK_SIGNAL_FUNC(fuc_adbinstall),NULL);
		g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(wd_fselect)->cancel_button),"clicked",GTK_SIGNAL_FUNC(fuc_cancel),NULL);
}

void btnbackupcontact_clicked(GtkWidget *widget, gpointer *data)
{

}

void btnsetadb_clicked(GtkWidget *widget, gpointer *data)
{

}

void btnquit_clicked(GtkWidget *widget, gpointer *data)
{
		gtk_main_quit ();
}

void fuc_adbpush(GtkWidget *widget,gpointer *data)
{
	const char *str_path;
	str_path=gtk_file_selection_get_filename(GTK_FILE_SELECTION(wd_fselect));
	g_print("%s\n",gtk_file_selection_get_filename(GTK_FILE_SELECTION(wd_fselect)));
	printf("Selected path is : %s\n",str_path);
	adbpush(str_path);
	gtk_widget_destroy (wd_fselect);
}

void fuc_adbinstall(GtkWidget *widget,gpointer *data)
{
	const char *str_path;
	str_path=gtk_file_selection_get_filename(GTK_FILE_SELECTION(wd_fselect));
	g_print("%s\n",gtk_file_selection_get_filename(GTK_FILE_SELECTION(wd_fselect)));
	printf("Selected path is : %s\n",str_path);
	adbinstall(str_path);
	gtk_widget_destroy (wd_fselect);
}

GtkFunction fuc_cancel(GtkWidget *widget,gpointer *data)
{
			gtk_widget_destroy (wd_fselect);
}