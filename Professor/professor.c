#include "professor.h"
#include "../resource_monitor.h"

void *professorThread(){
    pthread_mutex_lock(&monitor.mutex);

    while(monitor.professor_dando_aula == FALSE){
        if(monitor.qtd_alunos_so_na_sala < monitor.max_alunos_so){
            if(monitor.qtd_alunos_duvida_esperando < monitor.max_atendimento_professor){
                // enquanto não tem os N alunos de SO em sala de aula
                // e os X alunos com duvida esperando atendimento
                // professor fica preparando aula.
                prepararAula();
            }

            // chegaram todos os X alunos com duvida na porta do professor
            // então ele deve atende-los
            atenderAlunos();

            // time(&T);
            // t.tv_sec = T + 3;
            // t.tv_nsec = 0;

            // // aguarda 3 segundos para voltar e verificar se chegou todos os alunos de so
            // pthread_cond_timedwait(&monitor.professor, &monitor.mutex, &t);
        }
        // espera chegar todos os alunos de SO
        pthread_cond_wait(&monitor.aluno_fila_so, &monitor.mutex);
        // chegaram todos os N alunos de SO, agora o professor deve dar aula
        darAula();
        // tempo para o professar dar a aula
        sleep(6);
    }

    // sinaliza aos alunos de SO que acabou a aula
    dispensarAlunos();

    // espera todos os alunos sairem da sala de aula
    pthread_cond_wait(&monitor.alunos_sairam_da_sala, &monitor.mutex);

    // agora o professor pode ir embora 
    irEmboraCasa();

    pthread_mutex_unlock(&monitor.mutex);
}

void prepararAula(){
    printf("\n👨‍🏫 | Professor está preparando a aula!\n");
    sleep(1);
}

void atenderAlunos(){
    printf("\n👨‍🏫 | Vou atender os alunos...\n");
    pthread_cond_signal(&monitor.aluno_fila_duvida);
    monitor.professor_atendendo=TRUE;
    sleep(1);
}

void darAula(){
    pthread_cond_wait(&monitor.aluno_fila_so, &monitor.mutex);
    printf("👨‍🏫 | Vou dar aula!\n");
    monitor.professor_dando_aula=TRUE;
    pthread_cond_signal(&monitor.alunos_so);
    sleep(1);
}

void dispensarAlunos(){
    printf("👨‍🏫 | Aula acabou, dispensando alunos...\n");
    sleep(1);
    pthread_cond_signal(&monitor.professor_acabou_a_aula);
    monitor.aula_finalizada=TRUE;
}

void irEmboraCasa(){
    printf("👨‍🏫 | Professor indo embora pra casa...\n");
    sleep(1);
}
