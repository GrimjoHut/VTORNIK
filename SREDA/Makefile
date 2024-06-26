CC = gcc
CFLAGS = -Wall -Werror

all: build_db

build_db: shared.o modules_db.o modules_table.o levels_table.o status_events_table.o
	$(CC) $(CFLAGS) -o build_db shared.o modules_db.o modules_table.o levels_table.o status_events_table.o

shared.o: shared.c
	$(CC) $(CFLAGS) -c shared.c

modules_db.o: modules_db.c
	$(CC) $(CFLAGS) -c modules_db.c

modules_table.o: modules_table.c
	$(CC) $(CFLAGS) -c modules_table.c

levels_table.o: levels_table.c
	$(CC) $(CFLAGS) -c levels_table.c

status_events_table.o: status_events_table.c
	$(CC) $(CFLAGS) -c status_events_table.c

clean:
	rm -f *.o build_db
