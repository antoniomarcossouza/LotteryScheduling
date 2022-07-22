/*
 *  lottery.c - Implementacao do algoritmo Lottery Scheduling e sua API
 *
 *  Autores: SUPER_PROGRAMADORES_C
 *  Projeto: Trabalho Pratico I - Sistemas Operacionais
 *  Organizacao: Universidade Federal de Juiz de Fora
 *  Departamento: Dep. Ciencia da Computacao
 *
 */

#include "lottery.h"

#include <stdio.h>
#include <string.h>

// Nome unico do algoritmo. Deve ter 4 caracteres.
const char lottName[] = "LOTT";

int slot;  // slot de Lottery

//=====Funcoes Auxiliares=====

//=====Funcoes da API=====

// Funcao chamada pela inicializacao do S.O. para a incializacao do escalonador
// conforme o algoritmo Lottery Scheduling
// Deve envolver a inicializacao de possiveis parametros gerais
// Deve envolver o registro do algoritmo junto ao escalonador
void lottInitSchedInfo() {
    SchedInfo *sched_info = malloc(sizeof(SchedInfo)); /* Alocando o espaço necessário
                                                       para registrar o algoritmo
                                                       de escalonamento */

    strcpy(sched_info->name, lottName); /* Armazenando o nome do algoritmo
                                         de loteria na struct de registro
                                         de algoritmos de escalonamento */

    sched_info->initParamsFn = lottInitSchedParams; /* Armazenando a funcao para inicializar
                                                    os parametros de escalonamento de um
                                                    processo na struct de registro
                                                    de algoritmos de escalonamento */

    sched_info->notifyProcStatusChangeFn = lottNotifyProcStatusChange; /* Armazenando a funcao que notifica
                                                                       que um processo mudou de estado na
                                                                       struct de registro de algoritmos
                                                                       de escalonamento */

    sched_info->scheduleFn = lottSchedule; /* Armazenando a funcao para decidir qual o
                                           proximo processo a obter a CPU na struct
                                           de registro de algoritmos de escalonamento */

    sched_info->releaseParamsFn = lottReleaseParams; /* Armazenando a funcao para liberar
                                                     os parametros de escalonemnto de um processo
                                                     na struct de registro de algoritmos de
                                                     escalonamento */

    slot = schedRegisterScheduler(sched_info); /* Registra o algoritmo de Loteria */
}

// Inicializa os parametros de escalonamento de um processo p, chamada
// normalmente quando o processo e' associado ao slot de Lottery
void lottInitSchedParams(Process *p, void *params) {
    //...
}

// Recebe a notificação de que um processo sob gerência de Lottery mudou de estado
// Deve realizar qualquer atualização de dados da Loteria necessária quando um processo muda de estado
void lottNotifyProcStatusChange(Process *p) {
    //...
}

// Retorna o proximo processo a obter a CPU, conforme o algortimo Lottery
Process *lottSchedule(Process *plist) {
    int total_tickets = 0;

    for (Process *p = plist; p != NULL; p = processGetNext(p)) { /* For na lista de processos para
                                                                 contar o número total de tickets */

        LotterySchedParams *sched_params = processGetSchedParams(p); /* Recebe os parâmetros do
                                                                     algoritmo de loteria */

        if (processGetStatus(p) != PROC_WAITING) {
            total_tickets += sched_params->num_tickets; /* Se o processo não estiver esperando, os
                                                        tickets são adicionados ao total de tickets */
        }
    }

    int chosen_ticket = rand() % total_tickets; /* Gerando um número aleatório
                                                entre zero e o total de ticket */

    int growing_process_list = 0; 

    for (Process *p = plist; p != NULL; p = processGetNext(p)) { /* For na lista de processos para
                                                                 encontrar o processo cujo ticket foi 
                                                                 sorteado */

        LotterySchedParams *sched_params = processGetSchedParams(p); /* Recebe os parâmetros do
                                                                     algoritmo de loteria */

        if (processGetStatus(p) != PROC_WAITING) {
            growing_process_list += sched_params->num_tickets;
            if (chosen_ticket <= growing_process_list) { /* Conforme a lista análoga a
                                                         'total_tickets' cresce o programa
                                                         checa se o ticket escolhido está na lista */

                return p; /* Retorna o próximo processo a receber a CPU */
            }
        }
    }

    return NULL;
}

// Libera os parametros de escalonamento de um processo p, chamada
// normalmente quando o processo e' desassociado do slot de Lottery
// Retorna o numero do slot ao qual o processo estava associado
int lottReleaseParams(Process *p) {
    //...
    return 0;
}

// Transfere certo numero de tickets do processo src para o processo dst.
// Retorna o numero de tickets efetivamente transfeirdos (pode ser menos)
int lottTransferTickets(Process *src, Process *dst, int tickets) {
    //...
    return 0;
}
