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
    if(alunosDuvidaCount == NUM_ALUNOS_DUVIDA){
         printf("Estou atendendo os alunos...\n");
        for(int i = 1; i <= NUM_ALUNOS_DUVIDA; i++){
            pthread_cond_signal(&prAtenderAlunos);
        }
    }
}

void darAula(){
    pthread_cond_wait(&alunosPresentes, &mutex); //espera pela sinalização de que todos 
                                                 //os alunos chegaram
    printf("Vou dar aula!\n");
    pthread_cond_broadcast(&prDarAula); //sinaliza para todos os alunos de SO que a aula vai começar
}

void dispensarAlunos(){}

void irEmboraCasa(){}
