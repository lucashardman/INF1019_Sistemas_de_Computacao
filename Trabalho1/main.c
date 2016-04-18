#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "escalonadores.h"

struct programaPrioridade{
	char execStr[5];
	char nome[15];
	int prioridade;
};

struct programaRoundRobin{
	char execStr[5];
	char nome[15];
};

struct programaLoteria{
	char execStr[5];
	char nome[15];
	int numeroTickets;
};

int main (void){

	FILE *exec;

	int metodoEscalonamento = 0; //1 - Prioridade - 2 - Round-robin - 3 - Lottery
	int loop = 0; //Variaveis auxiliares
	int contadorProgramas = 0; //Guarda o numero de programas em execucao

	struct programaPrioridade *lstProgramasPrioridade[maximo_programas]; //Lista de programas em execucao
	struct programaRoundRobin *lstProgramasRoundRobin[maximo_programas]; //Lista de programas em execucao
	struct programaLoteria *lstProgramasLoteria[maximo_programas]; //Lista de programas em execucao
	
	/* Escolha da politica de escalonamento */
	while(loop == 0){
		printf("Escolha a politica de escalonamento:\n1 - Por prioridade\n2 - Round-robin\n3 - Loteria\n");

		scanf("%d", &metodoEscalonamento);
		
		loop = 1;

		if(metodoEscalonamento != 1 && metodoEscalonamento != 2 && metodoEscalonamento != 3){
			printf("Politica de escalonamento invalida. Por favor, digite 1, 2 ou 3.\n");
			loop = 0;
		}
	}
	/* Fim: Escolha da politica de escalonamento */

	/****************************************************************************
	 * Preparacao dos programas a serem executados 								*
	 * 1 - Leitura do arquivo com a ordem de execucao dos programas				*
	 * 2 - Tratamento de erro para leitura do arquivo							*
	 * 3 - Alocacao de memoria para a estrutura que ira guardar os dados lidos	*
	 * 4 - Estrutura recebe os dados											*
	 ****************************************************************************/

	exec = fopen("exec.txt", "r");

	if (exec == NULL){
		printf("Erro na abertura do arquivo exec.exe");
		system("pause");
		exit(0);
	}

	/* Alocacao de memoria */
	for (loop=0; loop<maximo_programas; loop++){
		if(metodoEscalonamento == 1)
			lstProgramasPrioridade[loop] = (struct programaPrioridade*) malloc (sizeof(struct programaPrioridade) * 25);
		if(metodoEscalonamento == 2)
			lstProgramasRoundRobin[loop] = (struct programaRoundRobin*) malloc (sizeof(struct programaRoundRobin) * 25);
		if(metodoEscalonamento == 3)
			lstProgramasLoteria[loop] = (struct programaLoteria*) malloc (sizeof(struct programaLoteria) * 25);
	}
	/* Fim da alocacao de memoria */

	/* Estruturas recebem os dados do arquivo */
	if(metodoEscalonamento == 1){ //Para a politica de escalonamento POR PRIORIDADE
		while(fscanf(exec, "%s %s %d", (lstProgramasPrioridade[contadorProgramas])->execStr, (lstProgramasPrioridade[contadorProgramas])->nome, &(lstProgramasPrioridade[contadorProgramas])->prioridade) == 3){ 
			contadorProgramas++;
		}
	}
	else if(metodoEscalonamento == 2){ //Para a politica de escalonamento ROUND-ROBIN
		while(fscanf(exec, "%s %s", (lstProgramasRoundRobin[contadorProgramas])->execStr, (lstProgramasRoundRobin[contadorProgramas])->nome) == 2){ 
			contadorProgramas++;
		}
	}
	else if(metodoEscalonamento == 3){ //Para a politica de escalonamento LOTTERY
		while(fscanf(exec, "%s %s %d", (lstProgramasLoteria[contadorProgramas])->execStr, (lstProgramasLoteria[contadorProgramas])->nome, &(lstProgramasLoteria[contadorProgramas])->numeroTickets) == 3){ 
			contadorProgramas++;
		}
	}
	/* Fim: estruturas recebem os dados do arquivo */

	/****************************************************************************/
	// BLOCO DE TESTE:      
	//                                                    
	//printf("Marcador 1\n");
	//printf("%d\n",contadorProgramas);
	//
	// Teste politica 1:														
	//for(loop=0;loop<contadorProgramas;loop++)
	//	printf("1: %s - prioridade: %d\n",lstProgramasPrioridade[loop]->nome, lstProgramasPrioridade[loop]->prioridade);
	//
	// Teste politica 2:														
	//for(loop=0;loop<contadorProgramas;loop++)
	//	printf("1: %s\n",lstProgramasRoundRobin[loop]->nome);
	//
	// Teste politica 3:														
	//for(loop=0;loop<contadorProgramas;loop++)
	//	printf("3: %s - numero de tickets: %d\n",lstProgramasLoteria[loop]->nome, lstProgramasLoteria[loop]->numeroTickets);
	/****************************************************************************/


	/* Chamada das funcoes de escalonamento */
	if(metodoEscalonamento == 1){
	}
	else if(metodoEscalonamento == 2){
	}
	else if(metodoEscalonamento == 3){
	}
	else{
		printf("Erro na chamada das funcoes de escalonamento: metodo invalido\n");
	}
	/* Fim: chamada das funcoes de escalonamento */

	/* Limpeza de memora e encerramento de arquivos */
	for(loop=0;loop<maximo_programas;loop++){

		if(metodoEscalonamento == 1)
			free(lstProgramasPrioridade[loop]);
		if(metodoEscalonamento == 2)
			free(lstProgramasRoundRobin[loop]);
		if(metodoEscalonamento == 3)
			free(lstProgramasLoteria[loop]);
	}
	fclose(exec); //Fecha o arquivo exec.exe
	/* Fim: Limpeza de memora e encerramento de arquivos */

	return 0;
}
