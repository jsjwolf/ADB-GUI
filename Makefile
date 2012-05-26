CC=gcc
all:
	$(CC) -o ./bin/AdbGui ./src/splash.c `pkg-config --cflags --libs gtk+-2.0`
