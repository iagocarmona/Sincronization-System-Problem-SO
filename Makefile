C=gcc

P1=semaforo

FLAGS=-lpthread -lm

PROGS=$(P1)

all: $(PROGS)

$(P1):	$(P1).c
	$(CC) $(P1).c -o $(P1) $(FLAGS)

clean:
	rm $(PROGS)