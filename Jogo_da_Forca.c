#include <stdio.h>
#include <stdlib.h> //srand está nessa biblioteca
#include <locale.h>
#include <string.h>
#include <time.h> //time está nessa biblioteca
#include "Jogo_da_Forca_.h"

//variáveis globais
char palavra[TAM_PALAVRA]; // palavra é a palavra secreta
char letrasTotal[26];
int tentativas = 0;

void cabecalho()
{
    printf("\n******************************\n");
    printf("*Bem vindo ao Jogo de Forca *\n");
    printf("******************************\n\n");
}
//letras[] é um vetor que guarda o alfabeto
void captura_palpites() 
{
	char palpite;
	printf("Qual seu palpite, jogador? ");
	scanf(" %c", &palpite);
    printf("\n");
	
	if(letraExiste(palpite)){
		printf("Você  acertou: a palavra tem a letra %c\n\n", palpite);
	}else{
		printf("\nVocê errou: a palavra NÃO tem a letra %c\n\n", palpite);
	}

	letrasTotal[tentativas] = palpite; //palpite é chute de uma letra
	(tentativas)++; //Conta quantas vezes o jogador chutou até acertar a palavra secreta
}

int letraJaChutada(char letrachutada)
{// não vou passar o ponteiro da variável tentativas, pois não pretendo alterar o conteúdo dela.
	int achou = 0;

	for(int j = 0; j < tentativas; j++) {
		if(letrasTotal[j] == letrachutada) {
			achou = 1;
			break;
		}
	}
	return (achou);
}

void desenhaForca()
{  //printf("Já foi dados %d chutes.\n", tentativas);
	int erros = chutesErrados();
	
	//IF's ternários aqui:
		printf("  _______      \n");
		printf(" |/      |     \n");
		printf(" |      %c%c%c    \n", (erros >= 1 ? '(' : ' '), (erros >= 1 ? '_' : ' '), (erros >= 1 ? ')' : ' '));
		printf(" |      %c%c%c   \n", (erros >= 3 ? '\\' : ' '), (erros >= 2 ? '|' : ' '), (erros >= 3 ? '/' : ' '));
		printf(" |       %c     \n", (erros >= 2 ? '/' : ' '));
		printf(" |      %c%c   \n", (erros >= 4 ? '/' : ' '), (erros >= 4 ? '\\' : ' '));
		printf(" |             \n");
		printf("_|___          \n");
		printf("\n\n");

		for (int i = 0; i < strlen(palavra); i++)
		{

			int achou = letraJaChutada(palavra[i]);

			if (achou){
				printf("%c ", palavra[i]);
			}
			else{
				printf("_ ");
			}
		}
		printf("\n");
}

void adicionaPalavra()
{
	char quer;

	printf("Hey! Você deseja adicionar uma nova palavra no jogo? (S/N) ");
	scanf(" %c", &quer);

	if (quer == 'S'){
		char novaPalavra[TAM_PALAVRA];
		printf("\n\nQual a nova palavra?\n");
		scanf("%s", novaPalavra);

		FILE* f;
		f = fopen("Frutas.txt", "r+");
		if(f == 0){
			printf("Desculpe! Banco de dados indisponível.\n\n");
			exit(1);
		}

		int qtd;
		fscanf(f, "%d", &qtd);
		qtd++;

		fseek(f, 0, SEEK_SET);
		fprintf(f, "%d", qtd);

		fseek(f, 0, SEEK_END);
		fprintf(f, "\n%s", novaPalavra);

		fclose(f);
	}
}

void escolhePalavra()
{
	FILE* f;

	f = fopen("Frutas.txt", "r");
	if(f == 0){
		printf("Desculpe! Banco de dados indisponível.\n\n");
		exit(1);
	}

	int qtdPalavras;
	fscanf(f, "%d", &qtdPalavras);

	srand(time(0));
	int randomico = rand() % qtdPalavras;

	for(int i = 0; i <= randomico; i++){
		fscanf(f, "%s", palavra);
	}

	fclose(f);
}

int acertou()
{
	for(int i = 0; i <strlen(palavra); i++){
		if(!letraJaChutada(palavra[i])){
			return (0);
		}
	}
	return (1);
}
int letraExiste(char letrasTotal)
{
	for(int j = 0; j <strlen(palavra); j++){
		if (letrasTotal == palavra[j]){
			return 1;
		}
	}	
	return (0);	
}

int chutesErrados()
{
	int erros = 0;
	for(int i = 0;  i < tentativas; i++){
		if (!letraExiste(letrasTotal[i])){
			erros++;
		}
	}
	return (erros);
}

int morreu()
{
	return (chutesErrados()) >= 5;
}

int main() {

	escolhePalavra();
	cabecalho();

	do {
		desenhaForca();
		captura_palpites();
	
	} while (!acertou() && !morreu());
	
	if(acertou()){
		printf("Parabéns! Você acertou!!\n");

		printf("────────────────█████████─────────────── \n");
		printf("──────────────█████████████───────────── \n");
		printf("───────────███████████████████────────── \n");
		printf("──────────────────────────────────────── \n");
		printf("────────████████████████████████──────── \n");
		printf("────────████████████████████████──────── \n");
		printf("──────────────────────────────────────── \n");
		printf("█████████─████████████████████─█████████ \n");
		printf("█████████─████████████████████─█████████ \n");
		printf("███───────████████────████████───────███ \n");
		printf("███───────██████───██───██████───────███ \n");
		printf("─███──────█████──████────█████──────███─ \n");
		printf("──███─────████─────██─────████─────███── \n");
		printf("───███────████─────██─────████────███─── \n");
		printf("────███───█████────██────█████───███──── \n");
		printf("─────███──█████────██────█████──███───── \n");
		printf("──────███─███████──────███████─███────── \n");
		printf("───────██─████████████████████─██─────── \n");
		printf("────────█─████████████████████─█──────── \n");
		printf("──────────────────────────────────────── \n");
		printf("──────────████████████████████────────── \n");
		printf("───────────██████████████████─────────── \n");
		printf("─────────────██████████████───────────── \n");
		printf("───────────────███████████────────────── \n");
		printf("──────────────────────────────────────── \n");
		printf("────────────────█████████─────────────── \n");
		printf("──────────────█████████████───────────── \n");
	
	}else{
		printf("Poxa! Você perdeu!!\n");
		printf("A palavra era %s\n", palavra);
		printf("Tente novamente!");


		printf("\n");
		printf("  ___________.._______     \n");
		printf(" | .__________))______|    \n");
		printf(" | | / /      ||           \n");
		printf(" | |/ /       ||           \n");
		printf(" | | /        ||.-''.      \n");
		printf(" | |/         |/  _  \\    \n");
		printf(" | |          ||  `/,|     \n");
		printf(" | |          (\\`_.'      \n");
		printf(" | |         .-`--'.       \n");
		printf(" | |        /Y . . Y\\     \n");
		printf(" | |       // |   | \\\\   \n");
		printf(" | |      //  | . |  \\\\  \n");
		printf(" | |     ')   |   |   (`   \n");
		printf(" | |          ||'||        \n");
		printf(" | |          || ||        \n");
		printf(" | |          || ||        \n");
		printf(" | |          || ||        \n");
		printf(" | |         / | | \\      \n");
	    printf(" |'|'''''''| `-' `-' |'|   \n");
        printf(" |'|''''''\\ \\        |'| \n");
        printf(" | |       \\ \\       | | \n");
    	printf(" : :        \\ \\      : : \n");
    	printf(" . .         `'      . .   \n");		
	}
}
