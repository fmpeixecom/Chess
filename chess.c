#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define RESET "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define ORANGE "\x1B[33m"

void showBoard(char deColuna, int deLinha, int paraLinha, char paraColuna, char casa[8][8], char prom);
int validateRook(char deColuna, int deLinha, int paraLinha, char paraColuna, char casa[8][8]);
int validateKnight(char deColuna, int deLinha, int paraLinha, char paraColuna, char casa[8][8]);
int validateSquares(char deColuna, int deLinha, int paraLinha, char paraColuna, char casa[8][8]);
int validateBishop(char deColuna, int deLinha, int paraLinha, char paraColuna, char casa[8][8]);
int validateCanibalism(char deColuna, int deLinha, int paraLinha, char paraColuna, char casa[8][8]);
int validateKing(char deColuna, int deLinha, int paraLinha, char paraColuna, char casa[8][8]);
int validateQuennCross(char deColuna, int deLinha, int paraLinha, char paraColuna, char casa[8][8]);
int validateQueenDiagonals(char deColuna, int deLinha, int paraLinha, char paraColuna, char casa[8][8]);
int validatePawn(char deColuna, int deLinha, int paraLinha, char paraColuna, char casa[8][8]);
int validatePlayer(char casa[8][8], int deLinha, int deColuna);
int validateEndOfGame(int paraLinha, int paraColuna, char casa[8][8]);
void squares(char casa[8][8]);
int addCapturesPoints(int paraLinha, int paraColuna, char casa[8][8]);
int defineCapturedPieces(int paraLinha, int paraColuna, char casa[8][8]);
void showEvaluationBar(int i);
void engine(char casa[8][8]);
void engineBlackKing(char casa[8][8], int i, int j);
void engineBlackKnight(char casa[8][8], int i, int j);
void engineBlackBishop(char casa[8][8], int i, int j);
void engineBlackRook(char casa[8][8], int i, int j);
void engineBlackPawn(char casa[8][8], int i, int j);
void engineWhiteKing(char casa[8][8], int i, int j);
void engineWhiteKnight(char casa[8][8], int i, int j);
void engineWhiteBishop(char casa[8][8], int i, int j);
void engineWhiteRook(char casa[8][8], int i, int j);
void engineWhitePawn(char casa[8][8], int i, int j);
void legal(char casa[8][8]);
void legalReiPreto(char casa[8][8], int i, int j);
void legalCavaloPreto(char casa[8][8], int i, int j);
void legalBispoPreto(char casa[8][8], int i, int j);
void legalTorrePreta(char casa[8][8], int i, int j);
void legalPeaoPreto(char casa[8][8], int i, int j);
void legalReiBranco(char casa[8][8], int i, int j);
void legalCavaloBranco(char casa[8][8], int i, int j);
void legalBispoBranco(char casa[8][8], int i, int j);
void legalTorreBranco(char casa[8][8], int i, int j);
void legalPeaoBranco(char casa[8][8], int i, int j);
int moves = 0;
int pointsCapturedWhite = 0;
int pointsCapturedBlack = 0;
char pecasCapturadasBrancas[16];
int numeroPecasCapturadasBrancas = 0;
char pecasCapturadasPretas[16];
int numeroPecasCapturadasPretas = 0;
float vantagemPreta = 0;
float vantagemBranca = 0;
int jogadaIlegal = 0;

const float vantPeao[8][8] = {
   /*8*/ {10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f},
   /*7*/ { 3.5f,  4.0f,  4.0f,  4.0f,  4.0f,  4.0f,  4.0f,  3.5f},
   /*6*/ { 0.6f,  0.9f,  0.9f,  0.9f,  0.9f,  0.9f,  0.9f,  0.6f},
   /*5*/ { 0.2f,  0.3f,  0.4f,  0.5f,  0.5f,  0.3f,  0.3f,  0.2f},
   /*4*/ { 0.0f,  0.1f,  0.1f,  0.2f,  0.2f,  0.1f,  0.1f,  0.0f},
   /*3*/ { 0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
   /*2*/ { 0.0f,  0.1f,  0.1f,  0.1f,  0.1f,  0.1f,  0.1f,  0.0f},
   /*1*/ { 0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f}
};

const float vantCavalo[8][8] = {
   /*8*/ { 0.1f,  0.1f,  0.1f,  0.2f,  0.2f,  0.1f,  0.1f,  0.1f},
   /*7*/ { 0.5f,  0.5f,  0.5f,  0.6f,  0.6f,  0.5f,  0.5f,  0.5f},
   /*6*/ { 0.6f,  0.9f,  0.9f,  0.9f,  0.9f,  0.9f,  0.9f,  0.6f},
   /*5*/ { 0.3f,  0.4f,  0.5f,  0.7f,  0.7f,  0.5f,  0.4f,  0.3f},
   /*4*/ { 0.3f,  0.3f,  0.4f,  0.4f,  0.4f,  0.4f,  0.3f,  0.3f},
   /*3*/ { 0.2f,  0.2f,  0.2f,  0.3f,  0.3f,  0.2f,  0.2f,  0.2f},
   /*2*/ { 0.1f,  0.2f,  0.2f,  0.3f,  0.3f,  0.2f,  0.2f,  0.1f},
   /*1*/ { 0.0f,  0.1f,  0.1f,  0.1f,  0.1f,  0.1f,  0.1f,  0.0f}
};          /*a*/  /*b*/  /*c*/  /*d*/  /*e*/ /*f*/  /*g*/  /*h*/ 

const float vantBispo[8][8] = {
   /*8*/ {-0.4f, -0.4f, -0.4f, -0.4f, -0.4f, -0.4f, -0.4f, -0.4f},
   /*7*/ { 0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f},
   /*6*/ { 0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f},
   /*5*/ { 0.5f,  0.5f,  0.6f,  0.6f,  0.6f,  0.6f,  0.5f,  0.5f},
   /*4*/ { 0.5f,  0.5f,  0.8f,  0.6f,  0.6f,  0.8f,  0.5f,  0.5f},
   /*3*/ { 0.5f,  0.8f,  0.6f,  0.6f,  0.6f,  0.6f,  0.8f,  0.5f},
   /*2*/ { 0.6f,  0.8f,  0.8f,  0.7f,  0.7f,  0.8f,  0.8f,  0.6f},
   /*1*/ { 0.6f,  0.6f,  0.6f,  0.5f,  0.5f,  0.6f,  0.6f,  0.6f}
};          /*a*/  /*b*/  /*c*/  /*d*/  /*e*/ /*f*/  /*g*/  /*h*/ 

const float vantTorre[8][8] = {
   /*8*/ { 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f},
   /*7*/ { 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f},
   /*6*/ { 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f},
   /*5*/ { 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f},
   /*4*/ { 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.4f,  1.3f,  1.3f},
   /*3*/ { 1.1f,  1.1f,  1.0f,  1.0f,  1.0f,  1.0f,  1.1f,  1.1f},
   /*2*/ { 1.1f,  1.1f,  1.0f,  1.1f,  1.1f,  1.0f,  1.1f,  1.1f},
   /*1*/ { 1.1f,  1.1f,  1.0f,  1.2f,  1.2f,  1.0f,  1.1f,  1.1f}
};          /*a*/  /*b*/  /*c*/  /*d*/  /*e*/ /*f*/  /*g*/  /*h*/ 

const float vantDama[8][8] = {
   /*8*/ { 2.3f,  2.3f,  2.3f,  2.3f,  2.3f,  2.3f,  2.3f,  2.3f},
   /*7*/ { 2.3f,  2.3f,  2.3f,  2.3f,  2.3f,  2.3f,  2.3f,  2.3f},
   /*6*/ { 2.3f,  2.3f,  2.3f,  2.3f,  2.3f,  2.3f,  2.3f,  2.3f},
   /*5*/ { 2.3f,  2.3f,  2.3f,  2.3f,  2.3f,  2.3f,  2.3f,  2.3f},
   /*4*/ { 2.3f,  2.3f,  2.3f,  2.3f,  2.3f,  2.3f,  2.3f,  2.3f},
   /*3*/ { 2.3f,  2.3f,  2.3f,  2.3f,  2.3f,  2.3f,  2.3f,  2.3f},
   /*2*/ { 2.3f,  2.3f,  2.3f,  2.3f,  2.3f,  2.3f,  2.3f,  2.3f},
   /*2*/ { 2.3f,  2.3f,  2.3f,  2.3f,  2.3f,  2.3f,  2.3f,  2.3f}
};          /*a*/  /*b*/  /*c*/  /*d*/  /*e*/ /*f*/  /*g*/  /*h*/ 

const float vantRei[8][8] = {
   /*8*/ { 0.1f,  0.1f,  0.1f,  0.1f,  0.1f,  0.1f,  0.1f,  0.1f},
   /*7*/ { 0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
   /*6*/ { 0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
   /*5*/ { 0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
   /*4*/ { 0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
   /*3*/ { 0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
   /*2*/ { 0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
   /*1*/ { 0.1f,  0.2f,  0.1f, -0.3f, -0.1f,  0.1f,  0.2f,  0.1f}
};          /*a*/  /*b*/  /*c*/  /*d*/  /*e*/ /*f*/  /*g*/  /*h*/ 

int main()
{
    char casa[8][8];
    char deColuna;
    int deLinha;
    int paraLinha;
    char paraColuna;
    char prom = ' ';
    system("clear");
    squares(casa);
	while(1)
	{        
		printf("A peça que vai jogar está na casa: ");
		scanf("%c%d", &deColuna, &deLinha);
		printf("Vai para a casa: ");
		getchar();
		scanf("%c%d", &paraColuna, &paraLinha);
		getchar();
		showBoard(deColuna, deLinha, paraLinha, paraColuna, casa, prom);//chama-se a função showBoard
	}

    return 0;
}

void showBoard(char deColuna, int deLinha, int paraLinha, char paraColuna, char casa[8][8], char prom)
{
    //corresponder a cada letra que o utilizador escreveu um número de coluna
    switch(deColuna)
    {
        case 'a':
            deColuna = 1;
            break;
        case 'b':
            deColuna = 2;
            break;
        case 'c':
            deColuna = 3;
            break;
        case 'd':
            deColuna = 4;
            break;
        case 'e':
            deColuna = 5;
            break;
        case 'f':
            deColuna = 6;
            break;
        case 'g':
            deColuna = 7;
            break;
        case 'h':
            deColuna = 8;
            break;
        default:
            deColuna = 9;
            break;
    }
    switch(paraColuna)
    {
        case 'a':
            paraColuna = 1;
            break;
        case 'b':
            paraColuna = 2;
            break;
        case 'c':
            paraColuna = 3;
            break;
        case 'd':
            paraColuna = 4;
            break;
        case 'e':
            paraColuna = 5;
            break;
        case 'f':
            paraColuna = 6;
            break;
        case 'g':
            paraColuna = 7;
            break;
        case 'h':
            paraColuna = 8;
            break;
        default:
            paraColuna = 9;
            break;
    }
    jogadaIlegal = 0;
    char temporario = casa[9 - paraLinha - 1][paraColuna - 1];
    casa[9 - paraLinha-1][paraColuna-1] = casa[9 - deLinha-1][deColuna-1];
    casa[9 - deLinha-1][deColuna-1] = ' ';
    legal(casa);
    casa[9 - deLinha - 1][deColuna - 1] = casa[9 - paraLinha-1][paraColuna-1];
    casa[9 - paraLinha-1][paraColuna-1] = temporario;
    if(validateSquares(deColuna, deLinha, paraLinha, paraColuna, casa) == 1)
    {
        printf(ORANGE"     ->A casa de destino tem que ser diferente da casa de partida\n"RESET);
    }
    else if(deColuna == 9 || paraColuna == 9 || deLinha < 1 || deLinha > 8 || paraLinha < 1 || paraLinha > 8)
    {
        printf(ORANGE"      ->Coordenadas inválidas\n"RESET);
    }
    else if(validatePlayer(casa, deLinha, deColuna) == 1)
    {
        printf(ORANGE"     ->Não é a sua vez.\n"RESET);
    }
    else if(validateCanibalism(deColuna, deLinha, paraLinha, paraColuna, casa) == 1)
    {
        printf(ORANGE"     ->Não pode capturar as suas próprias peças\n"RESET);
    }
    else if(validateRook(deColuna, deLinha, paraLinha, paraColuna, casa) == 1)
    {
        printf(ORANGE"     ->A Torre não pode saltar por cima de peças\n"RESET);
    }
    else if(validateRook(deColuna, deLinha, paraLinha, paraColuna, casa) == 2)
    {
        printf(ORANGE"     ->A torre move-se na horizontal ou vertical\n"RESET);
    }
    else if(validateKnight(deColuna, deLinha, paraLinha, paraColuna, casa) == 1)
    {
        printf(ORANGE"     ->Movimento inválido do cavalo\n"RESET);
    }
    else if(validateKing(deColuna, deLinha, paraLinha, paraColuna, casa) == 1)
    {
        printf(ORANGE"     ->O rei pode apenas mover-se para qualquer casa imediatemente ao lado\n"RESET);
    }
    else if(validateBishop(deColuna, deLinha, paraLinha, paraColuna, casa) == 1)
    {
        printf(ORANGE"     ->O bispo pode apenas mover-se na diagonal\n"RESET);
    }
    else if(validateBishop(deColuna, deLinha, paraLinha, paraColuna, casa) == 2)
    {
        printf(ORANGE"     ->O bispo não pode saltar por cima de peças\n"RESET);
    }
    else if((validateQuennCross(deColuna, deLinha, paraLinha, paraColuna, casa) == 1 && validateQueenDiagonals(deColuna, deLinha, paraLinha, paraColuna, casa) == 2) || (validateQuennCross(deColuna, deLinha, paraLinha, paraColuna, casa) == 1 && validateQueenDiagonals(deColuna, deLinha, paraLinha, paraColuna, casa) == 1))
    {
        printf(ORANGE"     ->A dama não pode saltar por cima de peças\n"RESET);
    }
    else if((validateQueenDiagonals(deColuna, deLinha, paraLinha, paraColuna, casa) == 1 && validateQuennCross(deColuna, deLinha, paraLinha, paraColuna, casa) == 2) || (validateQueenDiagonals(deColuna, deLinha, paraLinha, paraColuna, casa) == 1 && validateQuennCross(deColuna, deLinha, paraLinha, paraColuna, casa) == 1))
    {
        printf(ORANGE"     ->A dama pode apenas mover-se na vertical, horizontal e diagonal\n"RESET);
    }
    else if((validateQuennCross(deColuna, deLinha, paraLinha, paraColuna, casa) == 2 && validateQueenDiagonals(deColuna, deLinha, paraLinha, paraColuna, casa) == 1) || (validateQuennCross(deColuna, deLinha, paraLinha, paraColuna, casa) == 2 && validateQueenDiagonals(deColuna, deLinha, paraLinha, paraColuna, casa) == 2))
    {
        printf(ORANGE"     ->A dama pode apenas mover-se na vertical, horizontal e diagonal\n"RESET);
    }
    else if((validateQueenDiagonals(deColuna, deLinha, paraLinha, paraColuna, casa) == 2 && validateQuennCross(deColuna, deLinha, paraLinha, paraColuna, casa) == 1) || (validateQueenDiagonals(deColuna, deLinha, paraLinha, paraColuna, casa) == 2 && validateQuennCross(deColuna, deLinha, paraLinha, paraColuna, casa) == 2))
    {
        printf(ORANGE"     ->A dama pode apenas mover-se na vertical, horizontal e diagonal\n"RESET);
    }
    else if(validatePawn(deColuna, deLinha, paraLinha, paraColuna, casa) == 1)
    {
        printf(ORANGE"     ->Movimento inválido do peão\n"RESET);
    }
    else if(validatePawn(deColuna, deLinha, paraLinha, paraColuna, casa) == 2)
    {
        printf(ORANGE"     ->O peão não pode saltar por cima de squares\n"RESET);
    }
    else if(validateEndOfGame(paraLinha, paraColuna, casa) == 2)
    {
        printf("\n\n\n\n\n\n\n-------------------------------------------+ O jogador de brancas ganhou +------------------------------------------\n\n\n\n\n\n\n\n\n");
        exit(10);
    }
    else if(validateEndOfGame(paraLinha, paraColuna, casa) == 1)
    {
        printf("\n\n\n\n\n\n\n--------------------------------------------+ O jogador de pretas ganhou +------------------------------------------\n\n\n\n\n\n\n\n\n");
        exit(10);
    }
    else if(jogadaIlegal == 1)
    {
        printf(ORANGE"     ->Jogada Ilegal\n"RESET);
    }
    else
    {
        if(validateKing(deColuna, deLinha, paraLinha, paraColuna, casa) == 2)
        {
            casa[7][7] = ' ';
            casa[7][5] = 'T';
        }
        else if(validateKing(deColuna, deLinha, paraLinha, paraColuna, casa) == 3)
        {
            casa[7][0] = ' ';
            casa[7][3] = 'T';
        }
        else if(validateKing(deColuna, deLinha, paraLinha, paraColuna, casa) == 4)
        {
            casa[0][7] = ' ';
            casa[0][5] = 't';
        }
        else if(validateKing(deColuna, deLinha, paraLinha, paraColuna, casa) == 5)
        {
            casa[0][0] = ' ';
            casa[0][3] = 't';
        }
        else if(validatePawn(deColuna, deLinha, paraLinha, paraColuna, casa) == 3)
        {
            if(moves % 2 == 0)//são as brancas
            {
                printf("Quer promover para (D, T, B, C):");
                getchar();
                scanf("%c", &prom);
                prom = toupper(prom);
                casa[8 - deLinha][deColuna - 1] = prom;
            }
            else//são as negras
            {
                printf("Quer promover para (d, t, b, c):");
                getchar();
                scanf("%c", &prom);
                casa[8 - deLinha][deColuna - 1] = prom;
            }
        }
        addCapturesPoints(paraLinha, paraColuna, casa);        
        defineCapturedPieces(paraLinha, paraColuna, casa);
        if(validatePawn(deColuna, deLinha, paraLinha, paraColuna, casa) != 3)
        {
            casa[9 - paraLinha-1][paraColuna-1] = casa[9 - deLinha-1][deColuna-1];
            casa[9 - deLinha-1][deColuna-1] = ' ';
        }        
        //começar a imprimir o tabuleiro
        system("clear");
        printf("\n\n");
        printf("O jogador de brancas já capturou as peças: ");
        for(int i = 0; i < numeroPecasCapturadasBrancas; i++)
        {
            if(i>0)
            {
                printf(", ");
            }
            printf("%c", pecasCapturadasBrancas[i]);
        }
        printf("    (%d pontos)", pointsCapturedWhite);
        printf("\n\n");
        printf("O jogador de pretas já capturou as peças: ");
        for(int i = 0; i < numeroPecasCapturadasPretas; i++)
        {
            if(i>0)
            {
                printf(", ");
            }
            printf("%c", pecasCapturadasPretas[i]);
        }
        printf("    (%d pontos)", pointsCapturedBlack);
        printf("\n\n");
        if(moves % 2 == 1)
        {
            printf("-------------------------------------------------------------É a vez das BRANCAS----------------------------------------------------------\n\n\n");
        }
        else
        {
            printf("-------------------------------------------------------------É a vez das PRETAS-----------------------------------------------------------\n\n\n");
        }
        engine(casa);
	    if(moves % 2 == 1)
        {
            printf("        ");
            for(int i = 0; i < 8; i++)//mostra a linha de cima
            {
                printf("+---");
            }
            printf("+");
            printf("\n");
            for(int i = 0; i < 16; i++)//linhas
            {
                showEvaluationBar(i);
                printf("%d. |", 8 - i/2);
                for(int j = 0; j < 8; j++)//colunas
                {
                    if(casa[i/2][j] == toupper(casa[i/2][j]))
                    {
                    printf(RED" %c "RESET, casa[i/2][j]);
                    }
                    else
                    {
                        printf(GREEN" %c "RESET, toupper(casa[i/2][j]));
                    }
                    printf("|");
                }
                printf("\n");
                i++;
                showEvaluationBar(i);
                printf("   ");
                for(int j = 0; j < 8; j++)//escreve uma linha depois de cada conjunto de 8 squares
                {
                    printf("+---");
                }
                printf("+");
                printf("\n");
            }
            if(pointsCapturedWhite+vantagemBranca > pointsCapturedBlack+vantagemPreta)
            {
                printf(" +%.1f", pointsCapturedWhite+vantagemBranca-pointsCapturedBlack-vantagemPreta);
            }
            else if(pointsCapturedBlack+vantagemPreta > pointsCapturedWhite+vantagemBranca)
            {
                printf(" -%.1f.1", pointsCapturedBlack+vantagemPreta-pointsCapturedWhite-vantagemBranca);
            }
            else
            {
                printf(" +0.0");
            }
            printf("     A   B   C   D   E   F   G   H \n");
        }
        else
        {
            printf("        ");
            for(int i = 0; i < 8; i++)
            {
                printf("+---");
            }
            printf("+");
            printf("\n");
            for(int i = 0; i < 16; i++)
            {
                showEvaluationBar(15-i);
                printf("%d. |", i/2+1);
                for(int j = 0; j < 8; j++)
                {
                    if(casa[7-i/2][7-j] == toupper(casa[7-i/2][7-j]))
                    {
                    printf(RED" %c "RESET, casa[7-i/2][7-j]);
                    }
                    else
                    {
                            printf(GREEN" %c "RESET, toupper(casa[7-i/2][7-j]));
                    }
                    printf("|");
                }
                printf("\n");
                i++;
                showEvaluationBar(15-i);
                printf("   ");
                for(int j = 0; j < 8; j++)
                {
                    printf("+---");
                }
                printf("+\n");
            }
            if(pointsCapturedWhite+vantagemBranca > pointsCapturedBlack+vantagemPreta)
            {
                printf(" +%.1f", pointsCapturedWhite+vantagemBranca-pointsCapturedBlack-vantagemPreta);
            }
            else if(pointsCapturedBlack+vantagemPreta > pointsCapturedWhite+vantagemBranca)
            {
                printf(" -%.1f", pointsCapturedBlack+vantagemPreta-pointsCapturedWhite-vantagemBranca);
            }
            else
            {
                printf(" +0.0");
            }
            printf("     H   G   F   E   D   C   B   A\n");
        }
        moves++;
        printf("\n");
    }
}

void squares(char casa[8][8]) //define as squares iniciais
{
    //definir as squares sem peças como espaço para formatar
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            casa[i][j] = ' ';
        }
    }
    //definir as posições iniciais das peças
    //peças brancas
    for(int i = 0; i < 8; i++)//definir todas as squares da linha 2 (casa[6]) como peões
    {
        casa[6][i] = 'P';
    }
    casa[7][1] = 'C';
    casa[7][6] = 'C';
    casa[7][0] = 'T';
    casa[7][7] = 'T';
    casa[7][2] = 'B';
    casa[7][5] = 'B';
    casa[7][3] = 'D';
    casa[7][4] = 'R';
    // peças negras
    for(int i = 0; i < 8; i++)//definir todas as squares da linha 7 (casa[1]) como peões
    {
        casa[1][i] = 'p';
    }
    casa[0][1] = 'c';
    casa[0][6] = 'c';
    casa[0][0] = 't';
    casa[0][7] = 't';
    casa[0][2] = 'b';
    casa[0][5] = 'b';
    casa[0][3] = 'd';
    casa[0][4] = 'r';
    printf("        ");
    for(int i = 0; i < 8; i++)//mostra a linha de cima
    {
        printf("+---"); 
    }
    printf("+");
    printf("\n");
    for(int i = 0; i < 8; i++)//linhas
    {
        (i < 4)?printf("|  | "):printf("|||| ");
        printf("%d. |", 8 - i);
        for(int j = 0; j < 8; j++)//colunas
        {
if(casa[i][j] == toupper(casa[i][j]))
{
	printf(RED" %c "RESET, casa[i][j]);
}
else
{
            printf(GREEN" %c "RESET, toupper(casa[i][j]));
}
printf("|");
       }
        printf("\n");
        (i < 4)?printf("|  | "):printf("|||| ");
        printf("   ");
        for(int i = 0; i < 8; i++)
        {
            printf("+---");
        }
        printf("+");
        printf("\n");
    }
    if(pointsCapturedWhite == pointsCapturedBlack)
    {
        printf(" +0.1");
    }
    else if(pointsCapturedWhite > pointsCapturedBlack)
    {
        printf(" +%d", pointsCapturedWhite-pointsCapturedBlack);
    }
    else
    {
        printf(" -%d", pointsCapturedBlack-pointsCapturedWhite);
    }
    printf("     A   B   C   D   E   F   G   H  \n");//mostrar coordenadas
}

int validateRook(char deColuna, int deLinha, int paraLinha, char paraColuna, char casa[8][8])
{
    if(toupper(casa[8 - deLinha][deColuna - 1]) == 'T')
    {
        if(deColuna == paraColuna || deLinha == paraLinha)
        {
            int deLinhaMatriz = 8 - deLinha;
            if(deLinha == paraLinha)//horizontal
            {
                if(paraColuna > deColuna)//para a direita
                {
                    for(int i = 0; i < paraColuna - deColuna - 1; i++)
                    {
                        if(casa[deLinhaMatriz][deColuna + i] != ' ')
                        {
                            return 1;
                            break;
                        }
                    }
                }
                else//vai para a esquerda
                {
                    for(int i = 0; i < deColuna - paraColuna - 1; i++)
                    {
                        if(casa[deLinhaMatriz][deColuna - i - 2] != ' ')
                        {
                            return 1;
                            break;
                        }
                    }
                    
                }
            }
            else//vertical
            {
                if(paraLinha > deLinha)//para a cima
                {
                    for(int i = 0; i <  paraLinha - deLinha - 1; i++)
                    {
                        if(casa[deLinhaMatriz - i - 1][deColuna - 1] != ' ')
                        {
                            return 1;
                            break;
                        }
                    }
                }
                else//vai para a baiio
                {
                    for(int i = 0; i < deLinha - paraLinha - 1; i++)
                    {
                        if(casa[deLinhaMatriz + i + 1][deColuna - 1] != ' ')
                        {
                            return 1;
                            break;
                        }
                    }
                    
                }
            }
        }
        else
        {
            return 2;
        }
    }
    else
    {
        return 0;
    }
    return 0;
}

int validateKnight(char deColuna, int deLinha, int paraLinha, char paraColuna, char casa[8][8])
{
    if(casa[8 - deLinha][deColuna - 1] == 'C' || casa[8 - deLinha][deColuna - 1] == 'c')
    {
        if(paraLinha == deLinha + 2 && paraColuna == deColuna + 1)//cima direita
        {
            return 0;
        }
        else if(paraLinha == deLinha + 2 && paraColuna == deColuna - 1)//cima esquerda
        {
            return 0;
        }
        else if(paraLinha == deLinha + 1 && paraColuna == deColuna + 2)//cima lado direita
        {
            return 0;
        }
        else if(paraLinha == deLinha + 1 && paraColuna == deColuna - 2)//cima lado esquerda
        {
            return 0;
        }
        else if(paraLinha == deLinha - 1 && paraColuna == deColuna + 2)//baiio lado direita
        {
            return 0;
        }
        else if(paraLinha == deLinha - 1 && paraColuna == deColuna - 2)//baiio lado esquerda
        {
            return 0;
        }
        else if(paraLinha == deLinha - 2 && paraColuna == deColuna + 1)//baiio direita
        {
            return 0;
        }
        else if(paraLinha == deLinha - 2 && paraColuna == deColuna - 1)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 0;
    }
}

int validateSquares(char deColuna, int deLinha, int paraLinha, char paraColuna, char casa[8][8])
{
    if(deLinha == paraLinha && deColuna == paraColuna)
    {
        return 1;
    }
    else if(casa[8-deLinha][deColuna-1] == ' ')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int validateCanibalism(char deColuna, int deLinha, int paraLinha, char paraColuna, char casa[8][8])
{
    if(casa[8 - paraLinha][paraColuna - 1] != ' ')
    {
        if(casa[8 - deLinha][deColuna - 1] != ' ')
        {
            if(toupper(casa[8 - deLinha][deColuna - 1]) == casa[8 - deLinha][deColuna - 1])//peça branca
            {
                if(toupper(casa[8 - paraLinha][paraColuna - 1]) == casa[8 - paraLinha][paraColuna - 1])//a casa de destino também é uma casa com peça branca
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            else//peça preta
            {
                if(toupper(casa[8 - paraLinha][paraColuna - 1]) != casa[8 - paraLinha][paraColuna - 1])//a casa de destino também é uma casa com peça preta
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 0;
    }
}

int validateKing(char deColuna, int deLinha, int paraLinha, char paraColuna, char casa[8][8])
{
    if(toupper(casa[8 - deLinha][deColuna - 1]) == 'R')
    {
        if(deLinha == paraLinha && paraColuna == deColuna + 2 && deLinha == 1 && deColuna == 5)//roque no lado do rei
        {
            if(casa[7][5] == ' ' && casa[7][6] == ' ' && casa[7][7] == 'T')
            {
                return 2;
            }
        }
        else if(deLinha == paraLinha && paraColuna == deColuna - 2 && deLinha == 1 && deColuna == 5)//roque no lado da dama
        {
            if(casa[7][1] == ' ' && casa[7][2] == ' ' &&  casa[7][3] == ' ' && casa[7][0] == 'T')
            {
                return 3;
            }
        }
        else if(deLinha == paraLinha && paraColuna == deColuna + 2 && deLinha == 8 && deColuna == 5)//roque no lado do rei
        {
            if(casa[0][5] == ' ' && casa[0][6] == ' ' && casa[0][7] == 't')
            {
                return 4;
            }
        }
        else if(deLinha == paraLinha && paraColuna == deColuna - 2 && deLinha == 8 && deColuna == 5)//roque no lado da dama
        {
            if(casa[0][1] == ' ' && casa[0][2] == ' ' &&  casa[0][3] == ' ' && casa[0][0] == 't')
            {
                return 5;
            }
        }
        else if(deLinha + 1 == paraLinha && deColuna == paraColuna)//cim
        {
            return 0;
        }
        else if(deLinha - 1 == paraLinha && deColuna == paraColuna)//cim
        {
            return 0;
        }
        else if(deLinha == paraLinha && deColuna + 1== paraColuna)//cim
        {
            return 0;
        }
        else if(deLinha == paraLinha && deColuna - 1 == paraColuna)//cim
        {
            return 0;
        }
        else if(deLinha + 1 == paraLinha && deColuna + 1 == paraColuna)//cim
        {
            return 0;
        }
        else if(deLinha + 1 == paraLinha && deColuna - 1 == paraColuna)//cim
        {
            return 0;
        }
        else if(deLinha - 1 == paraLinha && deColuna + 1 == paraColuna)//cim
        {
            return 0;
        }
        else if(deLinha - 1 == paraLinha && deColuna - 1 == paraColuna)//cim
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 0;
    }
    return 0;
}

int validateBishop(char deColuna, int deLinha, int paraLinha, char paraColuna, char casa[8][8])
{
    if(toupper(casa[8 - deLinha][deColuna - 1]) == 'B')
    {
        if(abs(paraColuna - deColuna) == abs(paraLinha - deLinha))
        {
            int deLinhaMatriz = 8 - deLinha;
            int paraLinhaMatriz = 8 - paraLinha;
            if(paraLinhaMatriz < deLinhaMatriz)//vai para cima
            {
                if(paraColuna > deColuna)//para a direita
                {
                    for(int i = 0; i < paraLinha - deLinha - 1; i++)
                    {
                        if(casa[deLinhaMatriz - i - 1][deColuna + i] != ' ')
                        {
                            return 2;
                            break;
                        }
                    }
                }
                else//vai para a esquerda
                {
                    for(int i = 0; i < paraLinha - deLinha - 1; i++)
                    {
                        if(casa[deLinhaMatriz - i - 1][deColuna - i - 2] != ' ')
                        {
                            return 2;
                            break;
                        }
                    }
                    
                }
            }
            else//vai para baiio
            {
                if(paraColuna > deColuna)//para a direita
                {
                    for(int i = 0; i < deLinha - paraLinha - 1; i++)
                    {
                        if(casa[deLinhaMatriz + i + 1][deColuna + i] != ' ')
                        {
                            return 2;
                            break;
                        }
                    }
                }
                else//vai para a esquerda
                {
                    for(int i = 0; i < deLinha - paraLinha - 1; i++)
                    {
                        if(casa[deLinhaMatriz + i + 1][deColuna - i - 2] != ' ')
                        {
                            return 2;
                            break;
                        }
                    }
                    
                }
            }
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 0;
    }
    return 0;
}

int validateQuennCross(char deColuna, int deLinha, int paraLinha, char paraColuna, char casa[8][8])
{
    if(toupper(casa[8 - deLinha][deColuna - 1]) == 'D')
    {
        if(deColuna == paraColuna || deLinha == paraLinha)
        {
            int deLinhaMatriz = 8 - deLinha;
            if(deLinha == paraLinha)//horizontal
            {
                if(paraColuna > deColuna)//para a direita
                {
                    for(int i = 0; i < paraColuna - deColuna - 1; i++)
                    {
                        if(casa[deLinhaMatriz][deColuna + i] != ' ')
                        {
                            return 1;
                            break;
                        }
                    }
                }
                else//vai para a esquerda
                {
                    for(int i = 0; i < deColuna - paraColuna - 1; i++)
                    {
                        if(casa[deLinhaMatriz][deColuna - i - 2] != ' ')
                        {
                            return 1;
                            break;
                        }
                    }
                    
                }
            }
            else//vertical
            {
                if(paraLinha > deLinha)//para a cima
                {
                    for(int i = 0; i <  paraLinha - deLinha - 1; i++)
                    {
                        if(casa[deLinhaMatriz - i - 1][deColuna - 1] != ' ')
                        {
                            return 1;
                            break;
                        }
                    }
                }
                else//vai para a baiio
                {
                    for(int i = 0; i < deLinha - paraLinha - 1; i++)
                    {
                        if(casa[deLinhaMatriz + i + 1][deColuna - 1] != ' ')
                        {
                            return 1;
                            break;
                        }
                    }
                    
                }
            }
        }
        else
        {
            return 2;
        }
    }
    else
    {
        return 0;
    }
    return 0;
}

int validateQueenDiagonals(char deColuna, int deLinha, int paraLinha, char paraColuna, char casa[8][8])
{
    if(toupper(casa[8 - deLinha][deColuna - 1]) == 'D')
    {
        if(abs(paraColuna - deColuna) == abs(paraLinha - deLinha))
        {
            int deLinhaMatriz = 8 - deLinha;
            int paraLinhaMatriz = 8 - paraLinha;
            if(paraLinhaMatriz < deLinhaMatriz)//vai para cima
            {
                if(paraColuna > deColuna)//para a direita
                {
                    for(int i = 0; i < paraLinha - deLinha - 1; i++)
                    {
                        if(casa[deLinhaMatriz - i - 1][deColuna + i] != ' ')
                        {
                            return 2;
                            break;
                        }
                    }
                }
                else//vai para a esquerda
                {
                    for(int i = 0; i < paraLinha - deLinha - 1; i++)
                    {
                        if(casa[deLinhaMatriz - i - 1][deColuna - i - 2] != ' ')
                        {
                            return 2;
                            break;
                        }
                    }
                    
                }
            }
            else//vai para baiio
            {
                if(paraColuna > deColuna)//para a direita
                {
                    for(int i = 0; i < deLinha - paraLinha - 1; i++)
                    {
                        if(casa[deLinhaMatriz + i + 1][deColuna + i] != ' ')
                        {
                            return 2;
                            break;
                        }
                    }
                }
                else//vai para a esquerda
                {
                    for(int i = 0; i < deLinha - paraLinha - 1; i++)
                    {
                        if(casa[deLinhaMatriz + i + 1][deColuna - i - 2] != ' ')
                        {
                            return 2;
                            break;
                        }
                    }
                    
                }
            }
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 0;
    }
    return 0;
}

int validatePawn(char deColuna, int deLinha, int paraLinha, char paraColuna, char casa[8][8])
{
    if(toupper(casa[8 - deLinha][deColuna - 1]) == 'P')
    {
        if(toupper(casa[8 - deLinha][deColuna - 1]) == casa[8 - deLinha][deColuna - 1])//peão branco
        {
            if(paraLinha > deLinha)
            {
                if(deColuna == paraColuna)
                {
                    if(deLinha == 2)//está na casa inicial
                    {
                        if(paraLinha - deLinha < 3 && paraLinha == 4)
                        {
                            if(casa[7 - deLinha][deColuna - 1] == ' ' && casa[6 - deLinha][deColuna - 1] == ' ')
                            {
                                return 0;
                            }
                            else{
                                return 2;
                            }
                        }
                        else if(paraLinha - deLinha < 3 && paraLinha == 3)
                        {
                            if(casa[7 - deLinha][deColuna - 1] == ' ')
                            {
                                return 0;
                            }
                            else
                            {
                                return 1;
                            }
                        }
                        else
                        {
                            return 1;
                        }
                    }
                    else if(deLinha == 7 && paraLinha == 8 && casa[8 - paraLinha][paraColuna - 1] == ' ')
                    {
                        return 3;
                    }
                    else
                    {
                        if(paraLinha - deLinha == 1)
                        {
                            if(casa[7 - deLinha][deColuna - 1] == ' ')
                            {
                                return 0;
                            }
                            else
                            {
                                return 2;
                            }
                        }
                        else
                        {
                            return 1;
                        }
                    }
                }
                else if(paraColuna == deColuna + 1 && paraLinha == deLinha + 1 && casa[8 - paraLinha][paraColuna - 1] != ' ' && 7 == deLinha && paraLinha == 8)
                {
                    return 3;
                }
                else if(paraColuna == deColuna - 1 && paraLinha == deLinha + 1  && casa[8 - paraLinha][paraColuna - 1] != ' ' && 7 == deLinha && paraLinha == 8)
                {
                    return 3;
                }
                else if(paraColuna == deColuna + 1 && paraLinha == deLinha + 1 && casa[8 - paraLinha][paraColuna - 1] != ' ')
                {
                    return 0;
                }
                else if(paraColuna == deColuna - 1 && paraLinha == deLinha + 1  && casa[8 - paraLinha][paraColuna - 1] != ' ')
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
            }
            else
            {
                return 1;
            }
        }
        else
        {
            if(paraLinha < deLinha)
            {
                if(deColuna == paraColuna)
                {
                    if(deLinha == 7 && paraLinha == 5)//está na casa inicial
                    {
                        if(casa[9 - deLinha][deColuna - 1] == ' ' && casa[10 - deLinha][deColuna - 1] == ' ')
                        {
                            return 0;
                        }
                        else{
                            return 2;
                        }
                    }
                    else if(deLinha == 2 && paraLinha == 1 && casa[8 - paraLinha][paraColuna - 1] == ' ')
                    {
                        return 3;
                    }
                    else
                    {
                        if(deLinha - paraLinha == 1)
                        {
                             if(casa[9 - deLinha][deColuna - 1] == ' ')
                            {
                                return 0;
                            }
                            else
                            {
                                return 2;
                            }
                        }
                        else
                        {
                            return 1;
                        }
                    }
                }
                else if(paraColuna == deColuna + 1 && paraLinha == deLinha - 1 && casa[8 - paraLinha][paraColuna - 1] != ' ' && 2 == deLinha && paraLinha == 1)
                {
                    return 3;
                }
                else if(paraColuna == deColuna - 1 && paraLinha == deLinha - 1 && casa[8 - paraLinha][paraColuna - 1] != ' ' && 2 == deLinha && paraLinha == 1)
                {
                    return 3;
                }
                else if(paraColuna == deColuna + 1 && paraLinha == deLinha - 1 && casa[8 - paraLinha][paraColuna - 1] != ' ')
                {
                    return 0;
                }
                else if(paraColuna == deColuna - 1 && paraLinha == deLinha - 1 && casa[8 - paraLinha][paraColuna - 1] != ' ')
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
            }
            else
            {
                return 1;
            }
        }
    }
    return 0;
}

int validatePlayer(char casa[8][8], int deLinha, int deColuna)
{
    if((moves % 2 == 0 && casa[8-deLinha][deColuna-1] == toupper(casa[8-deLinha][deColuna-1])) || 
    (moves % 2 == 1 && casa[8-deLinha][deColuna-1] != toupper(casa[8-deLinha][deColuna-1])))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int addCapturesPoints(int paraLinha, int paraColuna, char casa[8][8])
{
    if(moves % 2 == 0)
    {
        switch(casa[8-paraLinha][paraColuna-1])
        {
            case 'p':
                pointsCapturedWhite++;
                break;
            case 'c':
                pointsCapturedWhite+=3;
                break;
            case 'b':
                pointsCapturedWhite+=3;
                break;
            case 't':
                pointsCapturedWhite+=5;
                break;
            case 'd':
                pointsCapturedWhite+=9;
                break;
        }
    }
    else if(moves % 2 == 1)
    {
        switch(casa[8-paraLinha][paraColuna-1])
        {
            case 'P':
                pointsCapturedBlack++;
                break;
            case 'C':
                pointsCapturedBlack+=3;
                break;
            case 'B':
                pointsCapturedBlack+=3;
                break;
            case 'T':
                pointsCapturedBlack+=5;
                break;
            case 'D':
                pointsCapturedBlack+=9;
                break;
        }
    }
    return 0;
}

int validateEndOfGame(int paraLinha, int paraColuna, char casa[8][8])
{  
    if(toupper(casa[8-paraLinha][paraColuna-1]) == 'R')
    {
        if(moves % 2 == 1)
        {
            return 1;
        }
        else
        {
            return 2;
        }
    }
    else
    {
        return 0;
    }
}

int defineCapturedPieces(int paraLinha, int paraColuna, char casa[8][8])
{
    if(casa[8-paraLinha][paraColuna-1] != ' ')
    {
        if(moves % 2 == 0)
        {
           pecasCapturadasBrancas[numeroPecasCapturadasBrancas] = casa[8-paraLinha][paraColuna-1]; 
           numeroPecasCapturadasBrancas++;
        }
        else
        {
           pecasCapturadasPretas[numeroPecasCapturadasPretas] = casa[8-paraLinha][paraColuna-1];
           numeroPecasCapturadasPretas++;
        }
    }
    return 0;
}

void showEvaluationBar(int i)
{
    if((pointsCapturedWhite+vantagemBranca == pointsCapturedBlack+vantagemPreta)
     || (vantagemBranca < 1 && vantagemPreta < 1)
     || (abs(vantagemBranca - vantagemPreta) < 1))
    {
        if(i < 8)
        {
            printf("|  | ");
        }
        else
        {
            printf("|||| ");
        }
    }
    else if(pointsCapturedWhite+vantagemBranca > pointsCapturedBlack+vantagemPreta)
    {
        if(i < 6/(pointsCapturedWhite+vantagemBranca-pointsCapturedBlack-vantagemPreta))
        {
            printf("|  | ");
        }
        else
        {
            printf("|||| ");
        }
    }
    else
    {
        if(i < 16 - 6/(pointsCapturedBlack+vantagemPreta-pointsCapturedWhite-vantagemBranca))
        {
            printf("|  | ");
        }
        else
        {
            printf("|||| ");
        }
    }
}

void engine(char casa[8][8])
{
    if(moves % 2 == 0) //foi a jogada das bracas
    {
        vantagemBranca = 0;
        vantagemPreta = 0;
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if(casa[i][j] != toupper(casa[i][j]))//a casa tem uma peça preta
                {
                    engineBlackKing(casa, i, j);
                    engineBlackKnight(casa, i, j);
                    engineBlackBishop(casa, i, j);
                    engineBlackRook(casa, i, j);
                    engineBlackPawn(casa, i, j);
                }
                if(casa[i][j] == 'P')
                {
                    vantagemBranca += vantPeao[i][j]; 
                }
                if(casa[i][j] == 'p')
                {
                    vantagemPreta += vantPeao[7-i][j]; 
                }
                if(casa[i][j] == 'C')
                {
                    vantagemBranca += vantCavalo[i][j]; 
                }
                if(casa[i][j] == 'c')
                {
                    vantagemPreta += vantCavalo[7-i][j]; 
                }
                if(casa[i][j] == 'B')
                {
                    vantagemBranca += vantBispo[i][j];
                }
                if(casa[i][j] == 'b')
                {
                    vantagemPreta += vantBispo[7-i][j];
                }
                if(casa[i][j] == 'T')
                {
                    vantagemBranca += vantTorre[i][j];
                }
                if(casa[i][j] == 't')
                {
                    vantagemPreta += vantTorre[7-i][j];
                }
                if(casa[i][j] == 'D')
                {
                    vantagemBranca += vantDama[i][j];
                }
                if(casa[i][j] == 'd')
                {
                    vantagemPreta += vantDama[7-i][j];
                }
                if(casa[i][j] == 'R')
                {
                    vantagemBranca += vantRei[i][j];
                }
                if(casa[i][j] == 'r')
                {
                    vantagemPreta += vantRei[7-i][j];
                }
            }
        }
    }
    else
    {
        vantagemPreta = 0;
        vantagemBranca = 0;
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if(casa[i][j] == toupper(casa[i][j]))//a casa tem uma peça preta
                {
                    engineWhiteKing(casa, i, j);
                    engineWhiteKnight(casa, i, j);
                    engineWhiteBishop(casa, i, j);
                    engineWhiteRook(casa, i, j);
                    engineWhitePawn(casa, i, j);
                }
                if(casa[i][j] == 'P')
                {
                    vantagemBranca += vantPeao[i][j]; 
                }
                if(casa[i][j] == 'p')
                {
                    vantagemPreta += vantPeao[7-i][j];
                }
                if(casa[i][j] == 'C')
                {
                    vantagemBranca += vantCavalo[i][j]; 
                }
                if(casa[i][j] == 'c')
                {
                    vantagemPreta += vantCavalo[7-i][j]; 
                }
                if(casa[i][j] == 'B')
                {
                    vantagemBranca += vantBispo[i][j];
                }
                if(casa[i][j] == 'b')
                {
                    vantagemPreta += vantBispo[7-i][j];
                }
                if(casa[i][j] == 'T')
                {
                    vantagemBranca += vantTorre[i][j];
                }
                if(casa[i][j] == 't')
                {
                    vantagemPreta += vantTorre[7-i][j];
                }
                if(casa[i][j] == 'D')
                {
                    vantagemBranca += vantDama[i][j];
                }
                if(casa[i][j] == 'd')
                {
                    vantagemPreta += vantDama[7-i][j];
                }
                if(casa[i][j] == 'R')
                {
                    vantagemBranca += vantRei[i][j];
                }
                if(casa[i][j] == 'r')
                {
                    vantagemPreta += vantRei[7-i][j];
                }
            }
        }
    }
}

void engineBlackKing(char casa[8][8], int i, int j)
{
    if(casa[i][j] == 'r')
    {
        for(int a = -1; a < 2; a++)
        {
            for(int b = -1; b < 2; b++)
            {
                if(casa[i+a][j+b] == toupper(casa[i+a][j+b]) || casa[i+a][j+a] == ' ')
                {
                    switch(casa[i+a][j+b])
                    {
                        case 'P':
                            if(vantagemPreta < 1)//verifica se a vantagem anterior era menor
                            {
                                vantagemPreta = 1;//se a vantegm for menor esta passa a ser um
                            }
                            break;
                        case 'C':
                            if(vantagemPreta < 3)//verifica se a vantagem anterior era menor
                            {
                                vantagemPreta = 3;//se a vantegm for menor esta passa a ser um
                            }
                            break;
                        case 'B':
                            if(vantagemPreta < 3)//verifica se a vantagem anterior era menor
                            {
                                vantagemPreta = 3;//se a vantegm for menor esta passa a ser um
                            }
                            break;
                        case 'T':
                            if(vantagemPreta < 5)//verifica se a vantagem anterior era menor
                            {
                                vantagemPreta = 5;//se a vantegm for menor esta passa a ser um
                            }
                            break;
                        case 'D':
                            if(vantagemPreta < 9)//verifica se a vantagem anterior era menor
                            {
                                vantagemPreta = 9;//se a vantegm for menor esta passa a ser um
                            }
                            break;
                        default:
                            vantagemPreta = vantagemPreta;
                            break;
                    }
                } 
            }
        }
    }
}

void engineBlackKnight(char casa[8][8], int i, int j)
{
    if(casa[i][j] == 'c')
    {
        for(int a = -2; a < 3; a++)
        {
            if(a == 0)
            {
                continue;
            }
            else
            {
                for(int b = -2; b < 3; b++)
                {
                    if((b == 0)||(abs(b) == 2 && abs(a) == 2)||(abs(b) == 1 && abs(a) == 1))
                    {
                        continue;
                    }
                    else
                    {
                        switch(casa[i+a][j+b])
                        {
                            case 'P':
                                if(vantagemPreta < 1)//verifica se a vantagem anterior era menor
                                {
                                    vantagemPreta = 1;//se a vantegm for menor esta passa a ser um
                                }
                                break;
                            case 'C':
                                if(vantagemPreta < 3)//verifica se a vantagem anterior era menor
                                {
                                    vantagemPreta = 3;//se a vantegm for menor esta passa a ser um
                                }
                                break;
                            case 'B':
                                if(vantagemPreta < 3)//verifica se a vantagem anterior era menor
                                {
                                    vantagemPreta = 3;//se a vantegm for menor esta passa a ser um
                                }
                                break;
                            case 'T':
                                if(vantagemPreta < 5)//verifica se a vantagem anterior era menor
                                {
                                    vantagemPreta = 5;//se a vantegm for menor esta passa a ser um
                                }
                                break;
                            case 'D':
                                if(vantagemPreta < 9)//verifica se a vantagem anterior era menor
                                {
                                    vantagemPreta = 9;//se a vantegm for menor esta passa a ser um
                                }
                                break;
                            default:
                                vantagemPreta = vantagemPreta;
                                break;             
                        }
                    }
                }
            }
        }
    }
}

void engineBlackBishop(char casa[8][8], int i, int j)
{
    if(casa[i][j] == 'b' || casa[i][j] == 'd')
    {
        for(int c = -1; c < 2; c+=2)
        {
            for(int d = -1; d < 2; d+=2)
            {
                int squaresAVerificarVertical = 0;
                int squaresAVerificarHorizontal  = 0;
                if(c == 1)
                {
                    squaresAVerificarVertical = 7-i;
                }
                else
                {
                    squaresAVerificarVertical = i;
                }
                if(d == 1)
                {
                    squaresAVerificarHorizontal = 7-j;
                }
                else
                {
                    squaresAVerificarHorizontal = j;
                }
                if(casa[i+c][j+d] == toupper(casa[i+c][j+d]) && casa[i+c][j+d] != ' ')
                {
                    switch(casa[i+c][j+d])
                    {
                        case 'P':
                            if(vantagemPreta < 1)//verifica se a vantagem anterior era menor
                            {
                                vantagemPreta = 1;//se a vantegm for menor esta passa a ser um
                            }
                            break;
                        case 'C':
                            if(vantagemPreta < 3)//verifica se a vantagem anterior era menor
                            {
                                vantagemPreta = 3;//se a vantegm for menor esta passa a ser um
                            }
                            break;
                        case 'B':
                            if(vantagemPreta < 3)//verifica se a vantagem anterior era menor
                            {
                                vantagemPreta = 3;//se a vantegm for menor esta passa a ser um
                            }
                            break;
                        case 'T':
                            if(vantagemPreta < 5)//verifica se a vantagem anterior era menor
                            {
                                vantagemPreta = 5;//se a vantegm for menor esta passa a ser um
                            }
                            break;
                        case 'D':
                            if(vantagemPreta < 9)//verifica se a vantagem anterior era menor
                            {
                                vantagemPreta = 9;//se a vantegm for menor esta passa a ser um
                            }
                            break;
                        default:
                            vantagemPreta = vantagemPreta;
                            break;
                    }
                }
                else
                {
                    for(int a = 2; casa[i+c*(a-1)][j+d*(a-1)] == ' ' && a >=2 && a <= squaresAVerificarHorizontal && a <= squaresAVerificarVertical; a++)
                    {
                        if(casa[i+c*a][j+d*a] != ' ')//diagonal esquerda e cima
                        {
                            if(casa[i+c*a][j+d*a] == toupper(casa[i+c*a][j+d*a]))
                            {
                                switch(casa[i+c*a][j+d*a])
                                {
                                    case 'P':
                                        if(vantagemPreta < 1)//verifica se a vantagem anterior era menor
                                        {
                                            vantagemPreta = 1;//se a vantegm for menor esta passa a ser um
                                        }
                                        break;
                                    case 'C':
                                        if(vantagemPreta < 3)//verifica se a vantagem anterior era menor
                                        {
                                            vantagemPreta = 3;//se a vantegm for menor esta passa a ser um
                                        }
                                        break;
                                    case 'B':
                                        if(vantagemPreta < 3)//verifica se a vantagem anterior era menor
                                        {
                                            vantagemPreta = 3;//se a vantegm for menor esta passa a ser um
                                        }
                                        break;
                                    case 'T':
                                        if(vantagemPreta < 5)//verifica se a vantagem anterior era menor
                                        {
                                            vantagemPreta = 5;//se a vantegm for menor esta passa a ser um
                                        }
                                        break;
                                    case 'D':
                                        if(vantagemPreta < 9)//verworwoifica se a vantagem anterior era menor
                                        {
                                            vantagemPreta = 9;//se a vantegm for menor esta passa a ser um
                                        }
                                        break;
                                    default:
                                        vantagemPreta = vantagemPreta;
                                        break;
                                }
                            }
                            else
                            {
                                break;
                            }
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
            }
        }
    }    
}

void engineBlackRook(char casa[8][8], int i, int j)
{
    if(casa[i][j] == 't' || casa[i][j] == 'd')
    {
        for(int z = -1; z < 2; z+=2)
        {
            if(casa[i+z][j] == toupper(casa[i+z][j]) && casa[i+z][j] != ' ')
            {
                switch(casa[i+z][j])
                {
                    case 'P':
                        if(vantagemPreta < 1)
                        {
                            vantagemPreta = 1;
                        }
                        break;
                    case 'C':
                        if(vantagemPreta < 3)
                        {
                            vantagemPreta = 3;
                        }
                        break;
                    case 'B':
                        if(vantagemPreta < 3)
                        {
                            vantagemPreta = 3;
                        }
                        break;
                    case 'T':
                        if(vantagemPreta < 5)
                        {
                            vantagemPreta = 5;
                        }
                        break;
                    case 'D':
                        if(vantagemPreta < 9)
                        {
                            vantagemPreta = 9;
                        }
                        break;
                    default:
                        vantagemPreta = vantagemPreta;
                        break;
                }
            }
            for(int a = 2; casa[i+z*(a-1)][j] == ' ' && a <= 7; a++)
            {
                if(casa[i+z*a][j] != ' ')
                {
                    if(casa[i+z*a][j] == toupper(casa[i+z*a][j]))
                    {
                        switch(casa[i+z*a][j])
                        {
                            case 'P':
                                if(vantagemPreta < 1)
                                {
                                    vantagemPreta = 1;
                                }
                                break;
                            case 'C':
                                if(vantagemPreta < 3)
                                {
                                    vantagemPreta = 3;
                                }
                                break;
                            case 'B':
                                if(vantagemPreta < 3)
                                {
                                    vantagemPreta = 3;
                                }
                                break;
                            case 'T':
                                if(vantagemPreta < 5)
                                {
                                    vantagemPreta = 5;
                                }
                                break;
                            case 'D':
                                if(vantagemPreta < 9)
                                {
                                    vantagemPreta = 9;
                                }
                                break;
                            default:
                                vantagemPreta = vantagemPreta;
                                break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    continue;
                }
            }
        }

        for(int z = -1; z < 2; z+=2)
        {
            if(casa[i][j+z] == toupper(casa[i][j+z]) && casa[i][j+z] != ' ')
            {
                switch(casa[i][j+z])
                {
                    case 'P':
                        if(vantagemPreta < 1)
                        {
                            vantagemPreta = 1;
                        }
                        break;
                    case 'C':
                        if(vantagemPreta < 3)
                        {
                            vantagemPreta = 3;
                        }
                        break;
                    case 'B':
                        if(vantagemPreta < 3)
                        {
                            vantagemPreta = 3;
                        }
                        break;
                    case 'T':
                        if(vantagemPreta < 5)
                        {
                            vantagemPreta = 5;
                        }
                        break;
                    case 'D':
                        if(vantagemPreta < 9)
                        {
                            vantagemPreta = 9;
                        }
                        break;
                    default:
                        vantagemPreta = vantagemPreta;
                        break;
                }
            }
            for(int a = 2; casa[i][j+z*(a-1)] == ' ' && a <= 7; a++)
            {
                if(casa[i][j+z*a] != ' ')
                {
                    if(casa[i][j+z*a] == toupper(casa[i][j+z*a]))
                    {
                        switch(casa[i][j+z*a])
                        {
                            case 'P':
                                if(vantagemPreta < 1)
                                {
                                    vantagemPreta = 1;
                                }
                                break;
                            case 'C':
                                if(vantagemPreta < 3)
                                {
                                    vantagemPreta = 3;
                                }
                                break;
                            case 'B':
                                if(vantagemPreta < 3)
                                {
                                    vantagemPreta = 3;
                                }
                                break;
                            case 'T':
                                if(vantagemPreta < 5)
                                {
                                    vantagemPreta = 5;
                                }
                                break;
                            case 'D':
                                if(vantagemPreta < 9)
                                {
                                    vantagemPreta = 9;
                                }
                                break;
                            default:
                                vantagemPreta = vantagemPreta;
                                break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    continue;
                }
            }
        }
    }
}

void engineBlackPawn(char casa[8][8], int i, int j)
{
    if(casa[i][j] == 'p')
    {
        for(int a = -1; a < 2; a += 2)
        {
            if(casa[i+1][j+a*1] == toupper(casa[i+1][j+a*1]) && casa[i+1][j+a*1]  != ' ')
            {
                switch(casa[i+1][j+1*a])
                {
                    case 'P':
                        if(vantagemPreta < 1)
                        {
                            vantagemPreta = 1;
                        }
                        break;
                    case 'C':
                        if(vantagemPreta < 3)
                        {
                            vantagemPreta = 3;
                        }
                        break;
                    case 'B':
                        if(vantagemPreta < 3)
                        {
                            vantagemPreta = 3;
                        }
                        break;
                    case 'T':
                        if(vantagemPreta < 5)
                        {
                            vantagemPreta = 5;
                        }
                        break;
                    case 'D':
                        if(vantagemPreta < 9)
                        {
                            vantagemPreta = 9;
                        }
                        break;
                    default:
                        vantagemPreta = vantagemPreta;
                        break;
                }
            }
        }
    }
}

void engineWhiteKing(char casa[8][8], int i, int j)
{
    if(casa[i][j] == 'R')
    {
        for(int a = -1; a < 2; a++)
        {
            for(int b = -1; b < 2; b++)
            {
                if(casa[i+a][j+b] != toupper(casa[i+a][j+b]))
                {
                    switch(casa[i+a][j+b])
                    {
                        case 'p':
                            if(vantagemBranca < 1)//verifica se a vantagem anterior era menor
                            {
                                vantagemBranca = 1;//se a vantegm for menor esta passa a ser um
                            }
                            break;
                        case 'c':
                            if(vantagemBranca < 3)//verifica se a vantagem anterior era menor
                            {
                                vantagemBranca = 3;//se a vantegm for menor esta passa a ser um
                            }
                            break;
                        case 'b':
                            if(vantagemBranca < 3)//verifica se a vantagem anterior era menor
                            {
                                vantagemBranca = 3;//se a vantegm for menor esta passa a ser um
                            }
                            break;
                        case 't':
                            if(vantagemBranca < 5)//verifica se a vantagem anterior era menor
                            {
                                vantagemBranca = 5;//se a vantegm for menor esta passa a ser um
                            }
                            break;
                        case 'd':
                            if(vantagemBranca < 9)//verifica se a vantagem anterior era menor
                            {
                                vantagemBranca = 9;//se a vantegm for menor esta passa a ser um
                            }
                            break;
                        default:
                            vantagemBranca = vantagemBranca;
                            break;
                    }
                } 
            }
        }
    }
}

void engineWhiteKnight(char casa[8][8], int i, int j)
{
    if(casa[i][j] == 'C')
    {
        for(int a = -2; a < 3; a++)
        {
            if(a == 0)
            {
                continue;
            }
            else
            {
                for(int b = -2; b < 3; b++)
                {
                    if((b == 0)||(abs(b) == 2 && abs(a) == 2)||(abs(b) == 1 && abs(a) == 1))
                    {
                        continue;
                    }
                    else
                    {
                        switch(casa[i+a][j+b])
                        {
                            case 'p':
                                if(vantagemBranca < 1)//verifica se a vantagem anterior era menor
                                {
                                    vantagemBranca = 1;//se a vantegm for menor esta passa a ser um
                                }
                                break;
                            case 'c':
                                if(vantagemBranca < 3)//verifica se a vantagem anterior era menor
                                {
                                    vantagemBranca = 3;//se a vantegm for menor esta passa a ser um
                                }
                                break;
                            case 'b':
                                if(vantagemBranca < 3)//verifica se a vantagem anterior era menor
                                {
                                    vantagemBranca = 3;//se a vantegm for menor esta passa a ser um
                                }
                                break;
                            case 't':
                                if(vantagemBranca < 5)//verifica se a vantagem anterior era menor
                                  {
                                    vantagemBranca = 5;//se a vantegm for menor esta passa a ser um
                                }
                                break;
                            case 'd':
                                if(vantagemBranca < 9)//verifica se a vantagem anterior era menor
                                {
                                    vantagemBranca = 9;//se a vantegm for menor esta passa a ser um
                                }
                                break;
                            default:
                                vantagemBranca = vantagemBranca;
                                break;
                        }
                    }
                }
            }
        }
    }
}

void engineWhiteBishop(char casa[8][8], int i, int j)
{
    if(casa[i][j] == 'B' || casa[i][j] == 'D')
    {
        for(int c = -1; c < 2; c+=2)
        {
            for(int d = -1; d < 2; d+=2)
            {
                int squaresAVerificarVertical = 0;
                int squaresAVerificarHorizontal  = 0;
                if(c == 1)
                {
                    squaresAVerificarVertical = 7-i;
                }
                else
                {
                    squaresAVerificarVertical = i;
                }
                if(d == 1)
                {
                    squaresAVerificarHorizontal = 7-j;
                }
                else
                {
                    squaresAVerificarHorizontal = j;
                }
                if(casa[i+c][j+d] != toupper(casa[i+c][j+d]) && casa[i+c][j+d] != ' ')
                {
                    switch(casa[i+c][j+d])
                    {
                        case 'p':
                            if(vantagemBranca < 1)//verifica se a vantagem anterior era menor
                            {
                                vantagemBranca = 1;//se a vantegm for menor esta passa a ser um
                            }
                            break;
                        case 'c':
                            if(vantagemBranca < 3)//verifica se a vantagem anterior era menor
                            {
                                vantagemBranca = 3;//se a vantegm for menor esta passa a ser um
                            }
                            break;
                        case 'b':
                            if(vantagemBranca < 3)//verifica se a vantagem anterior era menor
                            {
                                vantagemBranca = 3;//se a vantegm for menor esta passa a ser um
                            }
                            break;
                        case 't':
                            if(vantagemBranca < 5)//verifica se a vantagem anterior era menor
                            {
                                vantagemBranca = 5;//se a vantegm for menor esta passa a ser um
                            }
                            break;
                        case 'd':
                            if(vantagemBranca < 9)//verifica se a vantagem anterior era menor
                            {
                                vantagemBranca = 9;//se a vantegm for menor esta passa a ser um
                            }
                            break;
                        default:
                            vantagemBranca = vantagemBranca;
                            break;
                    }
                }
                else
                {
                    for(int a = 2; casa[i+c*(a-1)][j+d*(a-1)] == ' ' && a >=2 && a <= squaresAVerificarHorizontal && a <= squaresAVerificarVertical; a++)
                    {
                        if(casa[i+c*a][j+d*a] != ' ')//diagonal esquerda e cima
                        {
                            if(casa[i+c*a][j+d*a] != toupper(casa[i+c*a][j+d*a]))
                            {
                                switch(casa[i+c*a][j+d*a])
                                {
                                    case 'p':
                                        if(vantagemBranca < 1)//verifica se a vantagem anterior era menor
                                        {
                                            vantagemBranca = 1;//se a vantegm for menor esta passa a ser um
                                        }
                                        break;
                                    case 'c':
                                        if(vantagemBranca < 3)//verifica se a vantagem anterior era menor
                                        {
                                            vantagemBranca = 3;//se a vantegm for menor esta passa a ser um
                                        }
                                        break;
                                    case 'b':
                                        if(vantagemBranca < 3)//verifica se a vantagem anterior era menor
                                        {
                                            vantagemBranca = 3;//se a vantegm for menor esta passa a ser um
                                        }
                                        break;
                                    case 't':
                                        if(vantagemBranca < 5)//verifica se a vantagem anterior era menor
                                        {
                                            vantagemBranca = 5;//se a vantegm for menor esta passa a ser um
                                        }
                                        break;
                                    case 'd':
                                        if(vantagemBranca < 9)//verifica se a vantagem anterior era menor
                                        {
                                            vantagemBranca = 9;//se a vantegm for menor esta passa a ser um
                                        }
                                        break;
                                    default:
                                        vantagemBranca = vantagemBranca;
                                        break;
                                }
                            }
                            else
                            {
                                break;
                            }
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
            }
        }
    } 
}

void engineWhiteRook(char casa[8][8], int i, int j)
{
    if(casa[i][j] == 'T' || casa[i][j] == 'D')
    {
        for(int z = -1; z < 2; z+=2)
        {
            if(casa[i+z][j] != toupper(casa[i+z][j]) && casa[i+z][j] != ' ')
            {
                switch(casa[i+z][j])
                {
                    case 'p':
                        if(vantagemBranca < 1)
                        {
                            vantagemBranca = 1;
                        }
                        break;
                    case 'c':
                        if(vantagemBranca < 3)
                        {
                            vantagemBranca = 3;
                        }
                        break;
                    case 'b':
                        if(vantagemBranca < 3)
                        {
                            vantagemBranca = 3;
                        }
                        break;
                    case 't':
                        if(vantagemBranca < 5)
                        {
                            vantagemBranca = 5;
                        }
                        break;
                    case 'd':
                        if(vantagemBranca < 9)
                        {
                            vantagemBranca = 9;
                        }
                        break;
                    default:
                        vantagemBranca = vantagemBranca;
                        break;
                }
            }
            for(int a = 2; casa[i+z*(a-1)][j] == ' ' && a <= 7; a++)
            {
                if(casa[i+z*a][j] != ' ')
                {
                    if(casa[i+z*a][j] != toupper(casa[i+z*a][j]))
                    {
                        switch(casa[i+z*a][j])
                        {
                            case 'p':
                                if(vantagemBranca < 1)
                                {
                                    vantagemBranca = 1;
                                }                           
                                break;
                            case 'c':
                                if(vantagemBranca < 3)
                                {
                                    vantagemBranca = 3;
                                }
                                break;
                            case 'b':
                                if(vantagemBranca < 3)
                                {
                                    vantagemBranca = 3;
                                }
                                break;
                            case 't':
                                if(vantagemBranca < 5)
                                {
                                    vantagemBranca = 5;
                                }
                                break;
                            case 'd':
                                if(vantagemBranca < 9)
                                {
                                    vantagemBranca = 9;
                                }
                                break;
                            default:
                                vantagemBranca = vantagemBranca;
                                break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    continue;
                }
            }
        }

        for(int z = -1; z < 2; z+=2)
        {
            if(casa[i][j+z] != toupper(casa[i][j+z]) && casa[i][j+z] != ' ')
            {
                switch(casa[i][j+z])
                {
                    case 'p':
                        if(vantagemBranca < 1)
                        {
                            vantagemBranca = 1;
                        }
                        break;
                    case 'c':
                        if(vantagemBranca < 3)
                        {
                            vantagemBranca = 3;
                        }
                        break;
                    case 'b':
                        if(vantagemBranca < 3)
                        {
                            vantagemBranca = 3;
                        }
                        break;
                    case 't':
                        if(vantagemBranca < 5)
                        {
                            vantagemBranca = 5;
                        }
                        break;
                    case 'd':
                        if(vantagemBranca < 9)
                        {
                            vantagemBranca = 9;
                        }
                        break;
                    default:
                        vantagemBranca = vantagemBranca;
                        break;
                }
            }
            for(int a = 2; casa[i][j+z*(a-1)] == ' ' && a <= 7; a++)
            {
                if(casa[i][j+z*a] != ' ')
                {
                    if(casa[i][j+z*a] == toupper(casa[i][j+z*a]))
                    {
                        switch(casa[i][j+z*a])
                        {
                            case 'p':
                                if(vantagemBranca < 1)
                                {
                                    vantagemBranca = 1;
                                }
                                break;
                            case 'c':
                                if(vantagemBranca < 3)
                                {
                                    vantagemBranca = 3;
                                }
                                break;
                            case 'b':
                                if(vantagemBranca < 3)
                                {
                                    vantagemBranca = 3;
                                }
                                break;
                            case 't':
                                if(vantagemBranca < 5)
                                {
                                    vantagemBranca = 5;
                                }
                                break;
                            case 'd':
                                if(vantagemBranca < 9)
                                {
                                    vantagemBranca = 9;
                                }
                                break;
                            default:
                                vantagemBranca = vantagemBranca;
                                break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    continue;
                }
            }
        }
    }
}

void engineWhitePawn(char casa[8][8], int i, int j)
{
    if(casa[i][j] == 'P')
    {
        for(int a = -1; a < 2; a += 2)
        {
            if(casa[i-1][j+a*1] != toupper(casa[i-1][j+a*1]) && casa[i-1][j+a*1] != ' ')
            {
                switch(casa[i-1][j+1*a])
                {
                    case 'p':
                        if(vantagemBranca < 1)
                        {
                            vantagemBranca = 1;
                        }
                        break;
                    case 'c':
                        if(vantagemBranca < 3)
                        {
                            vantagemBranca = 3;
                        }
                        break;
                    case 'b':
                        if(vantagemBranca < 3)
                        {
                            vantagemBranca = 3;
                        }
                        break;
                    case 't':
                        if(vantagemBranca < 5)
                        {
                            vantagemBranca = 5;
                        }
                        break;
                    case 'd':
                        if(vantagemBranca < 9)
                        {
                            vantagemBranca = 9;
                        }
                        break;
                    default:
                        vantagemBranca = vantagemBranca;
                        break;
                }
            }
        }
    }
}

void legal(char casa[8][8])
{
    if(moves % 2 == 0)
    {
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if(casa[i][j] != toupper(casa[i][j]))//a casa tem uma peça preta
                {
                    legalReiPreto(casa, i, j);
                    legalCavaloPreto(casa, i, j);
                    legalBispoPreto(casa, i, j);
                    legalTorrePreta(casa, i, j);
                    legalPeaoPreto(casa, i, j);
                }
            }
        }
    }
    else
    {
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if(casa[i][j] == toupper(casa[i][j]))//a casa tem uma peça preta
                {
                    legalReiBranco(casa, i, j);
                    legalCavaloBranco(casa, i, j);
                    legalBispoBranco(casa, i, j);
                    legalTorreBranco(casa, i, j);
                    legalPeaoBranco(casa, i, j);
                }
            }
        }
    }
}

void legalReiPreto(char casa[8][8], int i, int j)
{
    if(casa[i][j] == 'r')
    {
        for(int a = -1; a < 2; a++)
        {
            for(int b = -1; b < 2; b++)
            {
                if(casa[i+a][j+b] == toupper(casa[i+a][j+b]) || casa[i+a][j+a] == ' ')
                {
                    if(casa[i+a][j+b] == 'R')
                    {
                        jogadaIlegal = 1;
                    }
                } 
            }
        }
    }
}

void legalCavaloPreto(char casa[8][8], int i, int j)
{
    if(casa[i][j] == 'c')
    {
        for(int a = -2; a < 3; a++)
        {
            if(a == 0)
            {
                continue;
            }
            else
            {
                for(int b = -2; b < 3; b++)
                {
                    if((b == 0)||(abs(b) == 2 && abs(a) == 2)||(abs(b) == 1 && abs(a) == 1))
                    {
                        continue;
                    }
                    else
                    {
                        if(casa[i+a][j+b] == 'R')
                        {
                            jogadaIlegal = 1;
                        }
                    }
                }
            }
        }
    }
}

void legalBispoPreto(char casa[8][8], int i, int j)
{
    if(casa[i][j] == 'b' || casa[i][j] == 'd')
    {
        for(int c = -1; c < 2; c+=2)
        {
            for(int d = -1; d < 2; d+=2)
            {
                int squaresAVerificarVertical = 0;
                int squaresAVerificarHorizontal  = 0;
                if(c == 1)
                {
                    squaresAVerificarVertical = 7-i;
                }
                else
                {
                    squaresAVerificarVertical = i;
                }
                if(d == 1)
                {
                    squaresAVerificarHorizontal = 7-j;
                }
                else
                {
                    squaresAVerificarHorizontal = j;
                }
                if(casa[i+c][j+d] == toupper(casa[i+c][j+d]) && casa[i+c][j+d] != ' ')
                {
                    if(casa[i+c][j+d] == 'R')
                    {
                        jogadaIlegal = 1;
                    }
                }
                else
                {
                    for(int a = 2; casa[i+c*(a-1)][j+d*(a-1)] == ' ' && a >=2 && a <= squaresAVerificarHorizontal && a <= squaresAVerificarVertical; a++)
                    {
                        if(casa[i+c*a][j+d*a] != ' ')//diagonal esquerda e cima
                        {
                            if(casa[i+c*a][j+d*a] == toupper(casa[i+c*a][j+d*a]))
                            {
                                if(casa[i+c*a][j+d*a] == 'R')
                                {
                                    jogadaIlegal = 1;
                                }
                            }
                            else
                            {
                                break;
                            }
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
            }
        }
    }    
}

void legalTorrePreta(char casa[8][8], int i, int j)
{
    if(casa[i][j] == 't' || casa[i][j] == 'd')
    {
        for(int z = -1; z < 2; z+=2)
        {
            if(casa[i+z][j] == toupper(casa[i+z][j]) && casa[i+z][j] != ' ')
            {
                if(casa[i+z][j] == 'R')
                {
                    jogadaIlegal = 1;
                }
            }
            for(int a = 2; casa[i+z*(a-1)][j] == ' ' && a <= 7; a++)
            {
                if(casa[i+z*a][j] != ' ')
                {
                    if(casa[i+z*a][j] == toupper(casa[i+z*a][j]))
                    {
                        if(casa[i+z*a][j] == 'R')
                        {
                            jogadaIlegal = 1;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    continue;
                }
            }
        }

        for(int z = -1; z < 2; z+=2)
        {
            if(casa[i][j+z] == toupper(casa[i][j+z]) && casa[i][j+z] != ' ')
            {
                if(casa[i][j+z] == 'R')
                {
                    jogadaIlegal = 1;
                }
            }
            for(int a = 2; casa[i][j+z*(a-1)] == ' ' && a <= 7; a++)
            {
                if(casa[i][j+z*a] != ' ')
                {
                    if(casa[i][j+z*a] == toupper(casa[i][j+z*a]))
                    {
                        if(casa[i][j+z*a] == 'R')
                        {
                            jogadaIlegal = 1;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    continue;
                }
            }
        }
    }
}

void legalPeaoPreto(char casa[8][8], int i, int j)
{
    if(casa[i][j] == 'p')
    {
        for(int a = -1; a < 2; a += 2)
        {
            if(casa[i+1][j+a*1] == toupper(casa[i+1][j+a*1]) && casa[i+1][j+a*1]  != ' ')
            {
                if(casa[i+1][j+1*a] == 'R')
                {
                    jogadaIlegal = 1;
                }
            }
        }
    }
}

void legalReiBranco(char casa[8][8], int i, int j)
{
    if(casa[i][j] == 'R')
    {
        for(int a = -1; a < 2; a++)
        {
            for(int b = -1; b < 2; b++)
            {
                if(casa[i+a][j+b] != toupper(casa[i+a][j+b]))
                {
                    if(casa[i+a][j+b] == 'r')
                    {
                        jogadaIlegal = 1;
                    }
                } 
            }
        }
    }
}

void legalCavaloBranco(char casa[8][8], int i, int j)
{
    if(casa[i][j] == 'C')
    {
        for(int a = -2; a < 3; a++)
        {
            if(a == 0)
            {
                continue;
            }
            else
            {
                for(int b = -2; b < 3; b++)
                {
                    if((b == 0)||(abs(b) == 2 && abs(a) == 2)||(abs(b) == 1 && abs(a) == 1))
                    {
                        continue;
                    }
                    else
                    {
                        if(casa[i+a][j+b] == 'r')
                        {
                            jogadaIlegal = 1;
                        }
                    }
                }
            }
        }
    }
}

void legalBispoBranco(char casa[8][8], int i, int j)
{
    if(casa[i][j] == 'B' || casa[i][j] == 'D')
    {
        for(int c = -1; c < 2; c+=2)
        {
            for(int d = -1; d < 2; d+=2)
            {
                int squaresAVerificarVertical = 0;
                int squaresAVerificarHorizontal  = 0;
                if(c == 1)
                {
                    squaresAVerificarVertical = 7-i;
                }
                else
                {
                    squaresAVerificarVertical = i;
                }
                if(d == 1)
                {
                    squaresAVerificarHorizontal = 7-j;
                }
                else
                {
                    squaresAVerificarHorizontal = j;
                }
                if(casa[i+c][j+d] != toupper(casa[i+c][j+d]) && casa[i+c][j+d] != ' ')
                {
                    if(casa[i+c][j+d] == 'r')
                    {
                        jogadaIlegal = 1;
                    }
                }
                else
                {
                    for(int a = 2; casa[i+c*(a-1)][j+d*(a-1)] == ' ' && a >=2 && a <= squaresAVerificarHorizontal && a <= squaresAVerificarVertical; a++)
                    {
                        if(casa[i+c*a][j+d*a] != ' ')//diagonal esquerda e cima
                        {
                            if(casa[i+c*a][j+d*a] != toupper(casa[i+c*a][j+d*a]))
                            {
                                if(casa[i+c*a][j+d*a] == 'r')
                                {
                                    jogadaIlegal = 1;
                                }
                            }
                            else
                            {
                                break;
                            }
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
            }
        }
    }   
}

void legalTorreBranco(char casa[8][8], int i, int j)
{
    if(casa[i][j] == 'T' || casa[i][j] == 'D')
    {
        for(int z = -1; z < 2; z+=2)
        {
            if(casa[i+z][j] != toupper(casa[i+z][j]) && casa[i+z][j] != ' ')
            {
                if(casa[i+z][j] == 'r')
                {
                    jogadaIlegal = 1;
                }
            }
            for(int a = 2; casa[i+z*(a-1)][j] == ' ' && a <= 7; a++)
            {
                if(casa[i+z*a][j] != ' ')
                {
                    if(casa[i+z*a][j] != toupper(casa[i+z*a][j]))
                    {
                        if(casa[i+z*a][j] == 'r')
                        {
                            jogadaIlegal = 1;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    continue;
                }
            }
        }

        for(int z = -1; z < 2; z+=2)
        {
            if(casa[i][j+z] != toupper(casa[i][j+z]) && casa[i][j+z] != ' ')
            {
                if(casa[i][j+z] == 'r')
                {
                    jogadaIlegal = 1;
                }
            }
            for(int a = 2; casa[i][j+z*(a-1)] == ' ' && a <= 7; a++)
            {
                if(casa[i][j+z*a] != ' ')
                {
                    if(casa[i][j+z*a] == toupper(casa[i][j+z*a]))
                    {
                        if(casa[i][j+z*a] == 'r')
                        {
                            jogadaIlegal = 1;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    continue;
                }
            }
        }
    }
}

void legalPeaoBranco(char casa[8][8], int i, int j)
{
    if(casa[i][j] == 'P')
    {
        for(int a = -1; a < 2; a += 2)
        {
            if(casa[i-1][j+a*1] != toupper(casa[i-1][j+a*1]) && casa[i-1][j+a*1] != ' ')
            {
                if(casa[i-1][j+1*a] == 'r')
                {
                    jogadaIlegal = 1;
                }
            }
        }
    }
}
