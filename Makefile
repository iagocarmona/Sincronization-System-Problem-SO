CC=gcc -Wall

P1=aexec01
P2=exec02
P3=exec03
P4=exec04

PROGS=$(P1) $(P2) $(P3) $(P4)

FLAGS=-lpthread

all: $(PROGS)

$(P1):
	$(CC) $(P1).c -o $(P1) $(FLAGS)
$(P2):
	$(CC) $(P2).c -o $(P2) $(FLAGS)
$(P3):
	$(CC) $(P3).c -o $(P3) $(FLAGS)
$(P4):
	$(CC) $(P4).c -o $(P4) $(FLAGS)
	
clean:
	rm $(PROGS)