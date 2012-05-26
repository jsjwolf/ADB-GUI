#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"adb_gui.h"
int main(int argc, char *argv[])
{
	char *str_path="/home/stalin/Hotel_California.mp3 ";
	adbpush(str_path);
	return 0;
}