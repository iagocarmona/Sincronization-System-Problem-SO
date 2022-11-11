#include "resource_monitor.h"

void initMonitor()
{
    pthread_mutex_init(&monitor.mutex, NULL); // Inicializa o mutex e variáveis de condições
    pthread_cond_init(&monitor.professor, NULL); // Inicializa variáveis de condições do professor
    pthread_cond_init(&monitor.alunos_so, NULL); // Inicializa variáveis de condições dos alunos de SO
    pthread_cond_init(&monitor.alunos_duvidas, NULL); // Inicializa variáveis de condições dos alunos com duvidas

    pthread_cond_init(&monitor.aluno_fila_duvida, NULL); 
    pthread_cond_init(&monitor.aluno_fila_so, NULL); 
    pthread_cond_init(&monitor.professor_acabou_a_aula, NULL); 
    pthread_cond_init(&monitor.alunos_sairam_da_sala, NULL); 
    pthread_cond_init(&monitor.professor_dar_aula, NULL); 
    pthread_cond_init(&monitor.professor_atender, NULL); 
    pthread_cond_init(&monitor.professor_acabou_o_atendimento, NULL); 
    pthread_cond_init(&monitor.alunos_duvida_sairam, NULL); 

    monitor.qtd_alunos_duvida_esperando=0;
    monitor.qtd_alunos_tirando_duvidas=0;
    monitor.qtd_alunos_so_na_sala=0;
    monitor.max_alunos_so=NUM_ALUNOS_SO;
    monitor.max_alunos_duvidas=NUM_ALUNOS_DUVIDA;
    monitor.max_atendimento_professor=NUM_GRUPO_ATENDE_ALUNOS;
    monitor.professor_atendendo=FALSE;
    monitor.professor_dando_aula=FALSE;
    monitor.aula_finalizada=FALSE;
    monitor.qtd_alunos_duvida_atendendo=NUM_GRUPO_ATENDE_ALUNOS;
}

void destroyMonitor()
{
    pthread_mutex_destroy(&monitor.mutex);      /* libera o mutex */
    pthread_cond_destroy(&monitor.professor);      /* libera as variáveis de condições do professor */
    pthread_cond_destroy(&monitor.alunos_so);      /* libera as variáveis de condições dos alunos de SO */
    pthread_cond_destroy(&monitor.alunos_duvidas);      /* libera as variáveis de condições dos alunos com duvidas */

    pthread_cond_destroy(&monitor.aluno_fila_duvida);
    pthread_cond_destroy(&monitor.aluno_fila_so);
    pthread_cond_destroy(&monitor.professor_acabou_a_aula);
    pthread_cond_destroy(&monitor.alunos_sairam_da_sala);
    pthread_cond_destroy(&monitor.professor_dar_aula);
    pthread_cond_destroy(&monitor.professor_atender);
    pthread_cond_destroy(&monitor.professor_acabou_o_atendimento);
    pthread_cond_destroy(&monitor.alunos_duvida_sairam);
}