#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "resource_monitor.h"

/* **************************************************************** */
/*                    THREAD ALUNOS DUVIDA                         */
/* **************************************************************** */

void *alunosDuvidasThread(void *ptr){
    int id = (intptr_t) ptr;

    srand(time(NULL) + (id * 2));
    int sleepTime = rand() % 5; 
    sleep(sleepTime);

    pthread_mutex_lock(&monitor.mutex); 

    if(!monitor.professor_dando_aula && !monitor.professor_atendendo){
        printf("\n\t\t🙋‍♂‍‍\b | alunoDuvida_%d chegou na porta do professor\n", id);
        monitor.qtd_alunos_duvida_esperando++;
        pthread_cond_wait(&monito.aluno_fila_duvida, &monitor.mutex);
    }else if(){
        
    }

    if(monitor.professor_atendendo){
        printf("\t\t🙋‍♂‍‍\b | alunoDuvida_%d está aguardando atendimento do professor.\n", id);
    }

    printf("\n\t\t🙋‍♂‍‍\b | Professor ocupado! alunoDuvida_%d vai embora\n", id);
    pthread_mutex_unlock(&monitor.mutex);
    pthread_exit(0);
}

// void chegarSalaProfessor(int id){
//     printf("\n\t\t🙋‍♂‍‍\b | alunoDuvida_%d chegou na porta do professor\n", id);
//     sleep(1);
// }

// void aguardarProfessor(int id){
//     printf("\t\t🙋‍♂‍‍\b | alunoDuvida_%d está aguardando atendimento do professor.\n", id);
//     sleep(1);
// }

void tirarDuvidas(int id){
    printf("\t\t🙋‍♂‍‍\b | alunoDuvida_%d vai tirar suas dúvidas...\n", id);
    sleep(1);
}

void sairSalaProfessor(int id){
    printf("\t\t🙋‍♂‍‍\b | alunoDuvida_%d saiu da sala do professor\n", id);
    sleep(1);
}

/* **************************************************************** */
/*                      THREAD ALUNOS SO                           */
/* **************************************************************** */

void *alunosSOThread(void *ptr){
    int id = (intptr_t) ptr;

    srand(time(NULL) + (id * 2));
    int sleepTime = rand() % 8; 
    sleep(sleepTime);

    pthread_mutex_lock(&monitor.mutex);

    if(monitor.professor_dando_aula == FALSE){
        printf("\n\t👨‍💻 | alunoSO_%d entra na sala\n", id);
        monitor.qtd_alunos_so_na_sala++;
    }

    pthread_mutex_unlock(&monitor.mutex);
    pthread_exit(0);
}

void entrarSalaAula(int id){
    printf("\n\t👨‍💻 | alunoSO_%d entra na sala\n", id);
    sleep(1);
}

void sairSalaAula(int id){
    printf("\t👨‍💻 | alunoSO_%d sai da sala\n", id);
    sleep(1);
}

void aguardarAula(int id){
    printf("\t👨‍💻 | alunoSO_%d aguardando professor começar a aula\n", id);
    sleep(1);
}

void obaAulaSO(int id){
    printf("\t👨‍💻 | alunoSO_%d Oba! Aula de SO!\n", id);
}

void chamarProfessor(int id){
    printf("\n\t👨‍💻 | alunoSO_%d Avisa que chegou todos os alunos.\n", id);
    sleep(1);
}

/* **************************************************************** */
/*                        THREAD PROFESSOR                         */
/* **************************************************************** */

void *professorThread(){
    pthread_mutex_lock(&monitor.mutex);

    while(monitor.qtd_alunos_so_na_sala < monitor.max_alunos_so){
        if(monitor.qtd_alunos_duvida_esperando == monitor.max_atendimento_professor){
            printf("\n👨‍🏫 | Vou atender os alunos...\n");
            sleep(1);
        }
        printf("\n👨‍🏫 | Professor está preparando a aula!\n");
        sleep(1);
    }
    printf("👨‍🏫 | Vou dar aula!\n");
    sleep(1);

    pthread_mutex_unlock(&monitor.mutex);
    pthread_exit(0);
}

void prepararAula(){
    printf("\n👨‍🏫 | Professor está preparando a aula!\n");
    sleep(1);
}

void atenderAlunos(){
    printf("\n👨‍🏫 | Vou atender os alunos...\n");
    sleep(1);
}

void darAula(){
    printf("👨‍🏫 | Vou dar aula!\n");
    sleep(1);
}

void dispensarAlunos(){
    printf("👨‍🏫 | Aula acabou, dispensando alunos...\n");
    sleep(1);
}

void irEmboraCasa(){
    printf("👨‍🏫 | Professor indo embora pra casa...\n");
    sleep(1);
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

    // espera o professor acabar
    pthread_join(professor, NULL);

    // Destroi o monitor
    destroyMonitor();

    printf("\n");
    return 0;
}
