#include <stdio.h>
#include "alunos_duvidas.h"
#include "../resource_monitor.h"

void *alunosDuvidasThread(void *ptr){
    int num = (intptr_t) ptr;

    srand(time(NULL) + (num * 2));
    int sleepTime = rand() % 5; 
    sleep(sleepTime);

   
    if(!semaforo.professorEstaDandoAula){
        chegarSalaProfessor(num);
        aguardarProfessor(num);
        tirarDuvidas(num);
    }else{
        printf("\t\tProfessor está dando aula! AlunoDuvida_%d indo embora.", num);
        pthread_exit(0);
    }
    
}

void chegarSalaProfessor(int num){
    sleep(1);
    printf("\t\talunoDuvida_%d chegou na porta do professor\n", num);
    semaforo.alunosDuvidaCount++; //novo aluno quer tirar dúvidas - incrementa variável que sinaliza a quantidade de alunos com dúvidas
    printf("\t\t%d/%d AlunosDuvida esperando atendimento.\n", semaforo.alunosDuvidaCount, NUM_GRUPO_ATENDE_ALUNOS);
    aguardarProfessor(num);
}

void aguardarProfessor(int num){
    sleep(1);
    printf("\t\talunoDuvida_%d está aguardando atendimento do professor.\n", num);
    sem_wait(&semaforo.prAtenderAlunos); //espera pela sinalização do professor para tirar suas dúvidas
    tirarDuvidas(num);
}

void tirarDuvidas(int num){
    printf("\t\talunoDuvida_%d vai tirar suas dúvidas...\n", num);
    sleep(1); //simulação de tirar dúvidas
    printf("\t\talunoDuvida_%d tirou suas dúvidas e vai embora\n", num);
    sairSalaProfessor();
    semaforo.alunosDuvidaCount--; //aluno tirou dúvida e decremente variável de alunos com dúvida
}

void sairSalaProfessor(int num){
    sleep(1);
    printf("\t\talunoDuvida_%d saiu da sala do professor\n", num);
}
