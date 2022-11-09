#include <stdio.h>
#include "professor.h"
#include "../resource_monitor.h"

void *professorThread(){
    pthread_mutex_lock(&monitor.mutex);
    while(monitor.alunosDuvidaCount < NUM_GRUPO_ATENDE_ALUNOS){
        pthread_mutex_unlock(&monitor.mutex);
        prepararAula();
        pthread_mutex_lock(&monitor.mutex);
        if(monitor.alunosSOCount == NUM_ALUNOS_SO){
            pthread_mutex_unlock(&monitor.mutex);
            darAula();
            pthread_mutex_lock(&monitor.mutex);
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
        printf("entrei aq");
    pthread_mutex_unlock(&monitor.mutex);
    atenderAlunos();
    pthread_mutex_lock(&monitor.mutex);
    pthread_mutex_unlock(&monitor.mutex);
}

void prepararAula(){
    sleep(1);
    printf("Professor está preparando a aula!\n");
}

void atenderAlunos(){
    printf("Estou atendendo os alunos...\n");
    monitor.atendimento = TRUE;
    pthread_cond_signal(&monitor.prAtenderAlunos);
    sleep(1);
}

void darAula(){
    pthread_cond_wait(&monitor.alunosPresentes, &monitor.mutex); //espera pela sinalização de que todos os alunos chegaram
    monitor.professorEstaDandoAula = TRUE;
    printf("Vou dar aula!\n");
    pthread_cond_signal(&monitor.prDarAula); //sinaliza para todos os alunos de SO que a aula vai começar
    sleep(5);
}

void dispensarAlunos(){
    printf("Aula acabou, dispensando alunos...\n");
    pthread_cond_signal(&monitor.fimAula); //sinaliza para todos os alunos de SO que a aula acabou
}

void irEmboraCasa(){
    sleep(1);
    while(monitor.alunosSOCount != 0){
        //espera todos os alunos ir embora
    }
    printf("Professor indo embora pra casa...\n");
}

void finalizarAtendimento(){
    printf("Irei dar minha aula, encerrando atendimento de dúvidas...");
}
