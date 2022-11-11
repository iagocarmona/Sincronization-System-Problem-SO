#pragma once
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define NUM_GRUPO_ATENDE_ALUNOS 3 //número de alunos por grupo com dúvidas
#define NUM_ALUNOS_DUVIDA 5 //quantidade de alunos com dúvida
#define NUM_ALUNOS_SO 15

#define TRUE 1
#define FALSE 0

typedef struct Monitor{
    /* --- controle de concorrência --- */
    pthread_mutex_t mutex;

    pthread_cond_t professor;
    pthread_cond_t alunos_so;
    pthread_cond_t alunos_duvidas; 

    pthread_cond_t aluno_fila_duvida;
    pthread_cond_t aluno_fila_so;
    pthread_cond_t professor_acabou_a_aula;
    pthread_cond_t alunos_sairam_da_sala;
    pthread_cond_t professor_dar_aula;
    pthread_cond_t professor_atender;
    pthread_cond_t professor_acabou_o_atendimento;
    pthread_cond_t alunos_duvida_sairam;


    int qtd_alunos_duvida_esperando;
    int professor_atendendo;
    int professor_dando_aula;
    int max_atendimento_professor;
    int max_alunos_duvidas;
    int qtd_alunos_tirando_duvidas;
    int max_alunos_so;
    int qtd_alunos_so_na_sala;
    int aula_finalizada;
    int qtd_alunos_duvida_atendendo;

}Monitor;

struct Monitor monitor;

struct timespec t;
time_t T;

/* --- monitor operations --- */
void initMonitor();
void destroyMonitor();

