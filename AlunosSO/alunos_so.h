#pragma once
#define NUM_ALUNOS_SO 15

void *alunosSOThread(void *ptr);
void entrarSalaAula();
void sairSalaAula();
void aguardarAula();
void obaAulaSO();
void chamarProfessor(int n);