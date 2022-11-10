#include "resource_semaforo.h"

void initSemaforo()
{
    sem_init(&semaforo.alunosDuvida, 0, NUM_GRUPO_ATENDE_ALUNOS); // inicializa variáveis de condições dos alunos com duvidas
    sem_init(&semaforo.profDarAula, 0, 0); // inicializa semáforo de sinalização do começo da aula
    sem_init(&semaforo.profAtenderAlunos, 0, 0); //inicializa semáforo de sinalização do começo de atendimento dos alunos com dúvida
    sem_init(&semaforo.fimAula, 0, 0); //inicializa semáforo de sinalização de fim da aula de SO
    sem_init(&semaforo.alunosPresentes, 0, 0);  //inicializa semáforo de sinalização que todos osmalunos de SO chegaram

    semaforo.alunosSOCount = 0; //variável de contagem dos alunos de SO na sal
    semaforo.alunosDuvidaCount =0; //variável de contagem dos alunos com dúvida
    semaforo.professorEstaDandoAula = FALSE; //variável de verificação se o professor está dando aula ou não
    semaforo.salaAtend = FALSE;
    semaforo.alunosDuvidaRestante = NUM_ALUNOS_DUVIDA;
}
