CC=gcc -Wall

P1=AlunosDuvidas/alunos_duvidas
P2=AlunosSO/alunos_so
P3=Professor/professor
P4=semaforo

PROGS=main

FLAGS=-lpthread

all: $(PROGS)

clean:
	rm -f $(PROGS)

main: main.c semaforo.c semaforo.h
	$(CC) main.c $(P4).c $(P1).c $(P2).c $(P3).c -o $(PROGS) $(FLAGS)