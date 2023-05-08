CC     = gcc
CFLAGS = -std=c99 -Wall -Werror -g
EXE    = routeDealing
OBJT = routeDealing.o mapRead.o mapEdit.o routeInit.o routeSearch.o routeShown.o errReport.o

all: ${EXE}

clean:
	rm -rf *.o ${EXE}

*.o: *.c
	$(CC) -c $(CFLAGS) -I. $< -o $@

routeDealing: $(OBJT)
	$(CC) $(CFLAGS) -o pgmEcho $(OBJT1)
