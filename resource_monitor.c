#include "resource_monitor.h"

void initMonitor()
{
    pthread_mutex_init(&mutex, NULL); // Inicializa o mutex e variáveis de condições
    pthread_cond_init(&professor, NULL); // Inicializa variáveis de condições do professor
    pthread_cond_init(&alunosSO, NULL); // Inicializa variáveis de condições dos alunos de SO
    pthread_cond_init(&alunosDuvida, NULL); // Inicializa variáveis de condições dos alunos com duvidas
    pthread_cond_init(&prDarAula, NULL); // Inicializa variáveis de condições do professor dar aula

    alunosSOCount=FALSE;
    alunosDuvidaCount=FALSE;
}

void destroyMonitor()
{
    pthread_mutex_destroy(&mutex);      /* libera o mutex */
    pthread_cond_destroy(&professor);      /* libera as variáveis de condições do professor */
    pthread_cond_destroy(&alunosSO);      /* libera as variáveis de condições dos alunos de SO */
    pthread_cond_destroy(&alunosDuvida);      /* libera as variáveis de condições dos alunos com duvidas */
    pthread_cond_destroy(&prDarAula);      /* libera as variáveis de condições do professor dar aula*/
}