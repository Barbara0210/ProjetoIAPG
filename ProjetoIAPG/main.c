#include "main.h"

void jogo() {
    PERGUNTAS array_informacao[TAM_NOME]; //declaração do vetor array_informacao que é um vetor do tipo da estrutura perguntas
    JOGADOR jogadores[TAM_NOME];//declaração do vetor jogadores que é do tipo da estrutura jogador

    int numero_jogadores = inserir_jogadores(jogadores); //chama a funcao inserir_jogadores que le o numero e nome dos jogadores

    char answer;
    int retorno = 0;
srand((time(NULL)));
    ler_ficheiro(array_informacao);//funçao que le o ficheiro
    int numero_rondas;
    printf("Quantas rondas deseja jogar: ");
    scanf("%d",&numero_rondas);
    for (int a = 0; a < numero_jogadores; a++) {// 2 for que imprimem para cada jogador as perguntas e as opcoes de resposta
        for (int b =0 ; b < numero_rondas; b++) {
            int  aux=rand()%10;//gera um nº aleatorio para apresentarmos perguntas aleatorias
            printf("Jogador: %s \n", jogadores[a+1].nome);
            printf("N respostas certas: %d \n", jogadores[a+1].n_respostas_certas);
            printf("Pontuacao: %d \n", jogadores[a+1].pontuacao);
            printf("Pergunta: %s \n", array_informacao[aux].pergunta);
            printf("Opcao A: %s \n", array_informacao[aux].resposta1);
            printf("Opcao B: %s \n", array_informacao[aux].resposta2);
            printf("Opcao C: %s \n", array_informacao[aux].resposta3);
            printf("Opcao D: Usar Token \n");
            fflush(stdin);
            printf("Insira a sua resposta: ");
            answer = getchar();
            verificar_resposta(a, b,aux, retorno, jogadores, array_informacao, answer);//chama a função que verifica a resposta do jogador
        }
    }

    JOGADOR jog_vencedor = calcular_vencedor(numero_jogadores, jogadores); //chama a funcao que calcula o vencedor
    printf("Vencedor: %s \t Pontos: %d\n\n",jog_vencedor.nome, jog_vencedor.pontuacao);

    int export;
    printf("Deseja exportar os resultados do jogo?\n");
    printf("1 - Sim\n");
    printf("2 - Nao\n");
    scanf("%d", &export);

    switch (export) {
        case 1:
            guardar_resultados(numero_jogadores, jogadores);//chama a funcao que exporta os dados do jogo
            break;
        case 2:
            return;
        default:
            return;
    }
}

void verificar_resposta(int a, int b,int aux, int retorno, JOGADOR *jogadores, PERGUNTAS * array_informacao, char answer) { // funcao que verifica as respostas dos jogadores

    switch (answer) {
        case 'A':
        case 'a':
            retorno=strcmp(array_informacao[aux].resposta1,array_informacao[aux].respostacerta);
            break;
        case 'B':
        case 'b':
            retorno=strcmp(array_informacao[aux].resposta2,array_informacao[aux].respostacerta);
            break;
        case 'C':
        case 'c':
            retorno=strcmp(array_informacao[aux].resposta3,array_informacao[aux].respostacerta);
            break;
        case 'D':
        case 'd':
            printf("Voce usou o seu token!\n");
            printf("A resposta correta e: %s \n", array_informacao[aux].respostacerta);
            break;
    }

    if (retorno!=0) {
        printf("Errou! \n\n");
    } else {
        printf("Acertou :) \n\n");
        incrementar_pontuacao(&jogadores[a+1]); //funcao que aumenta a pontuacao dos jogadores se acertarem a resposta
    }
}

int inserir_jogadores(JOGADOR *jogadores) { // funcao que le o numero e nome dos jogadores
    int numero_jogadores = 0;
    printf("Insira o numero de jogadores: ");
    scanf("%d", &numero_jogadores);

    for (int j = 1; j <= numero_jogadores; j++) {
        printf("Insira o nome do %d jogador: ", j);
        scanf("%s", jogadores[j].nome);
    }

    return numero_jogadores;
}

void ler_ficheiro(PERGUNTAS * array_informacao) { //funcao que le o ficheiro e guarda no vetor array_informacao a informacao do ficheiro
    FILE *fp;
    int i = 0;
    char *delim = ";";
    char linha[TAM_NOME];

    fp = fopen("..\\data\\perguntas.csv", "r");
    if (fp == NULL) {
        printf("Erro ao abrir o ficheiro! ");
    }

    while (fgets(linha, sizeof(linha), (FILE *) fp) != NULL) {
        strcpy(array_informacao[i].categoria, strtok(linha, delim));
        strcpy(array_informacao[i].pergunta, strtok(NULL, delim));
        strcpy(array_informacao[i].resposta1, strtok(NULL, delim));
        strcpy(array_informacao[i].resposta2, strtok(NULL, delim));
        strcpy(array_informacao[i].resposta3, strtok(NULL, delim));
        strcpy(array_informacao[i].respostacerta, strtok(NULL, delim));

        array_informacao[i].respostacerta[strlen(array_informacao[i].respostacerta) - 1] = '\0';
        i++;
    }
    fclose(fp);

}

void incrementar_pontuacao(JOGADOR *jogadores) {//funcao que incrementa a pontuacao e as respostas certas do jogador
    jogadores -> pontuacao = jogadores -> pontuacao + 5;
    jogadores -> n_respostas_certas = jogadores -> n_respostas_certas + 1;
}

JOGADOR calcular_vencedor(int numero_jogadores, JOGADOR *jogadores){//funcao que calcula vencedor
    int pos;
    for (int c = 1;c <=numero_jogadores;c++) {
        if (jogadores[c].pontuacao > jogadores[c + 1].pontuacao) {
            pos = c;
        }
    }

    return jogadores[pos];
}

void guardar_resultados(int numero_jogadores, JOGADOR *jogadores) {//função qur guarda resultados e imprime tudo para um ficheiro
    FILE *fp;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    fp = fopen("C:..\\data\\resultados.txt", "a");
    if (fp == NULL) {
        printf("Erro ao abrir o ficheiro! ");
        exit(1);
    }

    fprintf(fp,"data da partida: %d-%02d-%02d %02d:%02d:%02d\n",
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    for(int i=1; i<=numero_jogadores; i++) {
        fprintf(fp, "Jogador: %s \t Pontuacao: %d \t Respostas Certas: %d\n", jogadores[i].nome, jogadores[i].pontuacao, jogadores[i].n_respostas_certas);
    }
    fprintf(fp,"\n");
    fclose(fp);
}

int main() {
    printf("Bem vindo ao jogo das perguntas!!\n");
    printf("Para comecar insere o numero de jogadores que irao jogar e em seguida os seus nomes :) \n");
    jogo();
    return 0;
}