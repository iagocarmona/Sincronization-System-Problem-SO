#include <stdio.h>
#include "alunos_so.h"
#include "../resource_semaforo.h"

void *alunosSOThread(void *ptr){
    int num = (intptr_t) ptr;

    srand(time(NULL) + (num * 2));
    int sleepTime = rand() % 5; 
    sleep(sleepTime);
  
    entrarSalaAula(num);
    sairSalaAula(num);
}

void entrarSalaAula(int num){
    semaforo.alunosSOCount++; //aluno de SO chegou, atualiza variável de quantidade de alunos na sala
    sleep(1);
    printf("\talunoSO_%d entra na sala\n", num);
    printf("\t%d/%d Alunos em sala.\n", semaforo.alunosSOCount, NUM_ALUNOS_SO);
    if(semaforo.alunosSOCount == NUM_ALUNOS_SO){ //verifica se último aluno chegou
        printf("\tTODOS OS ALUNOS CHEGARAM!");
        chamarProfessor(num);// o último aluno chama professor para aula 
    }else{
        // se não for o último alunos, ele aguarda na sala
        aguardarAula(num);
    }
}

void sairSalaAula(int num){
    sleep(1);
    sem_wait(&semaforo.fimAula); //espera pela sinalização de fim da aula para poder ir embora
    printf("\talunoSO_%d sai da sala\n", num);
}

void aguardarAula(int num){
    sleep(1);
    printf("\talunoSO_%d aguardando professor começar a aula\n", num);
    sem_wait(&semaforo.profDarAula); //espera pelo início da aula
    obaAulaSO(num); 
}

void obaAulaSO(int num){
    sleep(1);
    printf("\talunoSO_%d Oba! Aula de SO!\n", num);
}

void chamarProfessor(int num){
    sleep(1);
    printf("\talunoSO_%d Avisa que chegou todos os alunos.\n", num);
    sem_post(&semaforo.alunosPresentes); //último aluno sinaliza para o professor que a aula pode começar
    sem_wait(&semaforo.profDarAula);
    obaAulaSO(num);
}