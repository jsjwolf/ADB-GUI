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

	//声明函数
	GtkFunction fnc_splash(GtkWidget *widget,gpointer *data); //启动闪现控制
	//按钮事件
	void btnadbpush_clicked(GtkWidget *widget, gpointer *data);
	void btnadbinstall_clicked(GtkWidget *widget, gpointer *data);
	void btnadbreboot_clicked(GtkWidget *widget, gpointer *data);
	void btnadbreboot_clicked(GtkWidget *widget, gpointer *data);
	void btnadbstart_clicked(GtkWidget *widget, gpointer *data);
	void btnadbstop_clicked(GtkWidget *widget, gpointer *data);
	void btnbackupcontact_clicked(GtkWidget *widget, gpointer *data);
	void btnsetadb_clicked(GtkWidget *widget, gpointer *data);
	void btnquit_clicked(GtkWidget *widget, gpointer *data);
	void btnreboot_clicked(GtkWidget *widget,gpointer *data);
	void btnrebootrec_clicked(GtkWidget *widget,gpointer *data);
	void btnrebootbl_clicked(GtkWidget *widget,gpointer *data);
	//回调函数
	void fuc_adbpush(GtkWidget *widget,gpointer *data);
	void fuc_adbinstall(GtkWidget *widget,gpointer *data);
	void fuc_bucontact(GtkWidget *widget,gpointer *data);
	void fuc_setadb(GtkWidget *widget,gpointer *data);
	void fuc_cancel(GtkWidget *widget,gpointer *data); 

	//声明全局变量
	GtkWidget *wd_splash; //闪现屏幕
	GtkWidget *wd_main; //主窗体
	GtkWidget *wd_fselect; //文件选择窗口
	GtkWidget *wd_reboot; //重启窗口

int main(int argc, char *argv[])
{
	//--------------------------------------------------------
	//闪现部分开始
		//定义控件
		GtkWidget *img_bg;
		
		gtk_init(&argc,&argv); //GTK初始化
		
		//初始化
		wd_splash=gtk_window_new(GTK_WINDOW_TOPLEVEL);
		img_bg=gtk_image_new_from_file("splash.png");
		
		//窗体设置
		gtk_window_set_position(GTK_WINDOW(wd_splash),GTK_WIN_POS_CENTER); //屏幕中心启动
		gtk_window_set_default_size(GTK_WINDOW(wd_splash),300,200);
		gtk_window_set_decorated(GTK_WINDOW(wd_splash),FALSE);
		
		//填充容器
		gtk_container_add(GTK_CONTAINER(wd_splash),img_bg);

		gtk_widget_show_all(wd_splash);
		gtk_timeout_add(2000,fnc_splash,wd_splash); //时间控制
	//闪现部分结束
	//--------------------------------------------------------
		
	//--------------------------------------------------------
	//主窗体部分开始
		//定义控件
		GtkWidget *btn_adbpush, *btn_adbinstall, *btn_adbreboot, *btn_setadb, *btn_backupcontact;
		GtkWidget *btn_adbstart, *btn_adbstop, *btn_quit;
		GtkWidget *tbl_main, *tbl_top, *tbl_bottom, *tbl_topright;
		GtkWidget *img_logo;
		GtkWidget *lbl_blank;
		
		//初始化
		wd_main=gtk_window_new(GTK_WINDOW_TOPLEVEL); //初始化主窗体
		img_logo=gtk_image_new_from_file ("logo.png");
		btn_adbstart=gtk_button_new_with_label ("Start Adb"); //初始化 btn_adbstart
		btn_adbstop=gtk_button_new_with_label ("Stop Adb"); //初始化 btn_adbstop
		btn_adbpush=gtk_button_new_with_label("Push"); //初始化 btn_adbpush
		btn_adbinstall=gtk_button_new_with_label ("Install"); //初始化 btn_adbinstall
		btn_setadb=gtk_button_new_with_label("Set Adb"); //初始化 btn_setadb
		btn_backupcontact=gtk_button_new_with_label("Backup Contact"); //初始化 btn_backupcontact 
		btn_adbreboot=gtk_button_new_with_label("Reboot"); //初始化 btn_adbreboot
		btn_quit=gtk_button_new_with_label("Quit"); //初始化 btn_quit
		tbl_main=gtk_table_new(2,1,FALSE); //主框架
		tbl_top=gtk_table_new(1,2,FALSE); //上半部分
		tbl_topright=gtk_table_new(2,3,FALSE); //右上角
		tbl_bottom=gtk_table_new (3,4,FALSE); //下半部分
		lbl_blank=gtk_label_new("    "); //空白标签
		
		//主窗体设置
		gtk_container_set_border_width(GTK_CONTAINER(wd_main),10);
		gtk_widget_set_size_request(wd_main,530,400);
		gtk_window_set_title (GTK_WINDOW(wd_main),"ADB-GUI");
		gtk_window_set_position(GTK_WINDOW(wd_main),GTK_WIN_POS_CENTER); //屏幕中心启动
		
		//容器设置
		gtk_table_set_row_spacings(GTK_TABLE(tbl_main),10);
		gtk_table_set_row_spacings(GTK_TABLE(tbl_top),10);
		gtk_table_set_row_spacings(GTK_TABLE(tbl_bottom),10);
		gtk_table_set_row_spacings(GTK_TABLE(tbl_topright),10);

		//控件设置
		gtk_widget_set_size_request(btn_adbinstall,150,40);
		gtk_widget_set_size_request(btn_adbpush,150,40);
		gtk_widget_set_size_request(btn_adbreboot,150,40);
		gtk_widget_set_size_request(btn_adbstart,150,30);
		gtk_widget_set_size_request(btn_adbstop,150,30);
		gtk_widget_set_size_request(btn_setadb,150,40);
		gtk_widget_set_size_request(btn_backupcontact,150,40);
		gtk_widget_set_size_request(btn_quit,100,30);
		gtk_widget_set_size_request(lbl_blank,70,30);
		
		//填充容器
		gtk_container_add (GTK_CONTAINER(wd_main),tbl_main);
		gtk_table_attach (GTK_TABLE(tbl_main),tbl_top,0,1,0,1,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),0,10);
		gtk_table_attach (GTK_TABLE(tbl_main),tbl_bottom,0,1,1,2,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),0,20);
		gtk_table_attach (GTK_TABLE(tbl_top),tbl_topright,1,2,0,1,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),10,0);
		gtk_table_attach (GTK_TABLE(tbl_top),img_logo,0,1,0,1,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),0,0); //行1列1
		gtk_table_attach (GTK_TABLE(tbl_topright),btn_adbstart,0,1,0,1,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),0,10); //行1列1
		gtk_table_attach (GTK_TABLE(tbl_topright),btn_adbstop,0,1,1,2,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),0,10); //行2列1
		gtk_table_attach (GTK_TABLE(tbl_topright),btn_quit,2,3,0,1,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),10,10); //行1列2
		gtk_table_attach (GTK_TABLE(tbl_topright),lbl_blank,1,2,0,1,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),10,10);
		gtk_table_attach (GTK_TABLE(tbl_bottom),btn_adbpush,0,1,0,1,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),10,10); //行1列1
		gtk_table_attach (GTK_TABLE(tbl_bottom),btn_adbinstall,0,1,1,2,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),10,10); //行1列2
		gtk_table_attach (GTK_TABLE(tbl_bottom),btn_backupcontact,0,1,2,3,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),10,10); //行1列3
		gtk_table_attach (GTK_TABLE(tbl_bottom),btn_setadb,2,3,2,3,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),10,10); //行3列3
		gtk_table_attach (GTK_TABLE(tbl_bottom),btn_adbreboot,1,2,0,1,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),10,10); //行1列2

		//信号连接
		g_signal_connect(G_OBJECT(wd_main),"delete_event",G_CALLBACK(gtk_main_quit),NULL); //关闭窗口结束主循环
		g_signal_connect(G_OBJECT(btn_adbstart),"clicked",G_CALLBACK(btnadbstart_clicked),(gpointer) wd_main); //btn_adbstart回调
		g_signal_connect(G_OBJECT(btn_adbstop),"clicked",G_CALLBACK(btnadbstop_clicked),(gpointer) wd_main); //btn_adbstop回调
		g_signal_connect(G_OBJECT(btn_adbpush),"clicked",G_CALLBACK(btnadbpush_clicked),(gpointer) wd_main); //btn_adbpush回调
		g_signal_connect(G_OBJECT(btn_adbinstall),"clicked",G_CALLBACK(btnadbinstall_clicked),(gpointer) wd_main); //btn_adbinstall回调
		g_signal_connect(G_OBJECT(btn_backupcontact),"clicked",G_CALLBACK(btnbackupcontact_clicked),(gpointer) wd_main); //btn_backupcontact回调
		g_signal_connect(G_OBJECT(btn_setadb),"clicked",G_CALLBACK(btnsetadb_clicked ),(gpointer) wd_main);//btn_setadb回调
		g_signal_connect(G_OBJECT(btn_quit),"clicked",G_CALLBACK(btnquit_clicked),(gpointer) wd_main);//btn_quit回调
		g_signal_connect(G_OBJECT(btn_adbreboot),"clicked",G_CALLBACK(btnadbreboot_clicked),(gpointer) wd_main);//btn_reboot回调
		
		
		gtk_main ();	
		return 0;
}

//函数

GtkFunction fnc_splash(GtkWidget *widget,gpointer *data) //闪现窗口控制
{
		sleep(3);
		gtk_widget_hide (wd_splash);
		gtk_widget_show_all (wd_main);
		return 0;
}

void btnadbstart_clicked(GtkWidget *widget, gpointer *data) //启动Adb
{
			system("adb start-server");
}

void btnadbstop_clicked(GtkWidget *widget, gpointer *data) //停止Adb
{
			system("adb kill-server");
}
//PUSH
void btnadbpush_clicked(GtkWidget *widget, gpointer *data) //按钮回调
{
		wd_fselect=gtk_file_selection_new("Select File");
		gtk_file_selection_set_filename(GTK_FILE_SELECTION(wd_fselect),"*.*");
		gtk_widget_show(wd_fselect);
		g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(wd_fselect)->ok_button),"clicked",GTK_SIGNAL_FUNC(fuc_adbpush),NULL);
		g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(wd_fselect)->cancel_button),"clicked",GTK_SIGNAL_FUNC(fuc_cancel),NULL);
}

void fuc_adbpush(GtkWidget *widget,gpointer *data) //执行
{
	const char *str_path;
	str_path=gtk_file_selection_get_filename(GTK_FILE_SELECTION(wd_fselect));
	g_print("%s\n",gtk_file_selection_get_filename(GTK_FILE_SELECTION(wd_fselect)));
	printf("Selected path is : %s\n",str_path);
	adbpush(str_path);
	gtk_widget_destroy (wd_fselect);
}
//INSTALL
void btnadbinstall_clicked(GtkWidget *widget, gpointer *data) //按钮回调
{
		wd_fselect=gtk_file_selection_new("Select File");
		gtk_file_selection_set_filename(GTK_FILE_SELECTION(wd_fselect),"*.apk");
		gtk_widget_show(wd_fselect);
		g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(wd_fselect)->ok_button),"clicked",GTK_SIGNAL_FUNC(fuc_adbinstall),NULL);
		g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(wd_fselect)->cancel_button),"clicked",GTK_SIGNAL_FUNC(fuc_cancel),NULL);
}

void fuc_adbinstall(GtkWidget *widget,gpointer *data) //执行
{
	const char *str_path;
	str_path=gtk_file_selection_get_filename(GTK_FILE_SELECTION(wd_fselect));
	g_print("%s\n",gtk_file_selection_get_filename(GTK_FILE_SELECTION(wd_fselect)));
	printf("Selected path is : %s\n",str_path);
	adbinstall(str_path);
	gtk_widget_destroy (wd_fselect);
}
//REBOOT
void btnadbreboot_clicked(GtkWidget *widget, gpointer *data) //按钮回调
{
	//--------------------------------------------------------
	//重启窗体部分
		//定义控件
		GtkWidget *tbl_reboot;
		GtkWidget *btn_reboot_rec, *btn_reboot_bl, *btn_reboot;

		//初始化
		wd_reboot=gtk_window_new(GTK_WINDOW_TOPLEVEL); //Initialize Window 初始化重启窗体
		tbl_reboot=gtk_table_new(3,1,FALSE);
		btn_reboot_rec=gtk_button_new_with_label("Reboot Recovery");
		btn_reboot_bl=gtk_button_new_with_label("Reboot Bootloader");
		btn_reboot=gtk_button_new_with_label("Reboot Normally");

		//窗体设置
		gtk_container_set_border_width(GTK_CONTAINER(wd_reboot),10); //设置边框宽度
		gtk_window_set_title (GTK_WINDOW(wd_reboot),"Reboot"); //设置标题
		gtk_window_set_position(GTK_WINDOW(wd_reboot),GTK_WIN_POS_CENTER); //设置初始位置：屏幕中央
		
		//容器设置
		gtk_table_set_row_spacings(GTK_TABLE(tbl_reboot),10);

		//控件设置
		gtk_widget_set_size_request(btn_reboot,150,40);
		gtk_widget_set_size_request(btn_reboot_rec,150,40);
		gtk_widget_set_size_request(btn_reboot_bl,150,40);
		
		//填充容器
		gtk_container_add(GTK_CONTAINER(wd_reboot), tbl_reboot);
		gtk_table_attach(GTK_TABLE(tbl_reboot), btn_reboot_rec, 0,1,0,1,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),0,0);
		gtk_table_attach(GTK_TABLE(tbl_reboot), btn_reboot_bl, 0,1,1,2,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),0,0);
		gtk_table_attach(GTK_TABLE(tbl_reboot), btn_reboot, 0,1,2,3,(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0),0,0);
		
		//信号连接
		g_signal_connect(G_OBJECT(btn_reboot_rec),"clicked",G_CALLBACK(btnrebootrec_clicked), (gpointer) wd_reboot); //Recovery
		g_signal_connect(G_OBJECT(btn_reboot_bl),"clicked",G_CALLBACK(btnrebootbl_clicked),(gpointer) wd_reboot); //Bootloader
		g_signal_connect(G_OBJECT(btn_reboot),"clicked",G_CALLBACK(btnreboot_clicked),(gpointer) wd_reboot); //Normal
		
		gtk_widget_show_all (wd_reboot);
		
	//重启窗体结束
	//--------------------------------------------------------
}

void btnrebootrec_clicked(GtkWidget *widget, gpointer *data) //重启为Recovery
{
	system("adb reboot recovery");
}

void btnrebootbl_clicked(GtkWidget *widget, gpointer *data) //重启为Bootloader
{
	system("adb reboot bootloader");
}

void btnreboot_clicked(GtkWidget *widget, gpointer *data) //正常重启
{
	system("adb reboot");
}
//联系人备份
void btnbackupcontact_clicked(GtkWidget *widget, gpointer *data) //按钮回调
{
		wd_fselect=gtk_file_selection_new("Select Path");
		gtk_file_selection_set_filename(GTK_FILE_SELECTION(wd_fselect)," ");
		gtk_widget_show(wd_fselect);
		g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(wd_fselect)->ok_button),"clicked",GTK_SIGNAL_FUNC(fuc_bucontact),NULL);
		g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(wd_fselect)->cancel_button),"clicked",GTK_SIGNAL_FUNC(fuc_cancel),NULL);
		
}

void fuc_bucontact(GtkWidget *widget,gpointer *data) //执行
{
	const char *str_path;
	str_path=gtk_file_selection_get_filename(GTK_FILE_SELECTION(wd_fselect));
	g_print("%s\n",gtk_file_selection_get_filename(GTK_FILE_SELECTION(wd_fselect)));
	printf("Selected path is : %s\n",str_path);
	adbbucontact(str_path);
	gtk_widget_destroy (wd_fselect);
}

//设置ADB环境变量
void btnsetadb_clicked(GtkWidget *widget, gpointer *data) //按钮回调
{
		wd_fselect=gtk_file_selection_new("Select Path");
		gtk_file_selection_set_filename(GTK_FILE_SELECTION(wd_fselect),"adb");
		gtk_widget_show(wd_fselect);
		g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(wd_fselect)->ok_button),"clicked",GTK_SIGNAL_FUNC(fuc_setadb),NULL);
		g_signal_connect(GTK_OBJECT(GTK_FILE_SELECTION(wd_fselect)->cancel_button),"clicked",GTK_SIGNAL_FUNC(fuc_cancel),NULL);
}

void fuc_setadb (GtkWidget *widget, gpointer *data) //执行
{
	const char *str_path;
	str_path=gtk_file_selection_get_filename(GTK_FILE_SELECTION(wd_fselect));
	g_print("%s\n",gtk_file_selection_get_filename(GTK_FILE_SELECTION(wd_fselect)));
	printf("Selected path is : %s\n",str_path);
	setadb(str_path);
	gtk_widget_destroy (wd_fselect);
}
//其他
void btnquit_clicked(GtkWidget *widget, gpointer *data) //退出按钮
{
		gtk_main_quit ();
}

void fuc_cancel(GtkWidget *widget,gpointer *data) //文件选择窗口“取消”回调
{
			gtk_widget_destroy (wd_fselect);
}
