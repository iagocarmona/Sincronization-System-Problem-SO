#pragma once
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define NUM_GRUPO_ATENDE_ALUNOS 3 //número de alunos por grupo com dúvidas
#define NUM_ALUNOS_DUVIDA 5 //quantidade de alunos com dúvida
#define NUM_ALUNOS_SO 15
// #define NUM_TURMA_SO 30 

#define TRUE 1
#define FALSE 0

typedef struct Monitor{
    /* --- controle de concorrência --- */
    pthread_mutex_t mutex;

    pthread_cond_t professor;
    pthread_cond_t alunosSO;
    pthread_cond_t alunosDuvida; 

    int qtd_alunos_duvida_esperando;
    int professor_atendendo;
    int qtd_alunos_tirando_duvidas;

}Monitor;

struct Monitor monitor;

struct timespec t;
time_t T;

/* --- monitor operations --- */
void initMonitor();
void destroyMonitor();

