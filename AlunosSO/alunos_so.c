#pragma once
#include <stdio.h>

#include "alunos_so.h"
#include "../resource_monitor.h"

void *alunosSOThread(void *ptr){
    if(professorDarAula){
        obaAulaSO();
    }
}

void entrarSalaAula(){}

void sairSalaAula(){}

void aguardarAula(){}

void obaAulaSO(){
    printf("OBA VAMOS TER AULA");
}

void chamarProfessor(int n){}