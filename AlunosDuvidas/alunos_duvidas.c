#include <stdio.h>
#include "alunos_duvidas.h"
#include "../semaforo.h"

void *alunosDuvidasThread(void *ptr){
    int num = (intptr_t) ptr;

    srand(time(NULL) + (num * 2));
    int sleepTime = rand() % 5; 
    sleep(sleepTime);
 
    if(!semaforo.professorEstaDandoAula){ //se o professor não está dando aula, vai tirar sua dúvida
        chegarSalaProfessor(num);
    }else{
        professorDandoAula(num);
    }
    
}

void chegarSalaProfessor(int num){
    sleep(1);
    if(!semaforo.professorEstaDandoAula){
        printf("\t\talunoDuvida_%d chegou na porta do professor\n", num);
        semaforo.alunosDuvidaCount++; //novo aluno quer tirar dúvidas - incrementa variável que sinaliza a quantidade de alunos com dúvidas
        printf("\t\t%d/%d AlunosDuvida esperando atendimento.\n", semaforo.alunosDuvidaCount, NUM_GRUPO_ATENDE_ALUNOS);
        aguardarProfessor(num);
    } else{
        professorDandoAula(num);
    }
}

void aguardarProfessor(int num){
    sleep(1);
    if(!semaforo.professorEstaDandoAula){
        printf("\t\talunoDuvida_%d está aguardando atendimento do professor.\n", num);
        sem_wait(&semaforo.profAtenderAlunos); //espera pela sinalização do professor para tirar suas dúvidas
        tirarDuvidas(num);
    } else{
        professorDandoAula(num);
    }
}

void tirarDuvidas(int num){
    if(!semaforo.professorEstaDandoAula){
        printf("\t\talunoDuvida_%d vai tirar suas dúvidas...\n", num);
        sleep(1); //simulação de tirar dúvidas
        printf("\t\talunoDuvida_%d tirou suas dúvidas e vai embora\n", num);
        sairSalaProfessor();
        semaforo.alunosDuvidaRestante--;
        semaforo.alunosDuvidaCount--; //aluno tirou dúvida e decremente variável de alunos com dúvida
    } else{
        professorDandoAula(num);
    }
}

void sairSalaProfessor(int num){
    sleep(1);
    printf("\t\talunoDuvida_%d saiu da sala do professor\n", num);
}

void professorDandoAula(int num){
    printf("\t\tProfessor está dando aula! AlunoDuvida_%d indo embora.", num);
    pthread_exit(0);
}