#include <stdio.h>
#include "alunos_so.h"
#include "../resource_monitor.h"

void *alunosSOThread(void *ptr){
    int num = (intptr_t) ptr;

    srand(time(NULL) + (num * 2));
    int sleepTime = rand() % 5; 
    sleep(sleepTime);

    pthread_mutex_lock(&monitor.mutex);
    entrarSalaAula(num);
    sairSalaAula(num);
    pthread_mutex_unlock(&monitor.mutex);
}

void entrarSalaAula(int num){
    monitor.alunosSOCount++; //aluno de SO chegou, atualiza variável de quantidade de alunos na sala
    sleep(1);
    printf("\talunoSO_%d entra na sala\n", num);
    printf("\t%d/%d Alunos em sala.\n", monitor.alunosSOCount, NUM_ALUNOS_SO);
    if(monitor.alunosSOCount == NUM_ALUNOS_SO){ //verifica se último aluno chegou
        printf("\tTODOS OS ALUNOS CHEGARAM!\n");
        chamarProfessor(num);// o último aluno chama professor para aula 
    }else{
        aguardarAula(num);
    }
}

void sairSalaAula(int num){
    sleep(1);
    pthread_cond_wait(&monitor.fimAula, &monitor.mutex);
    monitor.alunosSOCount--;
    printf("\talunoSO_%d sai da sala\n", num);
}

void aguardarAula(int num){
    sleep(1);
    printf("\talunoSO_%d aguardando professor começar a aula\n", num);
    pthread_cond_wait(&monitor.prDarAula, &monitor.mutex);
}

void obaAulaSO(int num){
    sleep(1);
    printf("\talunoSO_%d Oba! Aula de SO!\n", num);
}

void chamarProfessor(int num){
    sleep(1);
    printf("\talunoSO_%d Avisa que chegou todos os alunos.\n", num);
    // pthread_cond_signal(&monitor.alunosPresentes); //último aluno sinaliza para o professor que a aula pode começar
    pthread_cond_wait(&monitor.prDarAula, &monitor.mutex);
    obaAulaSO(num);
}