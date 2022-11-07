#include <stdio.h>
#include "alunos_so.h"
#include "../resource_monitor.h"

void *alunosSOThread(void *ptr){
    int num = (intptr_t) ptr;
    aguardarAula(num);
    pthread_cond_wait(&fimAula, &mutex);
    sairSalaAula(num);
    //pthread_exit(0);
}

void entrarSalaAula(int num){
    alunosSOCount++; //aluno de SO chegou, atualiza variável de quantidade de alunos na sala
    printf("\talunoSO_%d entra na sala\n", num);
    if(alunosSOCount == NUM_TURMA_SO){ //verifica se último aluno chegou
        chamarProfessor(num);// o último aluno chama professor para aula 
    }else{
        aguardarAula(num);
    }
}

void sairSalaAula(int num){
    printf("\talunoSO_%d sai na sala\n", num);
    pthread_exit(0);
}

void aguardarAula(int num){
    printf("\talunoSO_%d aguardando professor começar a aula\n", num);
    pthread_cond_wait(&prDarAula, &mutex);
    obaAulaSO(num);
}

void obaAulaSO(int num){
    printf("\talunoSO_%d fica feliz que vai ter aula\n", num);
}

void chamarProfessor(int num){
    printf("\talunoSO_%d chama professor\n", num);
    pthread_cond_signal(&alunosPresentes); //último aluno sinaliza para o professor que a aula pode começar
    pthread_cond_wait(&prDarAula, &mutex);
    obaAulaSO(num);
}