#include <stdio.h>
#include "alunos_so.h"
#include "../resource_monitor.h"

void *alunosSOThread(void *ptr){
    int id = (intptr_t) ptr;

    srand(time(NULL) + (id * 2));
    int sleepTime = rand() % 8; 
    sleep(sleepTime);

    pthread_mutex_lock(&monitor.mutex);

    if(monitor.qtd_alunos_so_na_sala < monitor.max_alunos_so){
        entrarSalaAula(id);
        aguardarAula(id);
    }else {
        printf("\n\tChegaram todos os alunos!");
        chamarProfessor(id);
    }

    if(monitor.professor_dando_aula == TRUE){
        obaAulaSO(id);
    }

    // espera finalizar a aula para sair da sala de aula
    pthread_cond_wait(&monitor.professor_acabou_a_aula, &monitor.mutex);

    // os alunos saem da sala de aula
    sairSalaAula();

    if(monitor.qtd_alunos_so_na_sala == 0){
        pthread_cond_signal(&monitor.alunos_sairam_da_sala);
    }

    pthread_mutex_unlock(&monitor.mutex);
}

void entrarSalaAula(int id){
    printf("\n\t👨‍💻 | alunoSO_%d entra na sala\n", id);
    monitor.qtd_alunos_so_na_sala++;
    printf("\t👨‍💻 | %d/%d alunos de SO aguardando\n", monitor.qtd_alunos_so_na_sala, monitor.max_alunos_so);
    sleep(1);
}

void sairSalaAula(int id){
    printf("\t👨‍💻 | alunoSO_%d sai da sala\n", id);
    monitor.qtd_alunos_so_na_sala--;
    printf("\t👨‍💻 | %d/%d alunos de SO em sala de aula\n", monitor.qtd_alunos_so_na_sala, monitor.max_alunos_so);
    sleep(1);
}

void aguardarAula(int id){
    printf("\t👨‍💻 | alunoSO_%d aguardando professor começar a aula\n", id);
    pthread_cond_wait(&monitor.alunos_so, &monitor.mutex);
    sleep(1);
}

void obaAulaSO(int id){
    printf("\t👨‍💻 | alunoSO_%d Oba! Aula de SO!\n", id);
}

void chamarProfessor(int id){
    printf("\n\t👨‍💻 | alunoSO_%d Avisa que chegou todos os alunos.\n", id);
    pthread_cond_signal(&monitor.aluno_fila_so);
    sleep(1);
}