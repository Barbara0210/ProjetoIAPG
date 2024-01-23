#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#define TAM_NOME 512

typedef struct perguntas {
    char categoria[TAM_NOME];
    char pergunta[TAM_NOME];
    char resposta1[TAM_NOME];
    char resposta2[TAM_NOME];
    char resposta3[TAM_NOME];
    char respostacerta[TAM_NOME];
} PERGUNTAS;

typedef struct jogador {
    char nome[TAM_NOME];
    int pontuacao;
    int n_respostas_certas;
} JOGADOR;

JOGADOR calcular_vencedor(int n_jogadores, JOGADOR *jogadores);
int inserir_jogadores(JOGADOR *jogadores);
void ler_ficheiro(PERGUNTAS * array_conteudo);
void verificar_resposta(int a, int b,int aux, int retorno, JOGADOR *jogadores, PERGUNTAS * array_conteudo, char answer);
void incrementar_pontuacao(JOGADOR *jogadores);
void guardar_resultados(int n_jogadores, JOGADOR *jogadores);