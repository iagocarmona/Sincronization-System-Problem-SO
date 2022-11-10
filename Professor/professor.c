#include <stdio.h>
#include "professor.h"
#include "../resource_semaforo.h"

void *professorThread(){
    while(semaforo.alunosDuvidaCount < NUM_GRUPO_ATENDE_ALUNOS){//não preencheu grupo de dúvidas
        prepararAula();
        if(semaforo.alunosSOCount == NUM_ALUNOS_SO){ //todos os alunos estão na sala
            darAula();   
            dispensarAlunos();
            irEmboraCasa();
        }
    }
        // while(monitor.alunosSOCount < NUM_ALUNOS_SO){
        //     pthread_mutex_unlock(&monitor.mutex);
        //     prepararAula();
        //     pthread_mutex_lock(&monitor.mutex);
        //     if(monitor.alunosDuvidaCount == NUM_GRUPO_ATENDE_ALUNOS && monitor.professorEstaDandoAula == FALSE){
        //         pthread_mutex_unlock(&monitor.mutex);
        //         atenderAlunos();
        //         pthread_mutex_lock(&monitor.mutex);
        //     }
        // }
    atenderAlunos(); //começa atendimento dos alunos com dúvida
}

void prepararAula(){
    sleep(1);
    printf("Professor está preparando a aula!\n");
}

void atenderAlunos(){
    printf("Estou atendendo os alunos...\n");
    sem_post(&semaforo.profAtenderAlunos); //sinaliza começo de atendimento
    sleep(1);
}

void darAula(){
    sem_wait(&semaforo.alunosPresentes); //espera pela sinalização de que todos os alunos chegaram
    semaforo.professorEstaDandoAula = TRUE; //avisa que está dando aula para os alunos com dúvida
    printf("Vou dar aula!\n");
    sem_post(&semaforo.profDarAula); //sinaliza para todos os alunos de SO que a aula vai começar
    sleep(5);
}

void dispensarAlunos(){
    printf("Aula acabou, dispensando alunos...\n");
    sem_post(&semaforo.fimAula); //sinaliza para todos os alunos de SO que a aula acabou
}

void irEmboraCasa(){
    sleep(1);
    printf("Professor indo embora pra casa...");
}
