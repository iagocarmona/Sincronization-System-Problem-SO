#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "Professor/professor.h"
#include "AlunosSO/alunos_so.h"
#include "AlunosDuvidas/alunos_duvidas.h"

#include "resource_monitor.h"

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
