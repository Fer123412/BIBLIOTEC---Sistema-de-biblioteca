#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

typedef struct no{
	int codigo;
	char titulo[100];
	float valor;
	struct no *prox;
}n1;

typedef struct{
	int codigo;
	char titulo[100];
	float valor;
} Livro;

typedef enum{
	CADASTRO,
	ATUALIZACAO,
	EXCLUIR
}tipoacao;

typedef struct acao{
	tipoacao tipo;
	
	Livro antes;
	Livro depois;
	
	int posicao;
	
	struct acao *prox;
} Acao;

void cadastrarlivros(n1 **l1, int qtd, Acao **pilha){
	for(int i = 0; i < qtd; i++){
		n1 *lista = (n1 *) malloc(sizeof(n1));
		
		if(lista == NULL){
			printf("ERRO: alocacao incompleta!");
			return;
		}
		
		printf("Codigo: ");
		fflush(stdin); scanf("%d", &lista->codigo);
		printf("Titulo: ");
		fflush(stdin); scanf("%s", &lista->titulo);
		printf("Valor: ");
		fflush(stdin); scanf("%f", &lista->valor);
		printf("\n-----------------------------");
		
		
		lista->prox = *l1;
		*l1 = lista;
		
		//PARTE DO HISTORICO
		Livro dados;
		
		dados.codigo = lista->codigo;
		strcpy(dados.titulo, lista->titulo);
		dados.valor = lista->valor;
		
		PUSH(pilha, CADASTRO, dados, dados, 0);
	}
}

void cadastrarlivromeio(n1 **lista, int qtd, int ant, Acao **pilha){
	for(int i=0; i<qtd; i++){
		n1 *aux = *lista;
		n1 *novo;
		int posicao = 0;
		while(aux != NULL && aux->codigo != ant){
			aux = aux->prox;
			posicao++;
		}
		
		if(aux == NULL){
			printf("Codigo nao encontrado!");
			return;
		}
		
		novo = (n1 *) malloc(sizeof(n1));
		
		if(novo != NULL){
			
			printf("Codigo: ");
			fflush(stdin); scanf("%d", &novo->codigo);
			printf("Titulo: ");
			fflush(stdin); scanf("%s", &novo->titulo);
			printf("Valor: ");
			fflush(stdin); scanf("%f", &novo->valor);
			printf("\n-----------------------------");
			
			novo->prox = aux->prox;
			aux->prox = novo;
		}else{
			printf("Erro de alocacao na memoria!");
		}
		
		//PARTE DO HISTORICO
		Livro dados;
		
		dados.codigo = novo->codigo;
		strcpy(dados.titulo, novo->titulo);
		dados.valor = novo->valor;
		
		PUSH(pilha, CADASTRO, dados, dados, posicao);
	}
}

void cadastrarlivrofim(n1 **lista, int qtd, Acao **pilha){
	for(int i = 0; i < qtd; i++){//valor auxiliar
		n1 *aux;
		n1 *novolista = (n1 *) malloc(sizeof(n1));
		int posicao = 0;
		
		if(novolista != NULL){
		
			printf("\nCodigo: ");
			fflush(stdin); scanf("%d", &novolista->codigo);
			
			printf("\nTitulo: ");
			fflush(stdin); scanf(" %99[^\n]", novolista->titulo);
			
			printf("\nValor: ");
			fflush(stdin); scanf("%f", &novolista->valor);
			printf("\n-------------------------\n");
		
			novolista->prox = NULL;
			
			if(*lista == NULL){
				*lista = novolista;
			}else{
				aux = *lista;
				
				while(aux->prox != NULL){
					aux = aux->prox;
					posicao++;
				}
				
				aux->prox = novolista;
			}
		}else{
			printf("ERRO a alocar memoria ");
		}
		
		//PARTE DO HISTORICO
		Livro dados;
		
		dados.codigo = novolista->codigo;
		strcpy(dados.titulo, novolista->titulo);
		dados.valor = novolista->valor;
		
		PUSH(pilha, CADASTRO, dados, dados, posicao);
	}
	
}

void listarlivros(n1 *lista){
	if(lista == NULL){
		printf("\nLista vazia!");
		return;
	}
	
	n1 *l1 = lista;
	
	while(l1 != NULL){
		printf("(%d, %s, %.2f) -> ", l1->codigo, l1->titulo, l1->valor);
		l1 = l1->prox;
	}
	

	printf("NULL");
}

void Atualizarlivros(n1 *lista, Acao **pilha){
	n1 *novalista = lista;
	int cod;
	
	if(lista == NULL){
		printf("Lista vazia!\n");
		return;
	}
	
	
	printf("Digite o codigo do livro: ");
	fflush(stdin); scanf("%d", &cod);
	
	while(novalista != NULL && novalista->codigo != cod){
		novalista = novalista->prox;
	}
	
	if(novalista == NULL){
		printf("Livro nao encontrado!");
		return;
	}
	
	//HISTORICO DE ATUALIZACAO ANTES
	Livro antes;
	antes.codigo = novalista->codigo;
	strcpy(antes.titulo, lista->titulo);
	antes.valor = novalista->valor;
	
	printf("\nCodigo: %d", novalista->codigo);
    printf("\nTitulo: %s", novalista->titulo);
    printf("\nValor: %.2f\n", novalista->valor);
    
	printf("\nDigite o novo titulo: ");
	fflush(stdin); scanf("%s", &novalista->titulo);
	
	printf("\nDigite o novo valor: ");
	fflush(stdin); scanf("%f", &novalista->valor);
	
	printf("Livro atualizado!");
	
	//HISTORICO DE ATUALIZACAO DEPOIS
	Livro depois;
	
	depois.codigo = novalista->codigo;
	strcpy(depois.titulo, novalista->titulo);
	depois.valor = novalista->valor;
	
	PUSH(pilha, ATUALIZACAO, antes, depois, 0);
}

void excluirlivros(n1 **lista, Acao **pilha){
	if(*lista == NULL){
		printf("Lista vazia!");
		return;
	}
	
	int codigo_livro;
	char resp;
	
	printf("\nDigite o codigo que quer excluir: ");
	fflush(stdin); scanf("%i", &codigo_livro);
	
	n1 *novalista = *lista;
	n1 *anterior = NULL; //para saber a lista antiga
	int posicao = 0;
	
	while(novalista != NULL && novalista->codigo != codigo_livro){
		anterior = novalista;
		novalista = novalista->prox;
		posicao++;
	}
	
	if(novalista == NULL){
		printf("Livro nao encontrado");
		return;
	}
	
	printf("\nCodigo: %d", novalista->codigo);
	printf("\nTitulo: %s", novalista->titulo);
	printf("\nValor: %.2f", novalista->valor);
	
	printf("\nExcluir livro?[s/n] ");
	fflush(stdin); scanf("%s", &resp);
	
	if(resp != 's' && resp != 'S'){
		printf("\nExclusao cancelada!");
		return;
	}
	
	if(anterior == NULL){
		*lista = novalista->prox; //era o primeiro
	} else{
		anterior->prox = novalista->prox;
	}
	
	//HISTORICO DE EXCLUSAO
	Livro antes;
	
	antes.codigo = novalista->codigo;
	strcpy(antes.titulo, novalista->titulo);
	antes.valor = novalista->valor;
	
	PUSH(pilha, EXCLUIR, antes, antes, posicao);
	
	free(novalista); //libera a memoria no sistema
	printf("\nLivro excluido!");
}

void salvarlista(n1 *lista){
	FILE *ficha = fopen("Ficha.dat", "wb");
	if(ficha == NULL){
		printf("Erro ao abrir o arquivo\n");
		return;
	}
	
	n1 *aux = lista;
    Livro temp;

    while(aux != NULL){

        temp.codigo = aux->codigo;
        strcpy(temp.titulo, aux->titulo);
        temp.valor = aux->valor;

        fwrite(&temp, sizeof(Livro), 1, ficha);

        aux = aux->prox;
    }

    fclose(ficha);
}

void carregarlista(n1 **lista){

    FILE *ficha = fopen("Ficha.dat", "rb");

    if(ficha == NULL){
        return;
    }

    Livro temp;
    n1 *ultimo = NULL;

    while(fread(&temp, sizeof(Livro), 1, ficha) == 1){

        n1 *novo = (n1 *) malloc(sizeof(n1));

        if(novo == NULL){
            printf("Erro de alocacao!");
            break;
        }

        novo->codigo = temp.codigo;
        strcpy(novo->titulo, temp.titulo);
        novo->valor = temp.valor;

        novo->prox = NULL;

        if(ultimo == NULL){
            *lista = novo;
        }else{
            ultimo->prox = novo;
        }

        ultimo = novo;
    }

    fclose(ficha);
}


// FUNÇÕES PILHAS
void PUSH(Acao **pilha, tipoacao tipo, Livro antes, Livro depois, int posicao){
	Acao *novo = malloc(sizeof(Acao));
	
	if(novo == NULL){
		printf("Erro de alocacao!");
		return;
	}
	
	novo->tipo = tipo;
	novo->antes = antes;
	novo->depois = depois;
	novo->posicao = posicao;
	
	novo->prox = *pilha;
	*pilha = novo;
	
	printf("\nAcao registrada no historico!");
}

Acao* POP(Acao **pilha){
	
	if(*pilha == NULL){
		printf("Nenhuma acao para desfazer!");
		return NULL;
	}
	
	Acao *removido = *pilha;
	
	*pilha = removido->prox;
	
	return removido;
}

void removerCodigo(n1 **lista, int codigo){
	
	n1 *atual = *lista;
	n1 *anterior = NULL;
	
	while(atual != NULL && atual->codigo != codigo){
		anterior = atual;
		atual = atual->prox;
	}
	
	if(atual == NULL){
		return;
	}
	
	if(anterior == NULL){
		*lista = atual->prox;
	}else{
		anterior->prox = atual->prox;
	}
	
	free(atual);
}

void restaurarLivro(n1 *lista, Livro dados){
	
	while(lista != NULL){
		if(lista->codigo == dados.codigo){
			
			strcpy(lista->titulo, dados.titulo);
			lista->valor = dados.valor;
			
			return;
		}
		
		lista = lista->prox;
	}
}


void inserirPosicao(n1 **lista, Livro dados, int posicao){
	
	n1 *novo = malloc(sizeof(n1));
	
	if(novo == NULL){
		return;
	}
	
	novo->codigo = dados.codigo;
	strcpy(novo->titulo, dados.titulo);
	novo->valor = dados.valor;
	
	if(posicao <= 0 || *lista == NULL){
		novo->prox = *lista;
		*lista = novo;
		return;
	}
	
	n1 *aux = *lista;
	
	for(int i=0; i<posicao - 1 && aux->prox != NULL; i++){
		aux = aux->prox;
	}
	
	novo->prox = aux->prox;
	aux->prox = novo;
}


void desfazer(Acao **pilha, n1 **lista){
	Acao *acao = POP(pilha);
	
	if(acao == NULL){
		return;
	}
	
	switch(acao->tipo){
		case CADASTRO:
			removerCodigo(lista, acao->depois.codigo);
			printf("\nCadastro desfeito!");
			break;
		case ATUALIZACAO:
			restaurarLivro(*lista, acao->antes);
			printf("\nAtualizacao desfeita!");
			break;
		case EXCLUIR:
			inserirPosicao(lista, acao->antes, acao->posicao);
			printf("\nExclusao desfeita!");
			break;
	}
	
	free(acao);
}

void mostrarHistorico(Acao *pilha){
	
	if(pilha == NULL){
		printf("\nNenhuma acao registrada!");
		return;
	}
	printf("\n----------------------------");
	printf("\n         HISTORICO          ");
	printf("\n----------------------------");
	while(pilha != NULL){
		
		switch(pilha->tipo){
			
			case CADASTRO:
				printf("\n[CADASTRO] Codigo: %d", pilha->depois.codigo);
				break;
			
			case ATUALIZACAO:
				printf("\n[ATUALIZACAO] Codigo: %d", pilha->antes.codigo);
				break;
			
			case EXCLUIR:
				printf("\n[EXCLUIR] Codigo: %d", pilha->antes.codigo);
				break;
		}
		
		pilha = pilha->prox;
	}
}

void gerarRelatorio(){
	
	FILE *ficha = fopen("Ficha.dat", "rb");
	
	if(ficha == NULL){
		printf("\nErro ao abrir o arquivo Ficha.dat!");
		return;
	}
	
	FILE *relatorio = fopen("relatorio_livros.txt", "w");
	
	if(relatorio == NULL){
		printf("\nErro ao criar o arquivo de relatorio!");
		fclose(ficha);
		return;
	}
	
	Livro livro;
	int quantidade = 0;
	
	fprintf(relatorio, "================================\n");
	fprintf(relatorio, "       RELATORIO DE LIVROS      \n");
	fprintf(relatorio, "================================\n\n");
	
	while(fread(&livro, sizeof(Livro), 1, ficha) == 1){
		
		fprintf(relatorio, "Codigo: %d\n", livro.codigo);
		fprintf(relatorio, "Titulo: %s\n", livro.titulo);
		fprintf(relatorio, "Valor: %.2f\n", livro.valor);
		
		fprintf(relatorio, "----------------------------\n");
		
		quantidade++;
	}
	
	fprintf(relatorio, "\nTotal de livros: %d\n", quantidade);
	
	fclose(ficha);
	fclose(relatorio);
	
	printf("\nRelatorio gerado!");
	printf("\nArquivo: relatorio_livros.txt");
}
int main(){
	int op,qtd, cod_anterior;
	char pose;
	n1 *l1=NULL;
	carregarlista(&l1);
	Acao *pilha = NULL;
	
	do{
		printf("\n=========================");
		printf("\n=      BIBLIATEC        =");
		printf("\n=========================");
		printf("\n= [1]Cadastrar livros   =");
		printf("\n= [2]listar livros      =");
		printf("\n= [3]Atualizar livros   =");
		printf("\n= [4]Excluir livros     =");
		printf("\n= [5]Desfazer acao      =");
		printf("\n= [6]Historico          =");
		printf("\n= [7]Imprimir Relatorio =");
		printf("\n= [0]Sair               =");
		printf("\n=========================");
		printf("\n> ");
		scanf("%d", &op);
		
		switch(op){
			case 1:
				printf("Qual sera a posicao?(Inicio(i),Meio(m),Fim(f)) ");
				fflush(stdin); scanf("%c", &pose);
				
				if(pose == 'i'){
					printf("Quantos livros? ");
					fflush(stdin); scanf("%d", &qtd);
					cadastrarlivros(&l1, qtd, &pilha);
				}
				if(pose == 'm'){
					printf("Quantos livros? ");
					fflush(stdin); scanf("%d", &qtd);
					
					printf("Codigo anterior? ");
					fflush(stdin); scanf("%d", &cod_anterior);
					cadastrarlivromeio(&l1, qtd, cod_anterior, &pilha);
				}
				if(pose == 'f'){
					printf("Quantos livros? ");
					fflush(stdin); scanf("%d", &qtd);
					cadastrarlivrofim(&l1, qtd, &pilha);
				}
				break;
			
			case 2:
				listarlivros(l1);
				break;
			
			case 3:
				Atualizarlivros(l1, &pilha);
				break;
			
			case 4:
				excluirlivros(&l1, &pilha);
				break;
			
			case 5:
				desfazer(&pilha, &l1);
				break;
			
			case 6:
				mostrarHistorico(pilha);
				break;
			
			case 7:
				salvarlista(l1);
				gerarRelatorio();
				break;
				
			case 0:
				salvarlista(l1);
				printf("sistema encerrado..");
				break;
				
			default:
				printf("opcao invalida!");
				break;
		}
	}while(op!=0);
	
	return 0;
}