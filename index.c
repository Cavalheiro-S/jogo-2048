#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define ESCAPE_KEY 224
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_LEFT 75
#define ARROW_RIGHT 77
#define ESC_KEY 27

struct POSITION
{
    int line;
    int column;
};

void printBoard(int board[4][4])
{
    system("cls");
    for (int line = 0; line < 4; line++)
    {
        for (int column = 0; column < 4; column++)
        {
            printf("%d", board[line][column]);
            printf("\t");
        }
        printf("\n");
    }
}

struct POSITION getRandomPosition()
{
    struct POSITION position;
    position.line = rand() % 4;
    position.column = rand() % 4;
    return position;
}

void setRandomNumberPosition(int board[4][4])
{
    struct POSITION pos1 = getRandomPosition();
    struct POSITION pos2 = getRandomPosition();

    board[pos1.line][pos1.column] = 2;
    board[pos2.line][pos2.column] = 2;
}

void initialScreen(int board[4][4])
{
    printf("\n\nBEM VINDO AO JOGO 2048\n\n");
    setRandomNumberPosition(board);
    printBoard(board);
    printf("Aperta uma tecla para iniciar o jogo\n");
}

// Os números vão se mover uma linha a cima
// Números que estão na primeira linha não fazem nada
// Caso haja algum número na linha que o número se movimentar então somam-se os valores e os coloca na ultima casa disponivel.
void moveNumbersUp(int board[4][4])
{
    for (int line = 1; line < 4; line++)
    {
        for (int column = 0; column < 4; column++)
        {
            // Verifica se o número é diferente de 0
            if (board[line][column] != 0)
            {
                int number = board[line][column];
                int lineToMove = line - 1;
                while (lineToMove >= 0)
                {
                    if (board[lineToMove][column] == 0)
                    {
                        board[lineToMove][column] = number;
                        board[lineToMove + 1][column] = 0;
                        lineToMove--;
                    }
                    else if (board[lineToMove][column] == number)
                    {
                        board[lineToMove][column] = number * 2;
                        board[lineToMove + 1][column] = 0;
                        lineToMove = -1;
                    }
                    else
                    {
                        lineToMove = -1;
                    }
                }
            }
        }
    }
}

void moveNumbersDown(int board[4][4])
{
    for (int line = 2; line >= 0; line--)
    {
        for (int column = 0; column < 4; column++)
        {
            if (board[line][column] != 0)
            {
                int number = board[line][column];
                int lineToMove = line + 1;
                while (lineToMove <= 3)
                {
                    if (board[lineToMove][column] == 0)
                    {
                        board[lineToMove][column] = number;
                        board[lineToMove - 1][column] = 0;
                        lineToMove++;
                    }
                    else if (board[lineToMove][column] == number)
                    {
                        board[lineToMove][column] = number * 2;
                        board[lineToMove - 1][column] = 0;
                        lineToMove = 4;
                    }
                    else
                    {
                        lineToMove = 4;
                    }
                }
            }
        }
    }
}

void moveNumbersRight(int board[4][4])
{
    for (int line = 1; line < 4; line++)
    {
        for (int column = 0; column < 4; column++)
        {
            // Verifica se o número é diferente de 0
            if (board[line][column] != 0)
            {
                int number = board[line][column];
                int columnToMove = column + 1;
                while (columnToMove < 4)
                {
                    // Se a coluna que o número vai se mover for igual a 0
                    if (board[line][columnToMove] == 0)
                    {
                        board[line][columnToMove] = number;

                        board[line][columnToMove - 1] = 0;
                        columnToMove++;
                    }
                    else if (board[line][columnToMove] == number)
                    {
                        board[line][columnToMove] = number * 2;
                        board[line][columnToMove - 1] = 0;
                        columnToMove = 4;
                    }
                    else
                    {
                        columnToMove = 4;
                    }
                }
            }
        }
    }
}

void moveNumbersLeft(int board[4][4])
{
    for (int line = 1; line < 4; line++)
    {
        for (int column = 0; column < 4; column++)
        {
            // Verifica se o número é diferente de 0
            if (board[line][column] != 0)
            {
                int number = board[line][column];
                int columnToMove = column - 1;
                while (columnToMove >= 0)
                {
                    if (board[line][columnToMove] == 0)
                    {
                        board[line][columnToMove] = number;
                        board[line][columnToMove + 1] = 0;
                        columnToMove--;
                    }
                    else if (board[line][columnToMove] == number)
                    {
                        board[line][columnToMove] = number * 2;
                        board[line][columnToMove + 1] = 0;
                        columnToMove = -1;
                    }
                    else
                    {
                        columnToMove = -1;
                    }
                }
            }
        }
    }
}

void verifyKeyPressed(int board[4][4])
{
    int pressedKey;
    while (pressedKey != ESC_KEY)
    {
        printf("Use as setas do seu teclado para jogar ... (ESC para sair)\n");
        pressedKey = getch();

        if (pressedKey == ESCAPE_KEY)
        {
            pressedKey = getch();

            switch (pressedKey)
            {
            case ARROW_UP:
                moveNumbersUp(board);
                printBoard(board);
                break;
            case ARROW_DOWN:
                moveNumbersDown(board);
                printBoard(board);
                break;
            case ARROW_LEFT:
                moveNumbersLeft(board);
                printBoard(board);
                break;
            case ARROW_RIGHT:
                moveNumbersRight(board);
                printBoard(board);
                break;
            default:
                printf("Outra tecla especial pressionada.\n");
            }
        }
        else
        {
            printf("Tecla pressionada: %c\n", pressedKey);
        }
    }
}

int main(void)
{
    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios

    // Fazer o board do jogo
    int board[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}};

    initialScreen(board);
    verifyKeyPressed(board);
    return 0;
}
