#include <stdio.h>
#include "alunos_so.h"
#include "../resource_monitor.h"

void *alunosSOThread(void *ptr){
    int id = (intptr_t) ptr;

    srand(time(NULL) + (id * 2));
    int sleepTime = rand() % 8; 
    sleep(sleepTime);

    pthread_mutex_lock(&monitor.mutex);

    

    pthread_mutex_unlock(&monitor.mutex);
}

void entrarSalaAula(int id){
    printf("\n\t👨‍💻 | alunoSO_%d entra na sala\n", id);
    sleep(1);
}

void sairSalaAula(int id){
    printf("\t👨‍💻 | alunoSO_%d sai da sala\n", id);
    sleep(1);
}

void aguardarAula(int id){
    printf("\t👨‍💻 | alunoSO_%d aguardando professor começar a aula\n", id);
    sleep(1);
}

void obaAulaSO(int id){
    printf("\t👨‍💻 | alunoSO_%d Oba! Aula de SO!\n", id);
}

void chamarProfessor(int id){
    printf("\t👨‍💻 | alunoSO_%d Avisa que chegou todos os alunos.\n", id);
    sleep(1);
}