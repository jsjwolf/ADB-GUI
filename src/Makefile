debug : adb_gui.c adb_gui.h
	gcc -g -Wall adb_gui.c -o adb_gui `pkg-config --cflags --libs gtk+-2.0`

out : adb_gui.c adb_gui.h
	gcc adb_gui.c -o adb_gui `pkg-config --cflags --libs gtk+-2.0`
	mv adb_gui ../output/
	cp *.png ../output/
