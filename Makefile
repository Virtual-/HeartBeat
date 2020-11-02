CC=cc
CFLAGS=-Wall -g

make: heartbeat.c
	$(CC) -o heartbeat heartbeat.c

install:
	cp fedinfo /usr/bin/

uninstall:
	rm /usr/bin/fedinfo

clean:
	rm fedinfo
