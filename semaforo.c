#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

// Defines
#define N_ALUNOS_SO 20
#define N_ALUNOS_DUVIDA 5
#define N_GRUPOS_DUVIDA 3

// Semaforos
sem_t sem_dar_aula;
sem_t sem_atender_aluno;
sem_t sem_sair_sala;
sem_t sem_sala_vazia;
sem_t sem_sala_lotada;
sem_t sem_dispensar_aluno;
sem_t sem_prof_livre;

// Variaveis globais
int quant_alunos_sala = 0;
int quant_alunos_duvida = 0;
int quant_alunos_esperando_sala = 0;
int quant_oba = 0;
int cont=0;
int prepAula = 0;
int grupos_duvidas = 0;

// Instancias de funcoes
void *professor(void *arg);
void *aluno_so(void *arg);
void *aluno_duvida(void *arg);

// Funcoes
void *professor(void *arg){
    
    //Preparar Aula
        printf("O professor Campiolo esta preparando atividades em sua sala. \nEm breve, %d pessoas terao aula de SO com o professor Campiolo.\nAlguns alunos entram na sala e outros o esperam para tirar duvidas do lado de fora.\n\n", N_ALUNOS_SO);
        prepAula = 1;
        
    if(cont==0){
        cont++;
    sem_post(&sem_prof_livre);
    }

    //fica no laço esperando se algo vai mudar seu estado
    while(quant_alunos_esperando_sala < N_ALUNOS_SO && quant_alunos_duvida < N_ALUNOS_DUVIDA){}

    if(quant_alunos_duvida == N_ALUNOS_DUVIDA){
        printf("Professor vai atender os grupos de dúvidas\n\n");
        while(grupos_duvidas > 0){

        }
        
    } 
        //professor espera pela pela chegada de todos os alunos
        sem_wait(&sem_sala_lotada);
        printf("O professor saiu para dar aula.\n\n");
        sleep(1);

        printf("O professor vai começar a aula!\n\n"); 
        sleep(2);
        for(int i = 1; i <= N_ALUNOS_SO; i++){
            sem_post(&sem_dar_aula);
        }

    //sem_post(&sem_dispensar_aluno);
        printf("A aula acabou, vou liberar os alunos!\n\n");
        sleep(1);
        for(int i = 1; i <= N_ALUNOS_SO; i++){
            sem_post(&sem_dispensar_aluno);
        }

        // Dispensar alunos
        sem_wait(&sem_sala_vazia);
        printf("O professor vai embora para casa!\n\n");
        return 0;
}

void *aluno_so(void *arg){

    while(!prepAula){}

    int id = *(int*)arg;
    sleep(3);
    srand(time(NULL) + (id * 2));
    int sleepTime = rand() % 5; 
    sleep(sleepTime);

    // Aluno de SO entra na sala
    printf("\tAluno_SO_%d entrou na sala\n\n", id);
    quant_alunos_sala++;
    // Aluno de SO aguarda o inicio da aula
    printf("\tAluno_SO_%d esta aguardando a aula\n\n", id);
    quant_alunos_esperando_sala++;

    if(quant_alunos_esperando_sala == N_ALUNOS_SO){
        printf("\tA SALA ESTA CHEIA!\n\n");     
        sem_wait(&sem_prof_livre);
        sem_post(&sem_sala_lotada);
        printf("\tO Aluno_SO_%d foi chamar o professor.\n\n", id);
        sem_post(&sem_prof_livre);
    }

    sem_wait(&sem_dar_aula);
    printf("\tOba aula de SO! %d\n\n", id);
   
    sem_wait(&sem_dispensar_aluno);
        printf("\tAluno %d saiu da sala!\n\n", id);
        quant_alunos_sala--;

    if(quant_alunos_sala == 0){
        printf("\tSALA VAZIA!!!\n\n");
        sem_post(&sem_sala_vazia);
    }
    //sleep(1);
    return NULL;
}

void *aluno_duvida(void *arg){
    while(!prepAula){}
    
    int id = *(int*)arg;
    sleep(3);
    srand(time(NULL) + (id * 2));
    int sleepTime = rand() % 5; 
    sleep(sleepTime);

     // Aluno com duvida chega para falar com o professor
    printf("\t\tAluno_DUVIDA_%d chegou no corredor\n\n", id);
    quant_alunos_duvida++;

     printf("\t\tAluno_DUVIDA_%d esta aguardando o professor\n\n", id);
    
    if(quant_alunos_duvida == N_GRUPOS_DUVIDA){
        if(quant_alunos_esperando_sala == N_ALUNOS_SO){
            printf("\t\tOs alunos de SO estão esperando a aula do professor, assim, Aluno_Duvida_%d vai embora\n\n", id);
            quant_alunos_duvida--;
            pthread_exit(NULL);
        }
        printf("\t\tO grupo de duvidas lotou!\n\n");
        grupos_duvidas++;
        sem_wait(&sem_prof_livre);
        sem_post(&sem_atender_aluno);
    }

        sem_wait(&sem_atender_aluno);
        printf("\t\tAluno_DUVIDA %d foi atendido!\n\n", id);
            quant_alunos_duvida--;
        if(quant_alunos_duvida == 0){
            grupos_duvidas--;
            printf("\t\tGRUPO ATENDIDO!!!\n\n");
            sem_post(&sem_prof_livre);
        } else{
            sem_post(&sem_atender_aluno);
        }    
}

int main(){
    
    // Inicialização dos semaforos
    sem_init(&sem_atender_aluno, 0, 0);
    sem_init(&sem_sair_sala, 0, 0);
    sem_init(&sem_sala_vazia, 0, 0);
    sem_init(&sem_sala_lotada, 0, 0);
    sem_init(&sem_dispensar_aluno, 0, 0);
    sem_init(&sem_prof_livre, 0, 0);

    // Criação das threads
    pthread_t professor_thread;
    pthread_t aluno_so_thread[N_ALUNOS_SO];
    pthread_t aluno_duvida_thread[N_ALUNOS_DUVIDA];


    // Cria argumentos para as threads
    int i;
    int *id_aluno_so;
    int *id_aluno_duvida;

    //Cria as threads
    pthread_create(&professor_thread, NULL, professor, NULL);

    for(i = 1; i <= N_ALUNOS_DUVIDA; i++){
            id_aluno_duvida = malloc(sizeof(int));
            *id_aluno_duvida = i;
            pthread_create(&aluno_duvida_thread[i], NULL, aluno_duvida, (void*) id_aluno_duvida);
        }

    for(i = 1; i <= N_ALUNOS_SO; i++){
        id_aluno_so = malloc(sizeof(int));
        *id_aluno_so = i;
        pthread_create(&aluno_so_thread[i], NULL, aluno_so, (void*) id_aluno_so);
    }
    

    // Espera pelas threads
    pthread_join(professor_thread, NULL);

    for(i = 0; i < N_ALUNOS_SO; i++){
        pthread_join(aluno_so_thread[i], NULL);
    }

    for(i = 0; i < N_ALUNOS_DUVIDA; i++){
        pthread_join(aluno_duvida_thread[i], NULL);
    }

    return 0;
}