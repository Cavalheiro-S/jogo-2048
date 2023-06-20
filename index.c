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

struct PLAYER
{
    char name[50];
    int points;
};

struct NODE
{
    struct PLAYER player;
    struct NODE *next;
};

struct POSITION
{
    int line;
    int column;
};

void printPlayers(struct NODE *head)
{
    struct NODE *current = head;
    printf("\nJogadores:\n");
    while (current != NULL)
    {
        printf("%s\t%d\n", current->player.name, current->player.points);
        current = current->next;
    }
}

void saveScore(struct NODE *head, char name[50], int score)
{
    struct NODE *current = head;
    struct NODE *previous = NULL;
    struct NODE *newNode = (struct NODE *)malloc(sizeof(struct NODE));
    newNode->player.points = score;
    strcpy(newNode->player.name, name);
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        while (current != NULL && current->player.points > score)
        {
            previous = current;
            current = current->next;
        }
        if (previous == NULL)
        {
            newNode->next = head;
            head = newNode;
        }
        else
        {
            previous->next = newNode;
            newNode->next = current;
        }
    }
}

int getPoints(int board[4][4])
{
    int points = 0;
    int maxNumber = 0;
    int sum = 0;
    int maxSum = 0;
    int maxLine = 0;
    int maxColumn = 0;

    // Verifica o maior número
    for (int line = 0; line < 4; line++)
    {
        for (int column = 0; column < 4; column++)
        {
            if (board[line][column] > maxNumber)
            {
                maxNumber = board[line][column];
            }
        }
    }

    // Verifica a soma dos números
    for (int line = 0; line < 4; line++)
    {
        sum = 0;
        for (int column = 0; column < 4; column++)
        {
            sum += board[line][column];
        }
        if (sum > maxSum)
        {
            maxSum = sum;
            maxLine = line;
        }
    }

    // Verifica a soma das colunas
    for (int column = 0; column < 4; column++)
    {
        sum = 0;
        for (int line = 0; line < 4; line++)
        {
            sum += board[line][column];
        }
        if (sum > maxSum)
        {
            maxSum = sum;
            maxColumn = column;
        }
    }

    points = maxNumber + maxSum + maxLine + maxColumn;
    return points;
}

void printBoard(int board[4][4])
{
    system("cls");
    int points = getPoints(board);
    printf("Pontos: %d\n", points);
    for (int line = 0; line < 4; line++)
    {
        for (int column = 0; column < 4; column++)
        {
            int currentNumber = board[line][column];
            if (currentNumber == 0)
                printf(".");
            else
                printf("%d", currentNumber);
            printf("\t");
        }
        printf("\n");
    }
}

void verifyIsWinner(int board[4][4])
{
    for (int line = 0; line < 4; line++)
    {
        for (int column = 0; column < 4; column++)
        {
            if (board[line][column] == 2048)
            {
                printf("Parabens voce ganhou o jogo\n");
                exit(0);
            }
        }
    }
}

int verifyHasMoves(int board[4][4])
{
    int hasMoves = 0;
    for (int line = 0; line < 4; line++)
    {
        for (int column = 0; column < 4; column++)
        {
            if (board[line][column] == 0)
            {
                hasMoves = 1;
            }
            if (line > 0 && board[line][column] == board[line - 1][column])
            {
                hasMoves = 1;
            }
            if (line < 3 && board[line][column] == board[line + 1][column])
            {
                hasMoves = 1;
            }
            if (column > 0 && board[line][column] == board[line][column - 1])
            {
                hasMoves = 1;
            }
            if (column < 3 && board[line][column] == board[line][column + 1])
            {
                hasMoves = 1;
            }
        }
    }

    return hasMoves;
}

struct POSITION getRandomPosition()
{
    struct POSITION position;
    position.line = rand() % 4;
    position.column = rand() % 4;
    return position;
}

void placeInitialRandomNumber(int board[4][4])
{
    struct POSITION pos1 = getRandomPosition();
    struct POSITION pos2 = getRandomPosition();

    while (pos1.column == pos2.column && pos1.line == pos2.line)
    {
        pos1 = getRandomPosition();
        pos2 = getRandomPosition();
    }

    board[pos1.line][pos1.column] = 2;
    board[pos2.line][pos2.column] = 2;
}

void placeOneRandomNumber(int board[4][4])
{
    struct POSITION pos = getRandomPosition();

    while (board[pos.line][pos.column] != 0)
        pos = getRandomPosition();

    board[pos.line][pos.column] = 2;
}

void initialScreen(int board[4][4])
{
    printf("\n\nBEM VINDO AO JOGO 2048\n\n");
    placeInitialRandomNumber(board);
    printBoard(board);
    printf("Aperta uma tecla para iniciar o jogo\n");
}

void moveNumbersUp(int board[4][4])
{
    for (int line = 0; line < 4; line++)
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
    for (int line = 3; line >= 0; line--)
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
    for (int line = 0; line < 4; line++)
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
    for (int line = 0; line < 4; line++)
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

void verifyKeyPressed(int board[4][4], struct NODE *head)
{
    int pressedKey;
    int hasMoves = 1;
    char playAgain;
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
                break;
            case ARROW_DOWN:
                moveNumbersDown(board);
                break;
            case ARROW_LEFT:
                moveNumbersLeft(board);
                break;
            case ARROW_RIGHT:
                moveNumbersRight(board);
                break;
            default:
                break;
            }
        }
        placeOneRandomNumber(board);
        verifyIsWinner(board);
        printBoard(board);
        hasMoves = verifyHasMoves(board);
        if (hasMoves == 0)
        {
            printf("Voce perdeu!\n");
            break;
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

    struct NODE *head = (struct NODE *)malloc(sizeof(struct NODE));
    initialScreen(board);
    verifyKeyPressed(board, head);
    return 0;
}
