#include <stdio.h>
#include "alunos_duvidas.h"
#include "../resource_monitor.h"

void *alunosDuvidasThread(void *ptr){
    int id = (intptr_t) ptr;

    srand(time(NULL) + (id * 2));
    int sleepTime = rand() % 5; 
    sleep(sleepTime);

    pthread_mutex_lock(&monitor.mutex); 

    chegarSalaProfessor(id); // todos os alunos com duvida podem chegar na porta do professor

    if(monitor.professor_atendendo == TRUE || monitor.qtd_alunos_so_na_sala == monitor.max_alunos_so){
        aguardarProfessor(id);
    }

    // espera professor liberar alunos na fila
    pthread_cond_wait(&monitor.aluno_fila_duvida, &monitor.mutex);

    // professor liberou entrada e os alunos podem tirar duvidas
    tirarDuvidas(id);

    // se o aluno tirou suas duvidas ele sai da sala do professor 
    sairSalaProfessor(id);

    // se nao tem mais alunos tirando duvidas, aqui sinaliza para os outros alunos que estavam na fila 
    if(monitor.qtd_alunos_tirando_duvidas == 0){
        monitor.professor_atendendo=FALSE;
        pthread_cond_signal(&monitor.alunos_duvidas);
    }

    pthread_mutex_unlock(&monitor.mutex);
}

void chegarSalaProfessor(int id){
    printf("\n\t\t🙋‍♂‍‍\b | alunoDuvida_%d chegou na porta do professor\n", id);
    monitor.qtd_alunos_duvida_esperando++;
    printf("\t\t🙋‍♂‍‍\b | %d/%d alunos com duvida aguardando atendimento\n", monitor.qtd_alunos_duvida_esperando, monitor.max_atendimento_professor);
    sleep(1);
}

void aguardarProfessor(int id){
    printf("\t\t🙋‍♂‍‍\b | alunoDuvida_%d está aguardando atendimento do professor.\n", id);
    pthread_cond_wait(&monitor.alunos_duvidas, &monitor.mutex);
    sleep(1);
}

void tirarDuvidas(int id){
    printf("\t\t🙋‍♂‍‍\b | alunoDuvida_%d vai tirar suas dúvidas...\n", id);
    monitor.qtd_alunos_duvida_esperando--;
    monitor.qtd_alunos_tirando_duvidas++;
    sleep(1);
    printf("\t\t🙋‍♂‍‍\b | alunoDuvida_%d tirou suas dúvidas e vai embora\n", id);
    monitor.qtd_alunos_tirando_duvidas--;
    sleep(1);
}

void sairSalaProfessor(int id){
    printf("\t\t🙋‍♂‍‍\b | alunoDuvida_%d saiu da sala do professor\n", id);
    sleep(1);
}
