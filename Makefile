CC=cc
CFLAGS=-Wall -g

make: heartbeat.c
	$(CC) -o heartbeat heartbeat.c fedora.c netbsd.c unix.c

install:
	cp heartbeat /usr/bin/

uninstall:
	rm /usr/bin/heartbeat

clean:
	rm heartbeat
