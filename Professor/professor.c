#include "professor.h"
#include "../resource_monitor.h"

void *professorThread(){
    pthread_mutex_lock(&monitor.mutex);

    while(monitor.qtd_alunos_SO < NUM_ALUNOS_SO){
        while(monitor.qtd_alunos_duvida_esperando < NUM_GRUPO_ATENDE_ALUNOS){
            prepararAula();
        }
        atenderAlunos();
    }
    
    pthread_mutex_unlock(&monitor.mutex);
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
