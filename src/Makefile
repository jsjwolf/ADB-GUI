adb_gui.o : adb_gui.c adb_gui.h
	gcc -c adb_gui.c  `pkg-config --cflags --libs gtk+-2.0`

adb_gui : adb_gui.o
	gcc -o adb_gui.o

clean :
	rm *.o