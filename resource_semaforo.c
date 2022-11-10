#include "resource_semaforo.h"

void initSemaforo()
{
    sem_init(&semaforo.alunosDuvida, NUM_GRUPO_ATENDE_ALUNOS); // Inicializa variáveis de condições dos alunos com duvidas
    sem_init(&semaforo.profDarAula, 0); // Inicializa semáforo de sinalização do começo da aula
    sem_init(&semaforo.profAtenderAlunos, 0);
    sem_init(&semaforo.fimAula, 0);
    sem_init(&semaforo.alunosPresentes, 0);

    semaforo.alunosSOCount=0;
    semaforo.alunosDuvidaCount=0;
    semaforo.professorEstaDandoAula=FALSE;
}
