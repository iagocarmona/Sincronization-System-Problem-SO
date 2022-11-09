#include <stdio.h>
#include "alunos_duvidas.h"
#include "../resource_monitor.h"

void *alunosDuvidasThread(void *ptr){
    int num = (intptr_t) ptr;

    srand(time(NULL) + (num * 2));
    int sleepTime = rand() % 5; 
    sleep(sleepTime);

    pthread_mutex_lock(&monitor.mutex);
    if(!monitor.professorEstaDandoAula){
        chegarSalaProfessor(num);
        //aguardarProfessor(num);
        //tirarDuvidas(num);
    }else{
        professorEstaDandoAula(num);
    }
    pthread_mutex_unlock(&monitor.mutex);
}

void chegarSalaProfessor(int num){
    sleep(1);
    printf("\t\talunoDuvida_%d chegou na porta do professor\n", num);
    
    if(!monitor.professorEstaDandoAula){
        monitor.alunosDuvidaCount++; //novo aluno quer tirar dúvidas - incrementa variável que sinaliza a quantidade de alunos com dúvidas
        //printf("\t\t%d/%d AlunosDuvida esperando atendimento.\n", monitor.alunosDuvidaCount, NUM_GRUPO_ATENDE_ALUNOS);
        aguardarProfessor(num);
    } else{
        professorEstaDandoAula(num);
    }
}

void aguardarProfessor(int num){
    sleep(1);
    printf("\t\talunoDuvida_%d está aguardando atendimento do professor.\n", num);
    pthread_cond_wait(&monitor.prAtenderAlunos, &monitor.mutex); //espera pela sinalização do professor para tirar suas dúvidas
    tirarDuvidas(num);
}

void tirarDuvidas(int num){
    printf("\t\talunoDuvida_%d vai tirar suas dúvidas...\n", num);
    sleep(1); //simulação de tirar dúvidas
    printf("\t\talunoDuvida_%d tirou suas dúvidas e vai embora\n", num);
    sairSalaProfessor(num);
    monitor.alunosDuvidaCount--; //aluno tirou dúvida e decremente variável de alunos com dúvida
}

void sairSalaProfessor(int num){
    sleep(1);
    printf("\t\talunoDuvida_%d saiu da sala do professor\n", num);
}

void professorEstaDandoAula(int num){
    printf("\t\tProfessor está dando aula! AlunoDuvida_%d indo embora.", num);
    pthread_exit(0);
}