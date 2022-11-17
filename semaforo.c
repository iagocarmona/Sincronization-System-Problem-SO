/**
 * @file semaforo.c
 * @author Thiago Gariani Quinto
 * @author Iago Ortega Carmona
 * @author Reginaldo Gregoria de Souza Neto
 * @brief Programa feito usando semáforos que simula a seguinte situação: o professor está preparando aula de SO, durante esse processo,
 * ele só pode ser interrompido se todos os alunos de SO chegarem na sala ou se chegar um grupo de dúvidas (não necessariamente de SO).
 * Se durante o atendimento de dúvidas chegar um novo grupo, este irão esperar o atual atendimento terminar. Os alunos de SO possuem 
 * sobre os alunos com dúvidas. Quando o último aluno de SO chegar, este irá chamar o professor.
 *
 * @version 0.8
 * Data de criação: 06/11/2022
 * Date de modificação: 16/11/2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Defines
#define N_ALUNOS_SO 40 //quantidadde de alunos da turma de SO
#define N_ALUNOS_DUVIDA 20 //quantidade de alunos com duvida
#define N_GRUPOS_DUVIDA 3 //quantidade do grupo de dúvidas

// Semaforos
sem_t sem_dar_aula; //sinalização de professor dar aula
sem_t sem_atender_aluno; //sinalização de atendimento 
sem_t sem_sair_sala; //sinalização de que os alunos podem sair da sala de aula
sem_t sem_sala_vazia; //sinalização de que a sala está de aula vazia
sem_t sem_sala_lotada; //sinalização de que a sala de aula está lotada
sem_t sem_dispensar_aluno; //sinalização de que os alunos podem irem embora
sem_t sem_atendimento; //sinalização de que acabou aatendimento de dúvidas

// Variaveis globais
int quant_alunos_sala = 0; //contador da quantidade de alunos de SO na sala
int quant_alunos_duvida = 0; //contador da quantidade de alunos om dúvida
int quant_alunos_esperando_sala = 0; //contador da quantidade de alunos de SO esperando na sala 
int prepAula = 0; //variável que sinaliza que o professor começou a preparar a aula
int grupos_duvidas = 0;//contador de grupos com dúvida
int alunos_grupo; //contador para verificar se o grupo foi atendido
int iniAulaSO = 0; //variável para mostrar que a aula começou
int alunosDuvidasFila;
int i;
int atendimento; //verificação se novo grupo pode ir

// Instancias de funcoes
void *professor();
void *aluno_so(void *arg);
void *aluno_duvida(void *arg);

/****************************************************PROFESSOR*****************************************************************/

/**
 * @brief função que o professor realiza, na qual ele verifica se oque fez com que ele parasse de preparar aula. Além disso, 
 * ele espera pela sinalização de que os alunos chegaram, após isso, dá início à aula e após o fim sinaliza aos alunos que 
 * eles podem ir embora. Para ir embora o professor espera a saída de todos os alunos da sala.
 * 
 * @param arg 
 * @return void* 
 */
void *professor(){
    
    //Preparar Aula
        printf("👨‍🏫O professor esta preparando atividades em sua sala!\n\n");
        prepAula = 1;
  
    //fica no laço esperando se algo vai mudar seu estado
    while(quant_alunos_esperando_sala < N_ALUNOS_SO && quant_alunos_duvida < N_ALUNOS_DUVIDA){}

    //verifica oque resultou na mudança de estado, se foi a chegada de alunos com dúvida entra no IF 
    if(quant_alunos_duvida == N_ALUNOS_DUVIDA){
        
        while(grupos_duvidas > 0 || quant_alunos_esperando_sala < N_ALUNOS_SO){  
            
            //fica no laço enquanto uma das condições forem satisfeitas
        }
        
    } 

        sem_post(&sem_atendimento); //sinaliza de que acabou atendimento

        sem_wait(&sem_sala_lotada); //professor espera pela sinalização de chegada de todos os alunos
        
        printf("👨‍🏫 O professor vai começar a aula!\n\n"); 
        sleep(2);

        for(i = 1; i <= N_ALUNOS_SO; i++){
            sem_post(&sem_dar_aula); //sinaliza para os alunos de SO que a aula vai começar
        }

        printf("👨‍🏫 A aula acabou, vou liberar os alunos!\n\n");
        sleep(2);

        for(i = 1; i <= N_ALUNOS_SO; i++){
            sem_post(&sem_dispensar_aluno); //sinalização para os alunos irem embora
        }

        sem_wait(&sem_sala_vazia); //espera pela sinalização de que a sala está vazia
        printf("👨‍🏫 O professor vai embora para casa!\n\n");

        pthread_exit(0);
}


/***********************************ALUNOS SO************************************************************/

/**
 * @brief função que contém o que os alunos de SO irão fazer, as ação realizadas por eles são a sinalização
 * ao professor de que todos chegaram para a aula, além disso, sinalizam também ao professor que todos foram 
 * embora ao final da aula. Quando o professor sinaliza o início da aula, todos exclamam sua felicidade.
 * 
 * @param arg ID do aluno de SO
 * @return void* 
 */
void *aluno_so(void *arg){

    while(!prepAula){}

    //geração aleatória de alunos de SO
    int id_so = *(int*)arg;
    sleep(3);
    srand(time(NULL) + (id_so * 2));
    int sleepTime = rand() % 5; 
    sleep(sleepTime);

    // Aluno de SO entra na sala
    printf("\t👨‍💻 Aluno_SO_%d entrou na sala\n\n", id_so);
    quant_alunos_sala++;
    
    // Aluno de SO aguarda o inicio da aula
    printf("\t👨‍💻 Aluno_SO_%d esta aguardando a aula\n\n", id_so);
    quant_alunos_esperando_sala++;

    if(quant_alunos_esperando_sala == N_ALUNOS_SO){
        printf("\tA SALA ESTA CHEIA!\n\n");     
        sem_wait(&sem_atendimento); //espera pela sinalização de que acabou atendimento
        iniAulaSO = 1; //motra que aula começou
        alunosDuvidasFila = (grupos_duvidas * N_GRUPOS_DUVIDA) - quant_alunos_duvida;
        if(alunosDuvidasFila > 0){
            for(int i = 1; i <= alunosDuvidasFila; i++){
                sem_post(&sem_atender_aluno);
            }
        }
        sem_post(&sem_sala_lotada); //sinaliza que a sala de aula está cheia
        printf("\t👨‍💻 O Aluno_SO_%d foi chamar o professor.\n\n", id_so);
    }

    sem_wait(&sem_dar_aula); //espera pela sinalização de que a aula vai começar
    printf("\t👨‍💻 Oba aula de SO! %d\n\n", id_so);
   
    sem_wait(&sem_dispensar_aluno); //espera pela sinalização de uqe pode dair da sala
    printf("\t👨‍💻 Aluno %d saiu da sala!\n\n", id_so);
    quant_alunos_sala--; //decrementa contador de alunos de SO na sala

    if(quant_alunos_sala == 0){ //se todos os alunos foram embora, sinaliza para o professor 
        printf("\tSALA VAZIA!!!\n\n");
        sem_post(&sem_sala_vazia); //sinaliza para o professor que a sala de aula está vazia
    }
    
    pthread_exit(0);
}


/********************************************************ALUNOS DÚVIDA*************************************************************/
/**
 * @brief função que contém as ações que os aluno com dúvidas irão realizar, como o aguardo da atendimento
 * do professor, ao terminarem de serem atendidos, o grupo atual s
 * 
 * @param arg ID do aluno com dúvidas
 * @return void* 
 */
void *aluno_duvida(void *arg){

    while(!prepAula){}
    
    //geração aleatória
    int id_duvida = *(int*)arg;
    sleep(3);
    srand(time(NULL) + (id_duvida * 2));
    int sleepTime = rand() % 5; 
    sleep(sleepTime);

    //Aluno com duvida chega para falar com o professor
    printf("\t\t🙋‍ Aluno_DUVIDA_%d chegou na sala do professor\n\n", id_duvida);
    quant_alunos_duvida++; //incrementa quantidade de alunos com dúvida

     printf("\t\t🙋‍ Aluno_DUVIDA_%d esta aguardando o professor\n\n", id_duvida);
   
    if(quant_alunos_esperando_sala == N_ALUNOS_SO){ //se todos os alunos de SO já chegaram, aluno com dúvida vai embora
        printf("\t\t🙋‍ Todos os alunos de SO chegaram, assim, Aluno_Duvida_%d vai embora\n\n", id_duvida);
        quant_alunos_duvida--; //decrementa contador de alunos com dúvida
        pthread_exit(0);
    }

    
    if((quant_alunos_duvida % N_GRUPOS_DUVIDA) == 0){ //verifica se há um grupo com dúvidas

        alunos_grupo = N_GRUPOS_DUVIDA; //atribui para a variável o número que contém o número de alunos do grupo
        grupos_duvidas++; //incrementa variável de grupos com dúvida
        while(atendimento){
            //espera que novo grupo termine
        } 
        printf("\t\tO grupo de duvidas lotou!\n\n");
        printf("👨‍🏫 Professor vai atender o grupo!\n\n");
        for(i = 1; i <= N_GRUPOS_DUVIDA; i++){
            sem_post(&sem_atender_aluno); //permite aos alunos com dúvida irem tirar suas dúvidas
        }
        atendimento = 1; //mostra que há um grupo que será atendido
    }

        sem_wait(&sem_atender_aluno); //espera pela sinalização de que é possível tirar dúvidas
        if(iniAulaSO){
            printf("\t\t🙋‍ Todos os alunos de SO chegaram, assim, Aluno_Duvida_%d vai embora\n\n", id_duvida);
            quant_alunos_duvida--;
            pthread_exit(0);
        }

        printf("\t\t🙋‍ Aluno_DUVIDA %d foi atendido!\n\n", id_duvida);
            alunos_grupo--; //foi atendido, decrementa contador
        if(alunos_grupo == 0){ //todo o grupo foi atendido
            atendimento = 0; //novo grupo pode ir 
            grupos_duvidas--; //decrementa contador de grupo de dúvidas
            printf("\t\tGRUPO ATENDIDO!!!\n\n");
            
        } 
    
        pthread_exit(0);
}

int main(){
    
    // Inicializa os semáforos para sinalização
    sem_init(&sem_atender_aluno, 0, 0);
    sem_init(&sem_sair_sala, 0, 0);
    sem_init(&sem_sala_vazia, 0, 0);
    sem_init(&sem_sala_lotada, 0, 0);
    sem_init(&sem_dispensar_aluno, 0, 0);
    sem_init(&sem_atendimento, 0 , 0);

    pthread_t professor_thread;
    pthread_t aluno_so_thread[N_ALUNOS_SO];
    pthread_t aluno_duvida_thread[N_ALUNOS_DUVIDA];

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