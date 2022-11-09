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
    pthread_t alunos_duvida[NUM_ALUNOS_DUVIDA];

    // Inicializa o monitor
    initMonitor();

    // professor
    pthread_create(&professor, NULL, (void *)professorThread, NULL);

    // alunos_so
    for(int i=1; i <= NUM_ALUNOS_SO; i++) {
        pthread_create(&(alunos_so[i]), NULL, (void *)alunosSOThread, (void *)(intptr_t)(i));
    }

    // alunos_duvida
    for(int i=1; i <= NUM_ALUNOS_DUVIDA; i++) {
        pthread_create(&(alunos_duvida[i]), NULL, (void *)alunosDuvidasThread, (void *)(intptr_t)(i));
    }

    // // Espera as threads alunos_so acabarem
    // for (int i=1; i <= NUM_ALUNOS_SO; i++) {
    //     pthread_join(alunos_so[i],NULL);
    // }

    // // espera as threads aluno_duvida acabarem
    // for (int i=1; i <= NUM_ALUNOS_DUVIDA; i++) {
    //     pthread_join(alunos_duvida[i],NULL);
    // }

    // espera o professor acabar
    pthread_join(professor, NULL);

    // Destroi o monitor
    destroyMonitor();

    printf("\n");
    return 0;
}
