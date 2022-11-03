#include <stdio.h>
#include "alunos_duvidas.h"
#include "../resource_monitor.h"

void *alunosDuvidasThread(void *ptr){
    int num = (intptr_t) ptr;
    chegarSalaProfessor();
    aguardarProfessor();
    tirarDuvidas();
    pthread_exit(0);
}

void chegarSalaProfessor(int num){
    printf("\t\talunoDuvida_%d chegou na porta do professor\n", num);
}

void aguardarProfessor(int num){
    printf("\t\talunoDuvida_%d está aguardando atendimento do professor.\n", num);
}

void tirarDuvidas(int num){
    printf("\t\talunoDuvida_%d vai tirar suas dúvidas...\n", num);
    pthread_cond_wait(&prAtenderAlunos, &mutex);
}

void sairSalaProfessor(int num){
    printf("\t\talunoDuvida_%d saiu da sala do professor\n", num);
}
