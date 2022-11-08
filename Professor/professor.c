#include <stdio.h>
#include "professor.h"
#include "../resource_monitor.h"

void *professorThread(void *ptr){
    int num = (intptr_t) ptr;
    pthread_mutex_lock(&monitor.mutex);
    while(monitor.alunosDuvidaCount < NUM_GRUPO_ATENDE_ALUNOS){
        printf("Professor %d\n", num);
        darAula();
        pthread_exit(0);
    }
    atenderAlunos();
    pthread_mutex_unlock(&monitor.mutex);
    pthread_exit(0);
}

void prepararAula(){
    sleep(1);
    printf("Professor está preparando a aula!");
}

void atenderAlunos(){
    if(monitor.alunosDuvidaCount == NUM_ALUNOS_DUVIDA){
        sleep(1);
        printf("Estou atendendo os alunos...\n");
        for(int i = 1; i <= NUM_ALUNOS_DUVIDA; i++){
            pthread_cond_signal(&monitor.prAtenderAlunos);
        }
    }
}

void darAula(){
    pthread_cond_wait(&monitor.alunosPresentes, &monitor.mutex); //espera pela sinalização de que todos os alunos chegaram
    printf("Vou dar aula!\n");
    sleep(1);
    pthread_cond_broadcast(&monitor.prDarAula); //sinaliza para todos os alunos de SO que a aula vai começar
}

void dispensarAlunos(){
    sleep(1);
    printf("Aula acabou, dispensando alunos...\n");
    pthread_cond_broadcast(&monitor.fimAula); //sinaliza para todos os alunos de SO que a aula acabou
}

void irEmboraCasa(){
    sleep(1);
    printf("Professor indo embora pra casa...");
}
