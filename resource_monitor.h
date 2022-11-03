#pragma once
#include <pthread.h>

#define NUM_TURMA_SO 30 
#define NUM_ATENDE_ALUNOS 5

#define TRUE 1
#define FALSE 0

/* --- controles de concorrência --- */
pthread_mutex_t mutex;
pthread_cond_t professor, alunosSO, alunosDuvida;

/* --- recursos --- */
int alunosSOCount;
int alunosDuvidaCount;

int professorDarAula;

/* --- monitor operations --- */
void initMonitor();
void destroyMonitor();

