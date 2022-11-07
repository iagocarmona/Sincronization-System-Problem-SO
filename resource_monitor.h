#pragma once
#include <pthread.h>
#include <unistd.h>

#define NUM_GRUPO_ATENDE_ALUNOS 3 //número de alunos por grupo com dúvidas
#define NUM_ALUNOS_DUVIDA 5 //quantidade de alunos com dúvida
#define NUM_ALUNOS_SO 15
#define NUM_TURMA_SO 30 

#define TRUE 1
#define FALSE 0

/* --- controles de concorrência --- */
pthread_mutex_t mutex;
pthread_cond_t professor, 
alunosSO, 
alunosDuvida, 
fimAula, //sinalização de que a aula acabou 
alunosPresentes, //sinalização se todos os alunos de SO chegaram na sala
prDarAula, //sinalização de início da aula
prAtenderAlunos; //sinalização de começo de atendimento aos alunos com dúvida

/* --- recursos --- */
int alunosSOCount = 0; //variável que sinaliza o número de alunos de SO presentes na sala
int alunosDuvidaCount = 0;; //variável que sinaliza a quantidade de alunos com dúvidas

/* --- monitor operations --- */
void initMonitor();
void destroyMonitor();

