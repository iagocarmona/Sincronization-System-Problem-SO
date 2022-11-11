all:
	gcc semaforo.c -o semaforo -lpthread
	./semaforo

clean:
	rm -f semaforo