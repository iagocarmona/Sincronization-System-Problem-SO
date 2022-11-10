#pragma once
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define NUM_GRUPO_ATENDE_ALUNOS 3 //número de alunos por grupo com dúvidas
#define NUM_ALUNOS_DUVIDA 5 //quantidade de alunos com dúvida
#define NUM_ALUNOS_SO 15
// #define NUM_TURMA_SO 30 

#define TRUE 1
#define FALSE 0

typedef struct Semaforo{
    /* --- controles de concorrência --- */
    sem_t mutex,
          alunosDuvida, // para controlec de grupo de dúvidas
          fimAula, //sinalização de que a aula acabou 
          alunosPresentes, //sinalização se todos os alunos de SO chegaram na sala
          profDarAula, //sinalização de início da aula
          profAtenderAlunos; //sinalização de começo de atendimento aos alunos com dúvida

    int alunosSOCount, //variável que sinaliza o número de alunos de SO presentes na sala
        alunosDuvidaCount, //variável que sinaliza a quantidade de alunos com dúvidas 
        professorEstaDandoAula, // variavel que sinaliza que o professor está dando aula 
        alunosDuvidaRestente, //variável de controle de quantos alunso ainda faltam para tirar dúvidas
        salaAtend,
        grupoAend; //variável de indicação do grupo que está sendo atendidfo
    
}Semaforo;

struct Semaforo semaforo;

struct timespec t;
time_t Time;

void initSemaforo(); //inicializa os valores do semáforo

