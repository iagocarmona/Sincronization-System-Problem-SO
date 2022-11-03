#include <stdio.h>
#include "professor.h"
#include "../resource_monitor.h"

void *professorThread(void *ptr){
    int num = (intptr_t) ptr;

    while(alunosDuvidaCount < NUM_GRUPO_ATENDE_ALUNOS){
        printf("Professor %d\n", num);
        darAula();
        pthread_exit(0);
    }
    atenderAlunos();
    pthread_exit(0);
}

void prepararAula(){}

void atenderAlunos(){
    pthread_cond_signal(&prAtenderAlunos);
    printf("Estou atendendo os alunos...\n");
}

void darAula(){
    printf("Vou dar aula!\n");
    pthread_cond_broadcast(&prDarAula);
}

void dispensarAlunos(){}

void irEmboraCasa(){}
