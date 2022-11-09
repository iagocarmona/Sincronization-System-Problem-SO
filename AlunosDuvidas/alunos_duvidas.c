#include <stdio.h>
#include "alunos_duvidas.h"
#include "../resource_monitor.h"

void *alunosDuvidasThread(void *ptr){
    int id = (intptr_t) ptr;

    srand(time(NULL) + (id * 2));
    int sleepTime = rand() % 3; 
    sleep(sleepTime);

    pthread_mutex_lock(&monitor.mutex); 

    while(!monitor.professor_atendendo || monitor.qtd_alunos_tirando_duvidas < NUM_GRUPO_ATENDE_ALUNOS){
        chegarSalaProfessor(id); // todos os alunos com duvida podem chegar na porta do professor
    }

    aguardarProfessor(id);

    pthread_mutex_unlock(&monitor.mutex);
}

void chegarSalaProfessor(int id){
    printf("\n\t\t🙋‍♂‍‍\b | alunoDuvida_%d chegou na porta do professor\n", id);
    monitor.qtd_alunos_duvida_esperando++;
    sleep(1);
}

void aguardarProfessor(int id){
    printf("\t\t🙋‍♂‍‍\b | alunoDuvida_%d está aguardando atendimento do professor.\n", id);
    pthread_cond_wait();
    sleep(1);
}

void tirarDuvidas(int id){
    printf("\t\t🙋‍♂‍‍\b | alunoDuvida_%d vai tirar suas dúvidas...\n", id);
    sleep(1);
    monitor.qtd_alunos_tirando_duvidas++;
    printf("\t\t🙋‍♂‍‍\b | alunoDuvida_%d tirou suas dúvidas e vai embora\n", id);
    sleep(1);
}

void sairSalaProfessor(int id){
    printf("\t\t🙋‍♂‍‍\b | alunoDuvida_%d saiu da sala do professor\n", id);
    sleep(1);
}
