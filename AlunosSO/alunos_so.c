#include <stdio.h>
#include "alunos_so.h"
#include "../resource_monitor.h"

void *alunosSOThread(void *ptr){
    int num = (intptr_t) ptr;
    aguardarAula(num);
    pthread_exit(0);
}

void entrarSalaAula(int num){
    printf("\talunoSO_%d entra na sala\n", num);
}

void sairSalaAula(int num){
    printf("\talunoSO_%d sai na sala\n", num);
}

void aguardarAula(int num){
    printf("\talunoSO_%d aguardando professor dar aula\n", num);
    pthread_cond_wait(&prDarAula, &mutex);
    obaAulaSO();
}

void obaAulaSO(int num){
    printf("\talunoSO_%d fica feliz que vai ter aula\n", num);
}

void chamarProfessor(int num){
    printf("\talunoSO_%d chama professor\n", num);
}