#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

// Defines
#define N_ALUNOS_SO 20
#define N_ALUNOS_DUVIDA 8
#define N_GRUPOS_DUVIDA 3

// Semaforos
//sem_t sem_preparar_aula;
sem_t sem_dar_aula;
sem_t sem_atender_aluno;
sem_t sem_duvida_espera;
sem_t sem_sair_sala;
sem_t sem_sala_vazia;
sem_t sem_sala_lotada;
sem_t sem_grupo_duvida;
sem_t sem_alunos_duvida;
sem_t sem_dispensar_aluno;
sem_t sem_dispensar_aluno_duvida;
sem_t sem_corredor_vazio;
sem_t sem_prof_livre;
sem_t sem_notifica;

// Variaveis globais
int quant_alunos_sala = 0;
int quant_alunos_duvida = 0;
int quant_grupo_duvida = 0;
int quant_alunos_atendidos = 0;
int quant_alunos_esperando_sala = 0;
int quant_oba = 0;
int cont = 0;
int quant_alunos_esperando_corredor = 0;
int duvidas = 0;
int sala_Aula_SO = 0;
int i;
int alunosDuvidas = 0;
int alunosSO = 0;

// Instancias de funcoes
void *professor(void *arg);
void *aluno_so(void *arg);
void *aluno_duvida(void *arg);

// Funcoes
void *professor(void *arg){
    
    //Preparar Aula

        printf("O professor Campiolo esta preparando atividades em sua sala... \n"); 
        alunosDuvidas = 1;
        alunosSO = 1;
        sem_wait(&sem_notifica); //espera por uma ação que faz parar o ato de preparar a aula

    if(cont==0){
        cont++;
        sem_post(&sem_prof_livre); //mostra que esta disponivel
    }

    //verifica se o que o interrompeu foi a chegada dos alunos_duvidas ou a chegadas dos alunos_so
    //caso foi a dos alunos_duvida, entra no if, caso não foi, ele dará aula
    if(quant_alunos_duvida == N_GRUPOS_DUVIDA && quant_alunos_esperando_sala != N_ALUNOS_SO ){

        while(quant_alunos_sala != N_ALUNOS_SO){ //enquanto todos os alunos de SO não estiverem na sala
            if(quant_alunos_duvida == N_GRUPOS_DUVIDA){ //se o grupo de dúvidas está cheio, atende o grupo
                printf("Professor atendendo alunos duvida\n");
                sem_wait(&sem_corredor_vazio);
            }
        }

        sala_Aula_SO = 1;
    
    }


    sem_wait(&sem_sala_lotada); //espera a sinalização do último alunos de que todos estão na sala
        printf("O professor vai dar aula.\n\n");
        sleep(1);

    for(int i = 1; i <= N_ALUNOS_SO; i++){
        sem_post(&sem_dar_aula); //sinaliza para cada aluno que a aula vai começar
    }
    
        sleep(5); //simulação da aula

        printf("\nA aula acabou!\n\n");
        for(int i = 1; i <= N_ALUNOS_SO; i++){
            sem_post(&sem_dispensar_aluno); //sinaliza para todos os alunos que a aula acabou
        }
       
        sleep(2);

        // Esperando todos os alunos irem embora
        sem_wait(&sem_sala_vazia);
        printf("O professor vai embora para casa!\n\n");
        return 0;
}

void *aluno_so(void *arg){
    int id = *(int*)arg;

    while(!alunosSO){}

    // chegada aleatória
    srand(time(NULL) + (id * 2));
    int sleepTime = rand() % 5; 
    sleep(sleepTime);

    // Aluno de SO entra na sala
    printf("\tAluno_SO_%d entrou na sala\n", id);

    // Aluno de SO aguarda o inicio da aula
    printf("\tAluno_SO_%d esta aguardando a aula\n", id);
    quant_alunos_sala++;
    printf("\tAlunoSO %d/%d estão na sala\n", quant_alunos_sala, N_ALUNOS_SO);

    if(quant_alunos_sala == N_ALUNOS_SO){
        sem_post(&sem_notifica); //notifica professor da chegada de todos os alunos

        printf("\n\tA SALA ESTA CHEIA!\n\n");  
        sala_Aula_SO = 1;   
        sem_wait(&sem_prof_livre); //espera professor estar livre
        sem_post(&sem_sala_lotada); //sinaliza que todos os alunos estão na sala
        printf("\tO Aluno_SO_%d foi chamar o professor.\n\n", id);
    }

    sem_wait(&sem_dar_aula); //espera pela sinalização do professor de que a aula vai começar
        printf("\tOba aula de SO! %d\n", id);
   
    sem_wait(&sem_dispensar_aluno); //espera pela sinalização do professor de que a aula acabou
        printf("\tAluno %d saiu da sala!\n", id);
        quant_alunos_sala--;
    if(quant_alunos_sala == 0){ //todos os alunos foram embora
        printf("\n\tSALA VAZIA!!!\n\n");
        sem_post(&sem_sala_vazia); //sinaliza para o professor que todos os alunos foram embora
    } 
    //sleep(1);
    return NULL;
}

void *aluno_duvida(void *arg){
    int id = *(int*)arg;
    
    while(!alunosDuvidas){}

    //chegada aleatória
    srand(time(NULL) + (id * 2));
    int sleepTime = rand() % 5; 
    sleep(sleepTime);

     // Aluno com duvida chega para falar com o professor
    printf("\n\t\t>>> Aluno_DUVIDA_%d chegou no corredor\n", id);
    quant_alunos_duvida++;


    printf("\t\tAluno_DUVIDA_%d esta aguardando o professor\n\n", id);
    quant_alunos_esperando_corredor++;

    printf("\t\tAlunoDuvida %d/%d\n", quant_alunos_esperando_corredor, N_GRUPOS_DUVIDA);


    if(sala_Aula_SO){
        printf("\t\tProfessor está dando aula, aluno-Duvida_%d vai embora\n", id);
        pthread_exit(0);
    }

    if(quant_alunos_duvida == N_GRUPOS_DUVIDA){ //o grupo está cheio
        sem_post(&sem_notifica); //sinaliza para o professor que há um grupo de dúvidas
        printf("\t\tO grupo de duvidas lotou!\n");

        sem_wait(&sem_prof_livre); //espera pela disponibilidade do professor

        // if(quant_alunos_esperando_sala < N_ALUNOS_SO){
        //     printf("\t\tO professor esta atendendo as duvidas no corredor\n\n");
        //     sem_post(&sem_atender_aluno);
        // }
        sleep(1);

        for (i = 1; i <= N_GRUPOS_DUVIDA; i++){
                sem_post(&sem_atender_aluno);
            }
    };
        sem_wait(&sem_atender_aluno);
        printf("\t\tAluno_DUVIDA %d foi atendido!\n", id);
            quant_alunos_duvida--;

        if(quant_alunos_duvida == 0){
            printf("\n\t\tGRUPO ATENDIDO!!!\n\n");
            sem_post(&sem_corredor_vazio);
            sem_post(&sem_prof_livre);
            printf("\n\t\tO professor volta a preparar aulas em sua sala.\n");
        }     
}

int main(){
    
    // Inicialização dos semaforos
    sem_init(&sem_atender_aluno, 0, 0);
    sem_init(&sem_duvida_espera, 0, 0);
    sem_init(&sem_sair_sala, 0, 0);
    sem_init(&sem_sala_vazia, 0, 0);
    sem_init(&sem_sala_lotada, 0, 0);
    sem_init(&sem_grupo_duvida, 0, 0);
    sem_init(&sem_alunos_duvida, 0, 0);
    sem_init(&sem_corredor_vazio, 0, 0);
    sem_init(&sem_dispensar_aluno, 0, 0);
    sem_init(&sem_dispensar_aluno_duvida, 0, 0);
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

    /*
    for(i = 0; i < N_ALUNOS_SO; i++){
        pthread_join(aluno_so_thread[i], NULL);
    }

    for(i = 0; i < N_ALUNOS_DUVIDA; i++){
        pthread_join(aluno_duvida_thread[i], NULL);
    }
    */

    return 0;
}