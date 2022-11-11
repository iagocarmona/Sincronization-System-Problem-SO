#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "resource_monitor.h"

/* **************************************************************** */
/*                    THREAD ALUNOS DUVIDA                         */
/* **************************************************************** */

void *alunosDuvidasThread(void *ptr){
    int id = (intptr_t) ptr;

    sleep(3);
    srand(time(NULL) + (id * 2));
    int sleepTime = rand() % 5; 
    sleep(sleepTime);

    pthread_mutex_lock(&monitor.mutex); 

    printf("\n\t\t🙋‍♂‍‍\b | alunoDuvida_%d chegou na porta do professor\n", id);
    monitor.qtd_alunos_duvida_esperando++;
    printf("\t\t🙋‍♂‍‍\b | %d/%d Alunos com duvida na fila\n", monitor.qtd_alunos_duvida_esperando, monitor.max_atendimento_professor);
    sleep(1);

    if(monitor.professor_atendendo){
        printf("\t\t🙋‍♂‍‍\b | alunoDuvida_%d está aguardando atendimento do professor.\n", id);
        sleep(1);
    }

    if(monitor.qtd_alunos_duvida_esperando == monitor.max_atendimento_professor){
        pthread_cond_signal(&monitor.professor);
    }
    
    pthread_cond_wait(&monitor.professor_atender, &monitor.mutex);
    printf("\n\t\t🙋‍♂‍‍\b | alunoDuvida_%d vai tirar suas dúvidas...\n", id);
    monitor.qtd_alunos_duvida_esperando--;
    printf("\t\t🙋‍♂‍‍\b | %d/%d Alunos com duvida na fila\n", monitor.qtd_alunos_duvida_esperando, monitor.max_atendimento_professor);

    pthread_cond_wait(&monitor.professor_acabou_o_atendimento, &monitor.mutex);
    monitor.qtd_alunos_duvida_atendendo--;
    printf("\n\t\t🙋‍♂‍‍\b | alunoDuvida_%d saiu da sala do professor\n\n", id);
   
    monitor.professor_atendendo = FALSE;

    pthread_mutex_unlock(&monitor.mutex);
    pthread_exit(NULL);
}

/* **************************************************************** */
/*                      THREAD ALUNOS SO                           */
/* **************************************************************** */

void *alunosSOThread(void *ptr){
    int id = (intptr_t) ptr;

    srand(time(NULL) + (id * 2));
    int sleepTime = rand() % 5; 
    sleep(sleepTime);

    pthread_mutex_lock(&monitor.mutex);

    printf("\n\t👨‍💻 | alunoSO_%d entra na sala\n", id);
    monitor.qtd_alunos_so_na_sala++;
    printf("\t👨‍💻 | alunoSO_%d aguardando professor começar a aula\n", id);
    printf("\t👨‍💻 | %d/%d Alunos em sala\n", monitor.qtd_alunos_so_na_sala, monitor.max_alunos_so);
    sleep(1);

    if(monitor.qtd_alunos_so_na_sala == monitor.max_alunos_so){
        printf("\n\t👨‍💻 | alunoSO_%d sou o ultimo aluno! vou avisar o professor!\n", id);
        if(monitor.professor_atendendo){
            printf("\n\t👨‍💻 | Aguardando atendimento dos alunos com dúvidas\n");
            time(&T);
            t.tv_sec = T + 5;
            t.tv_nsec = 0;
            pthread_cond_timedwait(&monitor.alunos_so, &monitor.mutex, &t);
        }
        pthread_cond_signal(&monitor.professor);
    }

    pthread_cond_wait(&monitor.professor_dar_aula, &monitor.mutex);
    printf("\t👨‍💻 | alunoSO_%d Oba! Aula de SO!\n", id);

    pthread_cond_wait(&monitor.professor_acabou_a_aula, &monitor.mutex);

    printf("\n\t👨‍💻 | alunoSO_%d sai da sala\n", id);
    monitor.qtd_alunos_so_na_sala--;
    printf("\t👨‍💻 | %d/%d Alunos em sala\n", monitor.qtd_alunos_so_na_sala, monitor.max_alunos_so);
    sleep(1);

    if(monitor.qtd_alunos_so_na_sala == 0){
        printf("\n\t👨‍💻 | Saíram todos os alunos da sala!\n");
       
        pthread_cond_signal(&monitor.alunos_sairam_da_sala);
    }

    pthread_mutex_unlock(&monitor.mutex);
    pthread_exit(NULL);
}

/* **************************************************************** */
/*                        THREAD PROFESSOR                         */
/* **************************************************************** */

void *professorThread(){
    pthread_mutex_lock(&monitor.mutex);

    printf("\n👨‍🏫 | Professor está preparando a aula!\n");

    inicio:
    pthread_cond_wait(&monitor.professor, &monitor.mutex);

    if(monitor.qtd_alunos_duvida_esperando == monitor.max_atendimento_professor){
        printf("\n👨‍🏫 | Vou atender os alunos...\n");
        monitor.professor_atendendo = TRUE;
        pthread_cond_broadcast(&monitor.professor_atender);

        time(&T);
        t.tv_sec = T + 5;
        t.tv_nsec = 0;
        pthread_cond_timedwait(&monitor.professor, &monitor.mutex, &t);

        printf("\n👨‍🏫 | Atendimento finalizado, dispensando alunos...\n\n");
        pthread_cond_broadcast(&monitor.professor_acabou_o_atendimento);

        // pthread_cond_wait(&monitor.alunos_duvida_sairam, &monitor.mutex);
        goto inicio;
    }

    if(monitor.qtd_alunos_so_na_sala == monitor.max_alunos_so){
        printf("\n👨‍🏫 | Vou dar aula!\n\n");
        pthread_cond_broadcast(&monitor.professor_dar_aula);
    }

    time(&T);
    t.tv_sec = T + 5;
    t.tv_nsec = 0;
    pthread_cond_timedwait(&monitor.professor, &monitor.mutex, &t);
    
    printf("\n👨‍🏫 | Aula acabou, dispensando alunos...\n\n");
    pthread_cond_broadcast(&monitor.professor_acabou_a_aula);

    pthread_cond_wait(&monitor.alunos_sairam_da_sala, &monitor.mutex);

    sleep(1);
    printf("\n👨‍🏫 | Professor indo embora pra casa...\n");

    pthread_mutex_unlock(&monitor.mutex);
    pthread_exit(NULL);
}

int main()
{
    pthread_t professor;
    pthread_t alunos_so[NUM_ALUNOS_SO];
    pthread_t alunos_duvidas[NUM_ALUNOS_DUVIDA];

    // Inicializa o monitor
    initMonitor();

    // professor
    if(pthread_create(&professor, NULL, (void *)professorThread, NULL) != 0){
        printf("\nERROR: Falha na criação da thread do professor.");
    }

    // alunos_so
    for(int i=1; i <= NUM_ALUNOS_SO; i++) {
        if(pthread_create(&(alunos_so[i]), NULL, (void *)alunosSOThread, (void *)(intptr_t)(i)) != 0){
            printf("\nERROR: Falha na criação da thread dos alunos de SO.");
        }
    }

    // alunos_duvidas
    for(int i=1; i <= NUM_ALUNOS_DUVIDA; i++) {
        if(pthread_create(&(alunos_duvidas[i]), NULL, (void *)alunosDuvidasThread, (void *)(intptr_t)(i)) !=0){
            printf("\nERROR: Falha na criação da thread dos alunos com dúvidas.");
        }
    }

    for(int i=1; i <= NUM_ALUNOS_SO; i++) {
        pthread_join(alunos_so[i], NULL);
    }

    for(int i=1; i <= NUM_ALUNOS_DUVIDA; i++) {
        pthread_join(alunos_duvidas[i], NULL);
    }

    // espera o professor acabar
    pthread_join(professor, NULL);

    // Destroi o monitor
    destroyMonitor();

    printf("\n");
    return 0;
}
