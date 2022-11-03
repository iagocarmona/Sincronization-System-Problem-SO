#pragma once
#include "professor.h"
#include "../resource_monitor.h"

void *professorThread(void *ptr){
    darAula();
}
void prepararAula(){}

void darAula(){
    professorDarAula=TRUE;
}

void dispensarAlunos(){}

void irEmboraCasa(){}
