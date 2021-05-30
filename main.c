#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QNT_JOGADORES 2

#define MAX_TAM_MATRIZ 100
#define MAX_QNT_PALAVRAS 25 
#define MAX_TAM_NOME 17 
#define MAX_TAM_PALAVRA 17 

#define PONTO_PALAVRA_PROPRIA 2
#define PONTO_PALAVRA_OUTRO 1

#define POS_NAO_REVELADA '-'

#define HORIZONTAL 0
#define VERTICAL 1
#define DIAGONAL 2
#define INVERTIDO -1
#define NORMAL -2
#define DIAGONAL_BAIXO_CIMA 12
#define DIAGONAL_CIMA_BAIXO 21

typedef struct {
    int numMapaOrdenado;
    char palavra[MAX_TAM_PALAVRA];
    int tamPalavra;
    int posicoes[MAX_TAM_MATRIZ][2];
    int posL; //linha da primeira posição da palavra
    int posC; //Coluna da primeira posição da palavra
    int inclinacao;
    int ordem;
    int encontrada; //Para saber se a palavra ja foi encontrda ou não
    int letrasEncontradas;
    int jogadaQueFoiEncontrada;
    int pontos;
} tPalavra;

typedef struct {
    int tamMatriz;
    char matriz[MAX_TAM_MATRIZ][MAX_TAM_MATRIZ];
    char posicaoNaoRevelada;
} tMatriz;

typedef struct {
    int id;
    char nome[MAX_TAM_NOME];
    int pontuacao;
    int numPalavras;
    int numPalavrasRestantes;
    int pontosFeitos;
    int pontoRecebidos;
    tPalavra palavras[MAX_QNT_PALAVRAS];
    tPalavra palavrasRestantes[MAX_QNT_PALAVRAS];
} tJogador;

typedef struct {
    int numMapaOrdenado;
    tMatriz matriz;
    tMatriz tabuleiro;
    int maxJogadasCadaJogador;
    tJogador jogadores[QNT_JOGADORES];
} tJogo;

//tJogo
tJogo CriarJogo(FILE *arquivoConfig);
tJogo IniciarJogo(tJogo jogo);
tJogo FazerJogada(tJogador jogadorDaJogada, int l, int c, tJogo jogo, int jogada);
tJogo GerarArquivoDeInicializacao(tJogo jogo, FILE *arquivoInicializacao);
void GerarAquivoEstatisticas(tJogo jogo, FILE *arquivoEstatistica);
void FinalizarJogo(tJogo jogo);
tMatriz ObterMatrizJogo(tJogo jogo);
tJogador ObterJogador(tJogo jogo, int pos);
int ObterNumeroDeLinhasJogo(tJogo jogo);
void ImprimePalavrasRestantes(tJogo jogo);
void MostraTabuleiro(tJogo jogo);
tJogo AtualizarPalavrasRestantesJogo(tJogo jogo);
int AcabaramAsPalavras(tJogo jogo);
int EhPosicaoRepetidaJogo(tJogo jogo, int l, int c);
int EhJogadaInvalidaJogo(tJogo jogo, int l, int c);
void OrdenarPalavrasEncontradasNoJogo(tJogo jogo, tPalavra palavras[], int quantTotal);
tJogador SubtrairQuantidadeDePalavrasRestantesJogador(tJogador jogador);
void GerarMapaOrdenado(tJogo jogo, FILE *arquivoMapaOrdenado);

//tPalavra
tPalavra CriarPalavra(char palavra[], tMatriz matriz);
tPalavra EncontrarInclinacao(tMatriz matriz, tPalavra palavra);
tPalavra ENcontrarPosicoes(tPalavra palavra);
int ObterTamanhoDaPalavra(tPalavra palavra);
int JaFoiEncontradaPalavra(tPalavra palavra);
char StringPalavra(tPalavra palavra, int pos);
void ObterStringPalavra(tPalavra tpalavra, char palavra[]);
int ObterLinhaPrimeiraPosicaoPalavra(tPalavra palavra);
int ObterColunaPrimeiraPosicaoPalavra(tPalavra palavra);
void ObterPosicoesPalavra(tPalavra palavra, int posicoes[][2]);
int ObterQuantidadeLetrasEncontradaspalavra(tPalavra palavra); //inutil
tPalavra MarcarComoEncontradaPalavra(tPalavra palavra);
tPalavra AdicionarUmaLetraEncontrada(tPalavra palavra);
void ImprimirPalavra(tPalavra palavra);
void ImprimirPalavraFormatada(tPalavra palavra);
char ObterPrimeiraLetraPalavra(tPalavra palavra);
void ImprimirPalavraNoArquivo(tPalavra palavra, FILE *arquivo);
void ImprimirPalavraNoArquivoFormatada(tPalavra palavra, FILE *arquivo);
int ObterJogadaQueFoiEncontradaPalavra(tPalavra palavra);
tPalavra AdicionarPontuacaoPalavra(tPalavra palavra, int pontos);
int ObterPontuacaoPalavra(tPalavra palavra);
tPalavra AdicionarJogadaQueFoiEncontradaPalavra(tPalavra palavra, int jogada);
tPalavra AdicionarNumMapaOrdenado(tPalavra palavra, int num);
int ObterNumMapaOrdenadoPalavra(tPalavra palavra);

//tJogador
tJogador CriarJogador(int id, int numPalavras, FILE *arquivoConfig, tMatriz matriz);
tJogador IniciarPalavrasRestantesJogador(tJogador jogador);
int ObterPontuacaoJogador(tJogador jogador);
int ObterIdJogador(tJogador jogador);
void ObterNomeJogador(tJogador jogador, char nome[]);
int ObterTamanhoNomeJogador(tJogador jogador);
int ObterNumeroDePalavrasJogador(tJogador jogador);
int ObterNumeroDePalavrasRestantesJogador(tJogador jogador);
tPalavra ObterMaiorPalavraJogador(tJogador jogador);
tPalavra ObterPalavraJogador(tJogador jogador, int pos);
tPalavra ObterPalavraRestanteJogador(tJogador jogador, int pos);
tJogador AdicionarPontosJogador(tJogador jogador, int pontuacao);
tJogador MarcarComoEncontradaPalavraDoJogador(tPalavra palavra, tJogador jogador, int pos);
tJogador AtualizarPalavrasRestantesJogador(tJogador jogador);
void ImprimirPalavrasJogador(tJogador jogador, FILE *arquivoInicializacao);
void ImprimirLetrasIniciaisJogador(tJogador jogador, FILE *arquivoInicializao);
tPalavra ObterMaiorPalavraJogador(tJogador jogador);
int ObterPontosFeitosJogador(tJogador jogador);
int ObterPontosRecebidosJogador(tJogador jogador);
tJogador AdicionarPontoFeitoJogador(tJogador jogador, int ponto);
tJogador AdicionarPontoRecebidoJogador(tJogador jogador, int ponto);
tJogador AlterarPalavraJogador(tJogador jogador, tPalavra palavra, int pos);

//tMatriz
tMatriz CriarMatriz(int tamMatriz, FILE *arquivoConfig);
tMatriz CriarTabuleiro(tMatriz matriz);
int ObterTamanhoDaMatriz(tMatriz matriz);
char ObterCaracterNaPosicaoMatriz(tMatriz matriz, int i, int j);
void ImprimirTabuleiro(tMatriz tabuleiro);
int VerificarSePosicaoJaFoiJogadaMatriz(tMatriz matriz, int l, int c);
int VerificarSePosicaoEstaForaDaMatriz(tMatriz matriz, int l, int c);

int main(int argc, char** argv) {

    if (argc <= 1) { //Verifica se foi digitado o endereço do arquivo
        printf("ERRO: O diretório de arquivos de configuração não foi informado\n");
        return 0;
    }

    char config[1001];
    char inicializacao[1001];
    char estatisticas[1001];
    char mapaOrdenado[1001];

    sprintf(inicializacao, "%s/saida/Inicializacao.txt", argv[1]);
    sprintf(estatisticas, "%s/saida/Estatisticas.txt", argv[1]);
    sprintf(mapaOrdenado, "%s/saida/MapaOrdenado.txt", argv[1]);
    sprintf(config, "%s/config.txt", argv[1]);

    FILE* arquivoMapaOrdenado = fopen(mapaOrdenado, "w");
    FILE* arquivoConfig = fopen(config, "r");
    FILE* arquivoInicializacao = fopen(inicializacao, "w");
    FILE* arquivoEstatistica = fopen(estatisticas, "w");


    tJogo jogo = CriarJogo(arquivoConfig);
    fclose(arquivoConfig);

    GerarArquivoDeInicializacao(jogo, arquivoInicializacao);
    fclose(arquivoInicializacao);

    jogo = IniciarJogo(jogo);

    GerarAquivoEstatisticas(jogo, arquivoEstatistica);
    fclose(arquivoEstatistica);

    GerarMapaOrdenado(jogo, arquivoMapaOrdenado);
    fclose(arquivoMapaOrdenado);

    return (EXIT_SUCCESS);
}

tJogo CriarJogo(FILE *arquivoConfig) {
    tJogo jogo;
    tMatriz mapaOrdenado;
    int maxJogadas, tamMatriz, numPalavras;
    int i, j;
    char palavrasJogador[MAX_QNT_PALAVRAS][MAX_TAM_PALAVRA];
    char c;

    //Leitura da duração do turno
    fscanf(arquivoConfig, "%d", &maxJogadas);
    jogo.maxJogadasCadaJogador = maxJogadas;

    //Leitura da matriz de palavras
    fscanf(arquivoConfig, "%d", &tamMatriz);
    fscanf(arquivoConfig, "%*c");
    tMatriz matriz = CriarMatriz(tamMatriz, arquivoConfig);
    jogo.matriz = matriz;

    //Inicia o contador do mapa ordenado 
    jogo.numMapaOrdenado = 1;

    //Leitura do numero de palavras de cada jogador
    fscanf(arquivoConfig, "%d", &numPalavras);

    //Cria jogadores e adiciona ao jogo
    for (i = 0; i < QNT_JOGADORES; i++) {
        tJogador jogador = CriarJogador(i + 1, numPalavras, arquivoConfig, matriz);
        jogo.jogadores[i] = jogador;
    }

    return jogo;
}

tJogo IniciarJogo(tJogo jogo) {
    ImprimePalavrasRestantes(jogo);
    tMatriz tabuleiro = CriarTabuleiro(jogo.matriz);
    jogo.tabuleiro = tabuleiro;
    MostraTabuleiro(jogo);

    int jogada = 0;
    int repetida, invalida;
    int i, j, n;
    int l, c; //Coordenadas da jogada 
    tJogador jogador;

    //Para cada turno
    for (i = 0; i < jogo.maxJogadasCadaJogador; i++) {
        //Para cada jogador
        for (j = 0; j < QNT_JOGADORES; j++) {
            jogada++;
            jogador = jogo.jogadores[j];
            char nome[ObterTamanhoNomeJogador(jogador) + 1];
            ObterNomeJogador(jogador, nome);

            printf("\n%s por favor entre com as coordenadas para a sua jogada:\n", nome);


            while (1) {
                scanf("%d%d", &l, &c);
                if (EhJogadaInvalidaJogo(jogo, l, c)) {
                    ImprimePalavrasRestantes(jogo);
                    MostraTabuleiro(jogo);
                    printf("\nCoordenadas fora do tabuleiro.%s por favor entre com novas coordenadas para a sua jogada:\n", nome);

                } else if (EhPosicaoRepetidaJogo(jogo, l, c)) {
                    ImprimePalavrasRestantes(jogo);
                    MostraTabuleiro(jogo);
                    printf("\nCoordenadas ja jogadas.%s por favor entre com novas coordenadas para a sua jogada:\n", nome);
                } else {
                    jogo = FazerJogada(jogador, l, c, jogo, jogada);
                    jogo = AtualizarPalavrasRestantesJogo(jogo);
                    ImprimePalavrasRestantes(jogo);
                    MostraTabuleiro(jogo);
                    break;
                }

            }

            if (AcabaramAsPalavras(jogo)) {
                FinalizarJogo(jogo);
                return jogo;
            }
        }
    }
    FinalizarJogo(jogo);

    return jogo;
}

void ImprimePalavrasRestantes(tJogo jogo) {
    char nomes[QNT_JOGADORES][MAX_TAM_NOME];
    int pontuacao[QNT_JOGADORES];
    int i, j, k;

    //Atribuição das informações dos jogadores
    for (i = 0; i < QNT_JOGADORES; i++) {
        // char nome[ObterTamanhoNomeJogador(jogo.jogadores[i]) + 1];
        char nome[MAX_TAM_NOME];
        ObterNomeJogador(jogo.jogadores[i], nome);
        strcpy(nomes[i], nome);
        pontuacao[i] = ObterPontuacaoJogador(jogo.jogadores[i]);
    }

    //Cabeçalho
    printf("|            Palavras Restantes           |\n");
    for (i = 0; i < QNT_JOGADORES; i++) {
        printf("|%-16s(%02d)", nomes[i], pontuacao[i]);
    }
    printf("|\n");
    printf("|--------------------|--------------------|\n");

    char aux[28] = {0};
    int numLinhas = ObterNumeroDeLinhasJogo(jogo);
    //Para cada linha impressa
    for (i = 0; i < numLinhas; i++) {
        //Para cada jogador
        for (j = 0; j < QNT_JOGADORES; j++) {
            if (i < ObterNumeroDePalavrasRestantesJogador(jogo.jogadores[j])) {
                tPalavra palavraRestante = ObterPalavraRestanteJogador(jogo.jogadores[j], i);
                ImprimirPalavraFormatada(palavraRestante);
            } else {

                printf("|%-20s", aux);
            }
        }
        printf("|\n");
    }
}

void MostraTabuleiro(tJogo jogo) {
    printf("\n");

    int i, j;
    char c;
    int tamMatriz = ObterTamanhoDaMatriz(jogo.matriz);
    //Imprime indices da coluna do  tabuleiro
    printf("   ");
    for (i = 0; i < tamMatriz; i++) {
        printf(" %02d", i);
    }

    printf("\n");

    //Para cada linha
    for (i = 0; i < tamMatriz; i++) {
        printf("%02d|", i);
        //Para cada coluna
        for (j = 0; j < tamMatriz; j++) {

            printf(" %c ", ObterCaracterNaPosicaoMatriz(jogo.tabuleiro, i, j));
        }
        printf("|\n");
    }
}

void FinalizarJogo(tJogo jogo) {
    tJogador jogador, vencedor;
    int empate = 0;

    int i;
    //Para cada jogador
    for (i = 0; i < QNT_JOGADORES; i++) {
        jogador = jogo.jogadores[i];
        if (i == 0 || ObterPontuacaoJogador(jogador) > ObterPontuacaoJogador(vencedor))
            vencedor = jogo.jogadores[i];
        if (ObterPontuacaoJogador(jogo.jogadores[0]) == ObterPontuacaoJogador(jogo.jogadores[1]))
            empate++;
    }

    int tam = ObterTamanhoNomeJogador(vencedor) + 1;
    char nome[tam];

    if (empate) {
        printf("\nEmpate");
    } else {
        ObterNomeJogador(vencedor, nome);
        printf("\n%s Ganhou!!!", nome);
    }

}

tJogo FazerJogada(tJogador jogadorDaJogada, int l, int c, tJogo jogo, int jogada) {
    int i, j, p;
    tJogador jogador;
    tPalavra palavra;

    //Para cada jogador
    for (j = 0; j < QNT_JOGADORES; j++) {
        jogador = jogo.jogadores[j];
        //Para cada palava 
        for (p = 0; p < ObterNumeroDePalavrasJogador(jogador); p++) {
            palavra = ObterPalavraJogador(jogador, p);

            //Se for a primeira letra da palavra
            if (l == ObterLinhaPrimeiraPosicaoPalavra(palavra) &&
                    c == ObterColunaPrimeiraPosicaoPalavra(palavra)) {

                int posicoes[ObterTamanhoDaPalavra(palavra)][2];
                ObterPosicoesPalavra(palavra, posicoes);

                //Se o jogador acertou sua própria palavra
                if (ObterIdJogador(jogadorDaJogada) == ObterIdJogador(jogador)) {
                    jogadorDaJogada = AdicionarPontosJogador(jogadorDaJogada, PONTO_PALAVRA_PROPRIA);
                    jogadorDaJogada = AdicionarPontoFeitoJogador(jogadorDaJogada, PONTO_PALAVRA_PROPRIA);

                    palavra = MarcarComoEncontradaPalavra(palavra);
                    jogadorDaJogada = AlterarPalavraJogador(jogadorDaJogada, palavra, p);
                    jogadorDaJogada = SubtrairQuantidadeDePalavrasRestantesJogador(jogadorDaJogada);

                    palavra = AdicionarPontuacaoPalavra(palavra, PONTO_PALAVRA_PROPRIA);
                    jogadorDaJogada = AlterarPalavraJogador(jogadorDaJogada, palavra, p);

                    palavra = AdicionarJogadaQueFoiEncontradaPalavra(palavra, jogada);
                    jogadorDaJogada = AlterarPalavraJogador(jogadorDaJogada, palavra, p);

                    palavra = AdicionarNumMapaOrdenado(palavra, jogo.numMapaOrdenado);
                    jogo.numMapaOrdenado++;
                    jogadorDaJogada = AlterarPalavraJogador(jogadorDaJogada, palavra, p);

                    jogo.jogadores[ObterIdJogador(jogadorDaJogada) - 1] = jogadorDaJogada;
                }//Se o jogador acertou a palavra de outro
                else {
                    jogador = AdicionarPontosJogador(jogador, PONTO_PALAVRA_OUTRO);
                    jogador = AdicionarPontoRecebidoJogador(jogador, PONTO_PALAVRA_OUTRO);

                    palavra = MarcarComoEncontradaPalavra(palavra);
                    jogador = AlterarPalavraJogador(jogador, palavra, p);
                    jogador = SubtrairQuantidadeDePalavrasRestantesJogador(jogador);

                    palavra = AdicionarPontuacaoPalavra(palavra, PONTO_PALAVRA_OUTRO);
                    jogador = AlterarPalavraJogador(jogador, palavra, p);

                    palavra = AdicionarJogadaQueFoiEncontradaPalavra(palavra, jogada);
                    jogador = AlterarPalavraJogador(jogador, palavra, p);

                    palavra = AdicionarNumMapaOrdenado(palavra, jogo.numMapaOrdenado);
                    jogo.numMapaOrdenado++;
                    jogador = AlterarPalavraJogador(jogador, palavra, p);

                    jogo.jogadores[ObterIdJogador(jogador) - 1] = jogador;
                }

                //Mostra a primeira letra maiuscula
                jogo.tabuleiro.matriz[l][c] = jogo.matriz.matriz[l][c]+('Z' - 'z');

                //Para o resto da palavra
                for (i = 1; i < ObterTamanhoDaPalavra(palavra); i++) {
                    //Se a letra ja estiver em maiusculo
                    if (jogo.tabuleiro.matriz[posicoes[i][0]][posicoes[i][1]] >= 'A'
                            && jogo.tabuleiro.matriz[posicoes[i][0]][posicoes[i][1]] <= 'Z') {
                        jogo.tabuleiro.matriz[posicoes[i][0]][posicoes[i][1]] =
                                jogo.matriz.matriz[posicoes[i][0]][posicoes[i][1]]+('Z' - 'z');
                    } else {
                        jogo.tabuleiro.matriz[posicoes[i][0]][posicoes[i][1]] =
                                jogo.matriz.matriz[posicoes[i][0]][posicoes[i][1]];
                    }
                }
                return jogo;
            }
        }
    }
    //Caso não seja primeira letra de uma palavra
    jogo.tabuleiro.matriz[l][c] = jogo.matriz.matriz[l][c]+('Z' - 'z');

    return jogo;
}

tJogo AtualizarPalavrasRestantesJogo(tJogo jogo) {
    int i = 0, j, p;
    tJogador jogador;
    tPalavra palavra;

    //Para cada jogador
    for (j = 0; j < QNT_JOGADORES; j++) {

        jogador = jogo.jogadores[j];
        jogo.jogadores[j] = AtualizarPalavrasRestantesJogador(jogador);
    }
    return jogo;
}

tMatriz ObterMatrizJogo(tJogo jogo) {

    return jogo.matriz;
}

void GerarMapaOrdenado(tJogo jogo, FILE *arquivoMapaOrdenado) {
    tJogador jogador;
    tPalavra palavra;
    int tam=ObterTamanhoDaMatriz(jogo.matriz);
    int mapaOrdenado[tam][tam];
    int posicoes[MAX_TAM_PALAVRA][2];
    int  p;

    //Zera o mapa ordenado
    int i, j;
    for (i = 0; i < tam; i++) {
        for (j = 0; j < tam; j++) {
            mapaOrdenado[i][j] = 0;
        }
    }

    //Preenche o mapa
    //Para cada jogador
    for (j = 0; j < QNT_JOGADORES; j++) {
        jogador = jogo.jogadores[j];
        //Para cada palava 
        for (p = 0; p < ObterNumeroDePalavrasJogador(jogador); p++) {
            palavra = ObterPalavraJogador(jogador, p);
            ObterPosicoesPalavra(palavra, posicoes);
            //Para cada letra da palavra
            for (i = 0; i < ObterTamanhoDaPalavra(palavra); i++) {
                //Se a posicao esta vazia e a palavra foi achada
                if (mapaOrdenado[posicoes[i][0]][posicoes[i][1]] == 0 &&
                        ObterNumMapaOrdenadoPalavra(palavra) != 0)
                        mapaOrdenado[posicoes[i][0]][posicoes[i][1]] = ObterNumMapaOrdenadoPalavra(palavra);
            }
        }
    }

    //Printa o mapa
    for (i = 0; i < tam; i++) {
        for (j = 0; j < tam; j++) {
            if (mapaOrdenado[i][j] == 0)
                fprintf(arquivoMapaOrdenado, " --");
	    else{
		//CORRECAO:formatacao do print do %d 
        	fprintf(arquivoMapaOrdenado, " %02d",mapaOrdenado[i][j]);
		}
        }
        fprintf(arquivoMapaOrdenado, "\n");
    }

}

tJogador ObterJogador(tJogo jogo, int pos) {

    return jogo.jogadores[pos];
}

int ObterNumeroDeLinhasJogo(tJogo jogo) {
    int maiorQnt = 0;
    int j;
    for (j = 0; j < QNT_JOGADORES; j++) {

        if (ObterNumeroDePalavrasRestantesJogador(jogo.jogadores[j]) > maiorQnt)
            maiorQnt = ObterNumeroDePalavrasRestantesJogador(jogo.jogadores[j]);
    }
    return maiorQnt;
}

int AcabaramAsPalavras(tJogo jogo) {
    int i, quant = 0;
    for (i = 0; i < QNT_JOGADORES; i++) {
        if (ObterNumeroDePalavrasRestantesJogador(jogo.jogadores[i]) == 0)

            return 1;
    }

    return 0;
}

int EhPosicaoRepetidaJogo(tJogo jogo, int l, int c) {
    if (VerificarSePosicaoJaFoiJogadaMatriz(jogo.tabuleiro, l, c))
        return 1;

    else
        return 0;
}

int EhJogadaInvalidaJogo(tJogo jogo, int l, int c) {
    if (VerificarSePosicaoEstaForaDaMatriz(jogo.matriz, l, c))
        return 1;

    else
        return 0;
}

tJogo GerarArquivoDeInicializacao(tJogo jogo, FILE *arquivoInicializacao) {
    tJogador jogador;
    char nome[MAX_TAM_NOME];
    int j, p;
    for (j = 0; j < QNT_JOGADORES; j++) {

        jogador = jogo.jogadores[j];
        ObterNomeJogador(jogador, nome);
        fprintf(arquivoInicializacao, "--Jogador %d--\n", ObterIdJogador(jogador));
        fprintf(arquivoInicializacao, "Nome: %s\n", nome);
        fprintf(arquivoInicializacao, "Palavras:\n");
        ImprimirPalavrasJogador(jogador, arquivoInicializacao);
        fprintf(arquivoInicializacao, "Maior Palavra: \n");
        ImprimirPalavraNoArquivo(ObterMaiorPalavraJogador(jogador), arquivoInicializacao);
        fprintf(arquivoInicializacao, "\nLetras Iniciais: \n");
        ImprimirLetrasIniciaisJogador(jogador, arquivoInicializacao);
        if(j<QNT_JOGADORES-1)
            fprintf(arquivoInicializacao,"\n");
    }

}

void GerarAquivoEstatisticas(tJogo jogo, FILE *arquivoEstatistica) {
    int quantPalavrasTotal = (ObterNumeroDePalavrasJogador(jogo.jogadores[0]) * QNT_JOGADORES);
    tJogador jogador;
    tPalavra palavra;
    tPalavra palavras[quantPalavrasTotal];
    char nome[MAX_TAM_NOME];

    fprintf(arquivoEstatistica, "--------------\n");
    fprintf(arquivoEstatistica, "--- PONTOS ---\n");
    fprintf(arquivoEstatistica, "--------------\n\n");

    int i, j;
    for (j = 0; j < QNT_JOGADORES; j++) {
        jogador = jogo.jogadores[j];
        ObterNomeJogador(jogador, nome);
        fprintf(arquivoEstatistica, "%s\n", nome);
        fprintf(arquivoEstatistica, "Feitos: %d\n", ObterPontosFeitosJogador(jogador));
        fprintf(arquivoEstatistica, "Recebidos: %d\n", ObterPontosRecebidosJogador(jogador));
        fprintf(arquivoEstatistica, "Total: %d\n\n", ObterPontuacaoJogador(jogador));
    }

    fprintf(arquivoEstatistica, "---------------------------\n");
    fprintf(arquivoEstatistica, "--- PALAVRAS POR PONTOS ---\n");
    fprintf(arquivoEstatistica, "---------------------------\n\n");
    fprintf(arquivoEstatistica, "|P|     Palavra    | T |\n");
    fprintf(arquivoEstatistica, "|-|----------------|---|\n");

    OrdenarPalavrasEncontradasNoJogo(jogo, palavras, quantPalavrasTotal);
    for (i = 0; i < quantPalavrasTotal; i++) {

        palavra = palavras[i];
        fprintf(arquivoEstatistica, "|%d|", ObterPontuacaoPalavra(palavra));
        ImprimirPalavraNoArquivoFormatada(palavra, arquivoEstatistica);
        fprintf(arquivoEstatistica, "|%03d|\n", ObterJogadaQueFoiEncontradaPalavra(palavra));
    }

}

void OrdenarPalavrasEncontradasNoJogo(tJogo jogo, tPalavra palavras[], int quantTotal) {
    int i = 0, j, p, cont0 = 0, cont1 = 0, cont2 = 0;
    tPalavra aux;
    tJogador jogador;
    tPalavra palavras0[quantTotal];
    tPalavra palavras1[quantTotal];
    tPalavra palavras2[quantTotal];
    char palavraAux1[MAX_TAM_PALAVRA];
    char palavraAux2[MAX_TAM_PALAVRA];

    //Cria uma lista com todas as palavras
    for (j = 0; j < QNT_JOGADORES; j++) {
        jogador = jogo.jogadores[j];
        //Armazena cada palavra
        for (p = 0; p < ObterNumeroDePalavrasJogador(jogador); p++) {
            palavras[i] = ObterPalavraJogador(jogador, p);
            i++;
        }
    }

    //Separa as palavras em lista para as 3 possisveis pontuacoes:0,1,2
    for (i = 0; i < quantTotal; i++) {
        if (ObterPontuacaoPalavra(palavras[i]) == 0) {
            palavras0[cont0] = palavras[i];
            cont0++;
        }
        if (ObterPontuacaoPalavra(palavras[i]) == 1) {
            palavras1[cont1] = palavras[i];
            cont1++;
        }
        if (ObterPontuacaoPalavra(palavras[i]) == 2) {
            palavras2[cont2] = palavras[i];
            cont2++;
        }
    }

    //Ordena as palavras com pontuacao 2
    for (i = 0; i < cont2; i++) {
        for (j = 0; j < cont2; j++) {
            ObterStringPalavra(palavras2[i], palavraAux1);
            ObterStringPalavra(palavras2[j], palavraAux2);
            if (strcmp(palavraAux1, palavraAux2) < 0) {
                aux = palavras2[i];
                palavras2[i] = palavras2[j];
                palavras2[j] = aux;
            }
        }
    }

    //Ordena as palavras com pontuacao 1
    for (i = 0; i < cont1; i++) {
        for (j = 0; j < cont1; j++) {
            ObterStringPalavra(palavras1[i], palavraAux1);
            ObterStringPalavra(palavras1[j], palavraAux2);
            if (strcmp(palavraAux1, palavraAux2) < 0) {
                aux = palavras1[i];
                palavras1[i] = palavras1[j];
                palavras1[j] = aux;
            }
        }
    }

    //Ordena as palavras com pontuacao 0
    for (i = 0; i < cont0; i++) {
        for (j = 0; j < cont0; j++) {
            ObterStringPalavra(palavras0[i], palavraAux1);
            ObterStringPalavra(palavras0[j], palavraAux2);
            if (strcmp(palavraAux1, palavraAux2) < 0) {
                aux = palavras0[i];
                palavras0[i] = palavras0[j];
                palavras0[j] = aux;
            }
        }
    }

    //Junta as 3 listas
    j = 0;
    for (i = 0; i < cont2; i++) {
        palavras[j] = palavras2[i];
        j++;
    }
    for (i = 0; i < cont1; i++) {
        palavras[j] = palavras1[i];
        j++;

    }
    for (i = 0; i < cont0; i++) {
        palavras[j] = palavras0[i];
        j++;
    }
}

tJogador CriarJogador(int id, int numPalavras, FILE *arquivoConfig, tMatriz matriz) {

    tJogador jogador;
    jogador.id = id;
    jogador.numPalavras = numPalavras;
    jogador.pontoRecebidos = 0;
    jogador.pontosFeitos = 0;
    jogador.pontuacao = 0;
    int i;
    char palavra[MAX_TAM_PALAVRA];

    //Leitura das palavras e nome do jogador
    for (i = 0; i < jogador.numPalavras; i++) {
        fscanf(arquivoConfig, "%s", &palavra); //Limite do tamanho da palavra
        fscanf(arquivoConfig, "%*c"); //Apaga o "\n" do aqruivo
        jogador.palavras[i] = CriarPalavra(palavra, matriz);
    }
    printf("Nome do Jogador %d:\n", jogador.id);
    scanf("%16s", &jogador.nome);

    jogador = IniciarPalavrasRestantesJogador(jogador);

    return jogador;
}

tJogador IniciarPalavrasRestantesJogador(tJogador jogador) {
    int i, j = 0;
    for (i = 0; i < jogador.numPalavras; i++) {
        int palavraFoiEncontrada = JaFoiEncontradaPalavra(jogador.palavras[i]);
        //Se a palavra ainda não foi encontrada
        if (!palavraFoiEncontrada) {
            jogador.palavrasRestantes[j] = jogador.palavras[i];
            j++;
        }
    }
    jogador.numPalavrasRestantes = j;

    return jogador;
}

int ObterPontuacaoJogador(tJogador jogador) {

    return jogador.pontuacao;
}

int ObterTamanhoNomeJogador(tJogador jogador) {

    return strlen(jogador.nome);
}

int ObterNumeroDePalavrasJogador(tJogador jogador) {

    return jogador.numPalavras;
}

tPalavra ObterPalavraJogador(tJogador jogador, int pos) {

    return jogador.palavras[pos];
}

tPalavra ObterPalavraRestanteJogador(tJogador jogador, int pos) {

    return jogador.palavrasRestantes[pos];
}

void ObterNomeJogador(tJogador jogador, char nome[]) {

    strcpy(nome, jogador.nome);
}

tJogador AdicionarPontosJogador(tJogador jogador, int pontuacao) {
    jogador.pontuacao += pontuacao;

    return jogador;
}

int ObterIdJogador(tJogador jogador) {

    return jogador.id;
}

int ObterNumeroDePalavrasRestantesJogador(tJogador jogador) {

    return jogador.numPalavrasRestantes;
}

tJogador AtualizarPalavrasRestantesJogador(tJogador jogador) {
    int numPalavras = jogador.numPalavras;
    tPalavra palavra;
    int i, j = 0;
    //Para cada palavra
    for (i = 0; i < numPalavras; i++) {
        palavra = jogador.palavras[i];
        int palavraFoiEncontrada = JaFoiEncontradaPalavra(jogador.palavras[i]);
        //Se a palavra ainda não foi encontrada
        if (!palavraFoiEncontrada) {

            jogador.palavrasRestantes[j] = jogador.palavras[i];
            j++;
        }
    }

    return jogador;
}

void ImprimirPalavrasJogador(tJogador jogador, FILE * arquivoInicializacao) {
    tPalavra palavra;
    int i;
    for (i = 0; i < jogador.numPalavras; i++) {

        palavra = jogador.palavras[i];
        ImprimirPalavraNoArquivo(palavra, arquivoInicializacao);
        fprintf(arquivoInicializacao, "\n");
    }
}

tPalavra ObterMaiorPalavraJogador(tJogador jogador) {
    tPalavra maiorPalavra;
    int i;
    for (i = 0; i < jogador.numPalavras; i++) {

        if (i == 0 || ObterTamanhoDaPalavra(jogador.palavras[i]) > ObterTamanhoDaPalavra(maiorPalavra))
            maiorPalavra = jogador.palavras[i];
    }


    return maiorPalavra;
}

void ImprimirLetrasIniciaisJogador(tJogador jogador, FILE * arquivoInicializao) {
    int num = jogador.numPalavras;
    char iniciais[num];
    char aux;
    int cont = 0, contRepetidas = 0;

    int i, j;
    //Armazena as primeiras letras de cada palavra
    for (i = 0; i < num; i++) {
        iniciais[i] = ObterPrimeiraLetraPalavra(jogador.palavras[i]);
    }

    //Coloca as letras iniciais em odem alfabetica
    for (i = 0; i < num; i++) {
        for (j = i; j < num; j++) {
            if (iniciais[i] > iniciais[j]) {
                aux = iniciais[i];
                iniciais[i] = iniciais[j];
                iniciais[j] = aux;
            }
        }
    }

    //Conta e imprime quantas vezes cada uma apareceu
    for (i = 0; i < num; i++) {
        if (i > 0 && iniciais[i] == iniciais[i - 1])
            continue;

        for (j = i; j < num; j++) {
            if (iniciais[i] == iniciais[j])
                cont++;
        }
        fprintf(arquivoInicializao, "%c -> %d\n", iniciais[i], cont);
        contRepetidas += cont;
        if (contRepetidas == num)

            break;
        cont = 0;

    }

}

int ObterPontosFeitosJogador(tJogador jogador) {

    return jogador.pontosFeitos;
}

int ObterPontosRecebidosJogador(tJogador jogador) {

    return jogador.pontoRecebidos;
}

tJogador AdicionarPontoFeitoJogador(tJogador jogador, int ponto) {
    jogador.pontosFeitos += ponto;

    return jogador;
}

tJogador AdicionarPontoRecebidoJogador(tJogador jogador, int ponto) {
    jogador.pontoRecebidos += ponto;

    return jogador;
}

tJogador AlterarPalavraJogador(tJogador jogador, tPalavra palavra, int pos) {
    jogador.palavras[pos] = palavra;

    return jogador;
}

tJogador SubtrairQuantidadeDePalavrasRestantesJogador(tJogador jogador) {
    jogador.numPalavrasRestantes--;

    return jogador;
}

tMatriz CriarMatriz(int tamMatriz, FILE * arquivoConfig) {
    tMatriz matriz;
    matriz.tamMatriz = tamMatriz;
    char c;
    int i, j;

    //Leitura da matriz de palavras
    for (i = 0; i < matriz.tamMatriz; i++) {
        for (j = 0; j < matriz.tamMatriz; j++) {

            fscanf(arquivoConfig, "%c", &c);
            matriz.matriz[i][j] = c;
            // printf("%c",c);
        }
        fscanf(arquivoConfig, "%*c");
        // printf("\n");
    }

    return matriz;
}

int ObterTamanhoDaMatriz(tMatriz matriz) {

    return matriz.tamMatriz;
}

tMatriz CriarTabuleiro(tMatriz matriz) {
    tMatriz tabuleiro;
    tabuleiro.tamMatriz = matriz.tamMatriz;
    tabuleiro.posicaoNaoRevelada = POS_NAO_REVELADA;
    int i, j;
    for (i = 0; i < matriz.tamMatriz; i++) {
        for (j = 0; j < matriz.tamMatriz; j++) {

            tabuleiro.matriz[i][j] = tabuleiro.posicaoNaoRevelada;
        }
    }
    return tabuleiro;
}

void ImprimirTabuleiro(tMatriz tabuleiro) {
    int i, j;
    for (i = 0; i < tabuleiro.tamMatriz; i++) {
        for (j = 0; j < tabuleiro.tamMatriz; j++) {

            printf("%c", tabuleiro.matriz[i][j]);
        }
    }
}

char ObterCaracterNaPosicaoMatriz(tMatriz matriz, int i, int j) {

    return matriz.matriz[i][j];
}

int VerificarSePosicaoJaFoiJogadaMatriz(tMatriz tabuleiro, int l, int c) {

    return (tabuleiro.matriz[l][c] >= 'A' && tabuleiro.matriz[l][c] <= 'Z');
}

int VerificarSePosicaoEstaForaDaMatriz(tMatriz matriz, int l, int c) {

    return (l > matriz.tamMatriz || l < 0 || c > matriz.tamMatriz || c < 0);

}

tPalavra CriarPalavra(char palavra[], tMatriz matriz) {
    tPalavra tpalavra;
    tpalavra.numMapaOrdenado = 0;
    tpalavra.encontrada = 0; //A palavra começa como não encontrada
    tpalavra.letrasEncontradas = 0; //Quantidade de letras acertadas na matriz
    tpalavra.pontos = 0;
    strcpy(tpalavra.palavra, palavra);
    tpalavra.tamPalavra = strlen(palavra);
    tpalavra = EncontrarInclinacao(matriz, tpalavra);
    tpalavra = ENcontrarPosicoes(tpalavra);

    return tpalavra;
}

int ObterTamanhoDaPalavra(tPalavra palavra) {

    return strlen(palavra.palavra);
}

tPalavra EncontrarInclinacao(tMatriz tmatriz, tPalavra tpalavra) {
    int tamMatriz = ObterTamanhoDaMatriz(tmatriz);
    int i, j;
    //Para cada linha
    for (i = 0; i < tamMatriz; i++) {
        //Para cada coluna
        for (j = 0; j < tamMatriz; j++) {
            //Se a primeira letra for encontrada
            if (tpalavra.palavra[0] == tmatriz.matriz[i][j]) {
                int p; //Indice da palavra
                int t = 0; //Conta quantas letras da palvra estao na posicao correta
                int l; //Percorre as linhas da matriz 
                int c; //percorre as colunas da matriz

                //A palavra está na horizontal e normal
                for (p = 0, c = j; p < tpalavra.tamPalavra && c >= 0 && c <= tamMatriz
                        && tpalavra.palavra[p] == tmatriz.matriz[i][c]; p++, c++) {
                    // if (tpalavra.palavra[p] == tmatriz.matriz[i][c])
                    t++;
                }
                //Se t for do mesmo tamanho da palavra então ela foi encontrada na matriz
                if (t == tpalavra.tamPalavra) {
                    tpalavra.inclinacao = HORIZONTAL;
                    tpalavra.ordem = NORMAL;
                    tpalavra.posL = i; //A linha da posição da primeira letra da palavra
                    tpalavra.posC = j; //A coluna da posição da primeira letra da palavra
                    return tpalavra;

                }
                t = 0;

                //A palavra está na horizontal e invertida
                for (p = 0, c = j; p < tpalavra.tamPalavra && c >= 0 && c <= tamMatriz; p++, c--) {
                    if (tpalavra.palavra[p] == tmatriz.matriz[i][c])
                        t++;
                }
                //Se t for do mesmo tamanho da palavra então ela foi encontrada na matriz
                if (t == tpalavra.tamPalavra) {
                    tpalavra.inclinacao = HORIZONTAL;
                    tpalavra.ordem = INVERTIDO;
                    tpalavra.posL = i;
                    tpalavra.posC = j;
                    return tpalavra;

                }
                t = 0;

                //A palavra está na vertical e normal
                for (p = 0, l = i; p < tpalavra.tamPalavra && l >= 0 && l <= tamMatriz; p++, l++) {
                    if (tpalavra.palavra[p] == tmatriz.matriz[l][j])
                        t++;
                }
                //Se t for do mesmo tamanho da palavra então ela foi encontrada na matriz
                if (t == tpalavra.tamPalavra) {
                    tpalavra.inclinacao = VERTICAL;
                    tpalavra.ordem = NORMAL;
                    tpalavra.posL = i;
                    tpalavra.posC = j;
                    return tpalavra;

                }
                t = 0;

                //A palavra está na vertical e invertida
                for (p = 0, l = i; p < tpalavra.tamPalavra && l >= 0 && l <= tamMatriz; p++, l--) {
                    if (tpalavra.palavra[p] == tmatriz.matriz[l][j])
                        t++;
                }
                //Se t for do mesmo tamanho da palavra então ela foi encontrada na matriz
                if (t == tpalavra.tamPalavra) {
                    tpalavra.inclinacao = VERTICAL;
                    tpalavra.ordem = INVERTIDO;
                    tpalavra.posL = i;
                    tpalavra.posC = j;
                    return tpalavra;

                }
                t = 0;

                //A palavra está na diagonal, normal e de baixo pra cima
                for (p = 0, l = i, c = j; p < tpalavra.tamPalavra && l >= 0 &&
                        l <= tamMatriz && c >= 0 && c <= tamMatriz; p++, l--, c++) {
                    if (tpalavra.palavra[p] == tmatriz.matriz[l][c])
                        t++;
                }
                //Se t for do mesmo tamanho da palavra então ela foi encontrada na matriz
                if (t == tpalavra.tamPalavra) {
                    tpalavra.inclinacao = DIAGONAL_BAIXO_CIMA;
                    tpalavra.ordem = NORMAL;
                    tpalavra.posL = i;
                    tpalavra.posC = j;
                    return tpalavra;

                }
                t = 0;

                //A palavra está na diagonal, invertida e de cima pra baixo
                for (p = 0, l = i, c = j; p < tpalavra.tamPalavra && l >= 0 &&
                        l <= tamMatriz && c >= 0 && c <= tamMatriz; p++, l++, c--) {
                    if (tpalavra.palavra[p] == tmatriz.matriz[l][c])
                        t++;
                }
                //Se t for do mesmo tamanho da palavra então ela foi encontrada na matriz
                if (t == tpalavra.tamPalavra) {
                    tpalavra.inclinacao = DIAGONAL_CIMA_BAIXO;
                    tpalavra.ordem = INVERTIDO;
                    tpalavra.posL = i;
                    tpalavra.posC = j;
                    return tpalavra;

                }
                t = 0;

                //A palavra está na diagonal, normal e de cima pra baixo
                for (p = 0, l = i, c = j; p < tpalavra.tamPalavra && l >= 0 &&
                        l <= tamMatriz && c >= 0 && c <= tamMatriz; p++, l++, c++) {
                    if (tpalavra.palavra[p] == tmatriz.matriz[l][c])
                        t++;
                }
                //Se t for do mesmo tamanho da palavra então ela foi encontrada na matriz
                if (t == tpalavra.tamPalavra) {
                    tpalavra.inclinacao = DIAGONAL_CIMA_BAIXO;
                    tpalavra.ordem = NORMAL;
                    tpalavra.posL = i;
                    tpalavra.posC = j;
                    return tpalavra;

                }
                t = 0;

                //A palavra está na diagonal, invertida e de baixo pra cima
                for (p = 0, l = i, c = j; p < tpalavra.tamPalavra && l >= 0 &&
                        l <= tamMatriz && c >= 0 && c <= tamMatriz; p++, l--, c--) {
                    if (tpalavra.palavra[p] == tmatriz.matriz[l][c])
                        t++;
                }
                //Se t for do mesmo tamanho da palavra então ela foi encontrada na matriz
                if (t == tpalavra.tamPalavra) {
                    tpalavra.inclinacao = DIAGONAL_BAIXO_CIMA;
                    tpalavra.ordem = INVERTIDO;
                    tpalavra.posL = i;
                    tpalavra.posC = j;

                    return tpalavra;

                }
                t = 0;
            }
        }
    }
}

tPalavra ENcontrarPosicoes(tPalavra palavra) {
    int i, j;
    int p = 0; //Indice das posicoes das letras da palavra

    //Para palavra na horizontal
    if (palavra.inclinacao == HORIZONTAL) {
        if (palavra.ordem == NORMAL) {
            for (j = palavra.posC; p < palavra.tamPalavra; j++, p++) {
                palavra.posicoes[p][0] = palavra.posL; //Linha da letra na posição p da palavra
                palavra.posicoes[p][1] = j; //Coluna da letra na posição p da palavra
            }
        } else {//Caso contrário a palavra está invertida 
            for (j = palavra.posC; p < palavra.tamPalavra; j--, p++) {
                palavra.posicoes[p][0] = palavra.posL; //Linha da letra na posição p da palavra
                palavra.posicoes[p][1] = j; //Coluna da letra na posição p da palavra
            }
        }

        //Para palavra na vertical
    } else if (palavra.inclinacao == VERTICAL) {
        if (palavra.ordem == NORMAL) {
            for (i = palavra.posL; p < palavra.tamPalavra; i++, p++) {
                palavra.posicoes[p][0] = i; //Linha da letra na posição p da palavra
                palavra.posicoes[p][1] = palavra.posC; //Coluna da letra na posição p da palavra
            }
        } else {//Caso contrário a palavra está invertida 
            for (i = palavra.posL; p < palavra.tamPalavra; i--, p++) {
                palavra.posicoes[p][0] = i; //Linha da letra na posição p da palavra
                palavra.posicoes[p][1] = palavra.posC; //Coluna da letra na posição p da palavra
                ;
            }
        }
        //Para palavra na diagonal
    } else {
        if (palavra.ordem == NORMAL) {
            if (palavra.inclinacao == DIAGONAL_BAIXO_CIMA) {
                for (i = palavra.posL, j = palavra.posC; p < palavra.tamPalavra; i--, j++, p++) {
                    palavra.posicoes[p][0] = i; //Linha da letra na posição p da palavra
                    palavra.posicoes[p][1] = j; //Coluna da letra na posição p da palavra
                }
            }
            if (palavra.inclinacao == DIAGONAL_CIMA_BAIXO) {
                for (i = palavra.posL, j = palavra.posC; p < palavra.tamPalavra; i++, j++, p++) {
                    palavra.posicoes[p][0] = i; //Linha da letra na posição p da palavra
                    palavra.posicoes[p][1] = j; //Coluna da letra na posição p da palavra
                }
            }
        } else {//Caso contrário a palavra está invertida 
            if (palavra.inclinacao == DIAGONAL_BAIXO_CIMA) {
                for (i = palavra.posL, j = palavra.posC; p < palavra.tamPalavra; i--, j--, p++) {
                    palavra.posicoes[p][0] = i; //Linha da letra na posição p da palavra
                    palavra.posicoes[p][1] = j; //Coluna da letra na posição p da palavra
                }
            }
            if (palavra.inclinacao == DIAGONAL_CIMA_BAIXO) {
                for (i = palavra.posL, j = palavra.posC; p < palavra.tamPalavra; i++, j--, p++) {

                    palavra.posicoes[p][0] = i; //Linha da letra na posição p da palavra
                    palavra.posicoes[p][1] = j; //Coluna da letra na posição p da palavra
                }
            }
        }
    }
    return palavra;
}

int JaFoiEncontradaPalavra(tPalavra palavra) {
    if (palavra.letrasEncontradas == palavra.tamPalavra)
        palavra.encontrada = 1;

    return palavra.encontrada;
}

char StringPalavra(tPalavra palavra, int pos) {

    return palavra.palavra[pos];
}

int PosicoesPalavra(tPalavra palavra, int posLetra, int i) {

    return palavra.posicoes[posLetra][i];
}

int ObterLinhaPrimeiraPosicaoPalavra(tPalavra palavra) {

    return palavra.posL;
}

int ObterColunaPrimeiraPosicaoPalavra(tPalavra palavra) {

    return palavra.posC;
}

void ObterStringPalavra(tPalavra tpalavra, char palavra[]) {

    strcpy(palavra, tpalavra.palavra);
}

void ObterPosicoesPalavra(tPalavra palavra, int posicoes[][2]) {
    int i, j;
    for (i = 0; i < palavra.tamPalavra; i++) {
        for (j = 0; j < 2; j++) {

            posicoes[i][j] = palavra.posicoes[i][j];
        }
    }
}

tPalavra MarcarComoEncontradaPalavra(tPalavra palavra) {
    palavra.encontrada = 1;

    return palavra;
}

int ObterQuantidadeLetrasEncontradaspalavra(tPalavra palavra) {

    return palavra.letrasEncontradas;
}

tPalavra AdicionarUmaLetraEncontrada(tPalavra palavra) {
    palavra.letrasEncontradas++;

    return palavra;
}

void ImprimirPalavra(tPalavra palavra) {

    printf("%s", palavra.palavra);
}

void ImprimirPalavraNoArquivo(tPalavra palavra, FILE * arquivo) {

    fprintf(arquivo, "%s", palavra.palavra);
}

void ImprimirPalavraNoArquivoFormatada(tPalavra palavra, FILE * arquivo) {

    fprintf(arquivo, "%-16s", palavra.palavra);
}

void ImprimirPalavraFormatada(tPalavra palavra) {

    printf("|%-20s", palavra.palavra);
}

char ObterPrimeiraLetraPalavra(tPalavra palavra) {

    return palavra.palavra[0];
}

int ObterJogadaQueFoiEncontradaPalavra(tPalavra palavra) {

    return palavra.jogadaQueFoiEncontrada;
}

tPalavra AdicionarPontuacaoPalavra(tPalavra palavra, int pontos) {
    palavra.pontos = pontos;

    return palavra;
}

int ObterPontuacaoPalavra(tPalavra palavra) {

    return palavra.pontos;
}

tPalavra AdicionarJogadaQueFoiEncontradaPalavra(tPalavra palavra, int jogada) {
    palavra.jogadaQueFoiEncontrada = jogada;
    return palavra;
}

tPalavra AdicionarNumMapaOrdenado(tPalavra palavra, int num) {
    palavra.numMapaOrdenado = num;
    return palavra;
}

int ObterNumMapaOrdenadoPalavra(tPalavra palavra) {
    return palavra.numMapaOrdenado;
}
