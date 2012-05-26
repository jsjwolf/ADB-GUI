#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<gtk/gtk.h>

void adbpush (const char *path)
{
	const char *c1="adb push ";
	const char *c2=" \/sdcard\/ ";
	int i;
	i=strlen(path)+strlen(c1)+strlen(c2);
	char cmd[i];
	strcpy(cmd,c1);
	strcat(cmd, path);
	strcat(cmd,c2);
	system(cmd);
}	

void adbinstall(const char *path)
{
	const char *c1="adb install ";
	int i;
	i=strlen(path)+strlen(c1);
	char cmd[i];
	strcpy(cmd,c1);
	strcat(cmd, path);
	system(cmd);
}

void adbbucontact(const char *path)
{
		const char *c1="adb pull \/data\/data\/com.android.providers.contacts\/databases\/contacts2.db ";
		int i;
		i=strlen(path)+strlen(c1);
		char cmd[i];
		strcpy(cmd,c1);
		strcat(cmd,path);
		system(cmd);
}

void setadb(const char *path)
{
	int i;
	const char *c1="echo  \" export ADB= ";
	const char *c2="\nexport PATH=$PATH:ADB \" >> $HOME\/.bashrc";
	const char *c3="source $HOME\/.bashrc";
	i=strlen(c1)+strlen(path)+strlen(c2);
	char cmd[i];
	strcpy(cmd,c1);
	strcat(cmd,path);
	strcat(cmd,c2);
	system(cmd);
	system(c3);
}