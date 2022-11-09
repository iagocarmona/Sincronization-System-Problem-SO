#include "resource_monitor.h"

void initMonitor()
{
    pthread_mutex_init(&monitor.mutex, NULL); // Inicializa o mutex e variáveis de condições
    pthread_cond_init(&monitor.professor, NULL); // Inicializa variáveis de condições do professor
    pthread_cond_init(&monitor.alunosSO, NULL); // Inicializa variáveis de condições dos alunos de SO
    pthread_cond_init(&monitor.alunosDuvida, NULL); // Inicializa variáveis de condições dos alunos com duvidas
    pthread_cond_init(&monitor.prDarAula, NULL); // Inicializa variáveis de condições do professor dar aula

    monitor.alunosSOCount=0;
    monitor.alunosDuvidaCount=0;
    monitor.professorEstaDandoAula=FALSE;
}

void destroyMonitor()
{
    pthread_mutex_destroy(&monitor.mutex);      /* libera o mutex */
    pthread_cond_destroy(&monitor.professor);      /* libera as variáveis de condições do professor */
    pthread_cond_destroy(&monitor.alunosSO);      /* libera as variáveis de condições dos alunos de SO */
    pthread_cond_destroy(&monitor.alunosDuvida);      /* libera as variáveis de condições dos alunos com duvidas */
    pthread_cond_destroy(&monitor.prDarAula);      /* libera as variáveis de condições do professor dar aula*/
}