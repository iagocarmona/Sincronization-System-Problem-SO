#pragma once

/**
 * @brief realiza ass chamadas das funçẽos executadas pelo professor
 * 
 * @return void* 
 */
void *professorThread();



/**
 * @brief realiza a saída que demonstra que o professor está preparando sua aula
 * 
 */
void prepararAula();



/**
 * @brief tem como saída uma mensagem que iniciará o atendimento dos alunos com dúvida,
 * por meio da variável de condição "prAtenderAlunos" sinaliza para os alunos com dúvida 
 * que iniciará o atendimento
 * 
 */
void atenderAlunos();


/**
 * @brief espera pela sinalização de que todos os alunos daa turma de SO estão presentes, 
 * se receber tal sinalização, seta a variável que diz se está dando aula pu não. Após isso,
 * sinaliza para todos os alunos que a aula irá começar.
 * 
 */
void darAula();


/**
 * @brief Após o fim da aula, o professor sinaliza para os alunos o fim da aula, e apresenta
 * na tela a mensagem que diz que a aula cabou.
 * 
 */
void dispensarAlunos();


/**
 * @brief 
 * 
 */
void irEmboraCasa();
