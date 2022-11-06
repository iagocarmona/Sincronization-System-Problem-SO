#include <stdio.h>
#include "alunos_duvidas.h"
#include "../resource_monitor.h"

void *alunosDuvidasThread(void *ptr){
    int num = (intptr_t) ptr;
    chegarSalaProfessor();
    aguardarProfessor();
    tirarDuvidas();
    pthread_exit(0);
}

void chegarSalaProfessor(int num){
    printf("\t\talunoDuvida_%d chegou na porta do professor\n", num);
    alunosDuvidaCount++;//novo aluno quer tirar dúvidas - incrementa variável que sinaliza 
                        //a quantidade de alunos com dúvidas
    aguardarProfessor(num);
}

void aguardarProfessor(int num){
    printf("\t\talunoDuvida_%d está aguardando atendimento do professor.\n", num);
    pthread_cond_wait(&prAtenderAlunos, &mutex);//espera pela sinalização do professor 
                                                //para tirar suas dúvidas
    tirarDuvidas(num);
}

void tirarDuvidas(int num){
    printf("\t\talunoDuvida_%d vai tirar suas dúvidas...\n", num);
    sleep(2);//simulação de tirar dúvidas
    printf("\t\talunoDuvida_%d tirou suas dúvidas e vai embora\n", num);
    alunosDuvidaCount--; //aluno tirou dúvida e decremente variável de alunos com dúvida
}

void sairSalaProfessor(int num){
    printf("\t\talunoDuvida_%d saiu da sala do professor\n", num);
}
