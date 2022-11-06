#pragma once
#include <pthread.h>
#include <unistd.h>


#define NUM_GRUPO_ATENDE_ALUNOS 3
#define NUM_ALUNOS_DUVIDA 5
#define NUM_ALUNOS_SO 15
#define NUM_TURMA_SO 30 

#define TRUE 1
#define FALSE 0

/* --- controles de concorrência --- */
pthread_mutex_t mutex;
pthread_cond_t professor, alunosSO, alunosDuvida, prDarAula, prAtenderAlunos;

/* --- recursos --- */
int alunosSOCount;
int alunosDuvidaCount = 0;

/* --- monitor operations --- */
void initMonitor();
void destroyMonitor();

