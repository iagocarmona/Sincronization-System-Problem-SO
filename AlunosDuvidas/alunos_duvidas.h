#pragma once

/**
 * @brief função que realiza as chamadas das funções que serão executadas pelos alunosDuvidas
 * 
 * @param ptr identificador do alunosDuvidas
 * @return void* 
 */
void *alunosDuvidasThread(void *ptr);


/**
 * @brief A chegar na sala so professor para tirar dúvidas, uma mnsagem sai na tela
 * informando o ato, caso o professor esteja disponível, a variável de quentidade de
 * alunos com dúvida é incrementada, se o professor não estar disponível, o aluno com
 *  dúvida vai embora
 * 
 * @param num identificador do alunoDuvida
 */
void chegarSalaProfessor(int num);
void aguardarProfessor(int num);
void tirarDuvidas(int num);
void sairSalaProfessor(int num);
void professorEstaDandoAula(int num);