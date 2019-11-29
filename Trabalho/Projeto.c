#define _GNU_SOURCE
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
#include <unistd.h>               // chamar a funcao sleep
#include <stdbool.h>              // define a constante inteira ou booleana
#include <pthread.h>              // inclui as funcoes para as threads
#include <semaphore.h>            // inclui as funcoes para implementar o semaforo


struct c {
	int saldo;
};

                                  // declarando as variaveis

sem_t transacoes_semaforo;     // define o semaforo


bool transacoes;

typedef struct c conta;

conta from, to;

int valor;

int qtd_transferencias = 0;

int transferenciasFinalizadas = 0;

void* transferencia(void *arg){                    


	sem_wait(&transacoes_semaforo);     // trava o semaforo

	qtd_transferencias++;               // variael para contar o numero de transferencias

	printf("Iniciando transferencia: %d ...\n" , qtd_transferencias);


	transacoes = rand() & 1;       // funcao que faz as transferencias de forma aleatoria
	if(transacoes == true){
		if (from.saldo >= valor){
			from.saldo -= valor;
			to.saldo += valor;
			if (from.saldo && to.saldo == 0){
				printf("Saldo insuficiente");
			}
		}
	}else{
		if (to.saldo >= valor){
			to.saldo -= valor;
			from.saldo += valor;
			if (from.saldo && to.saldo == 0){
				printf("Saldo insuficiente");
		}
		}	
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Transferência realizada\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\n Saldo da conta1: R$ %d\n", from.saldo);
	printf("\n Saldo da conta2: R$ %d\n\n", to.saldo);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	sem_post(&transacoes_semaforo);          // operacao que libera o semaforo
}	

int main(){
	void* stack; 
	int i;

    pthread_t Threads[100];
	sem_init(&transacoes_semaforo, 0 , 1);

	from.saldo = 500;            // saldo da conta 1
	to.saldo = 500;              // saldo da conta 2
	valor = 10;                  // valor de cada transacao




        // cria as 100 threads
	for(i = 0; i < 100; i++){
		pthread_create(&Threads[i], NULL, transferencia, NULL);
	}

	printf("Todas as threads foram criadas\n\n\n\n");

	
	// manipula as threads
	for(i = 0; i < 100; i++){
		pthread_join(Threads[i], NULL);
		sleep(1);                                          // para fins esteticos
		printf("Thread %ld terminada!\n", Threads[i]);
	}

	// aviso final contendo a qtd final de threads concluidas
	printf("Transferencias realizadas: %d\n", qtd_transferencias);

	return 0;
}

