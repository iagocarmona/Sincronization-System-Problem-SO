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
    while(semaforo.alunosSOCount < NUM_ALUNOS_SO){
        printf("Professor está preparando a aula!\n");
    }
    darAula();
    dispensarAlunos();
    irEmboraCasa();
}

void atenderAlunos(){
    while(semaforo.alunosSOCount < NUM_ALUNOS_SO && semaforo.alunosDuvidaRestante >= NUM_GRUPO_ATENDE_ALUNOS){
        printf("Estou atendendo os alunos...\n");
        sem_post(&semaforo.profAtenderAlunos); //sinaliza começo de atendimento
        sleep(1);
    }
    //caso o motivo de saída do laço seja que todos os alunos chegaram, o professor vai dar aula, 
    //caso esse não seja o motivo, ele volta a preparar a aula
    if(semafor.alunosSOCount == NUM_ALUNOS_SO){
        darAula();
    } else{
        prepararAula();
    }
}

void darAula(){
    sem_wait(&semaforo.alunosPresentes); //espera pela sinalização de que todos os alunos chegaram
    semaforo.professorEstaDandoAula = TRUE; //avisa que está dando aula para os alunos com dúvida
    printf("Vou dar aula!\n");
    for(int i = 1; i <= NUM_ALUNOS_SO; i++){
        sem_post(&semaforo.profDarAula); //sinaliza para todos os alunos de SO que a aula vai começar
    }
    sleep(5); //simulação de dando aula
    dispensarAlunos();
}

void dispensarAlunos(){
    printf("Aula acabou, dispensando alunos...\n");
    for(int i = 1; i <= NUM_ALUNOS_SO; i++){
        sem_post(&semaforo.fimAula); //sinaliza para os alunos de SO que a aula acabou
    }
}

void irEmboraCasa(){
    sleep(1);
    while(semaforo.alunosSOCount != 0){
        printf("Professor está esperando todos os alunos saírem da sala\n");
    }
    printf("Último aluno foi embora!\n");
    printf("Professor indo embora pra casa...");
}
