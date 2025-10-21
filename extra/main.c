#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_SIZE 3
#define FILE_NAME "/out/game_history.txt"

typedef struct
{
    char *name;
    char symbol;
} Player;

typedef struct
{
    char board[BOARD_SIZE][BOARD_SIZE];
} Game;

typedef struct
{
    int row;
    int col;
} Move;

void initializeBoard(Game *const game)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            game->board[i][j] = ' ';
        }
    }
}

void printBoard(const Game *const game)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            printf(" %c ", game->board[i][j]);
            if (j < BOARD_SIZE - 1)
            {
                printf("|");
            }
        }
        printf("\n");
        if (i < BOARD_SIZE - 1)
        {
            printf("---+---+---\n");
        }
    }
}

void saveBoard(const Game *const game, FILE *const file, const Move *const lastMove, const char lastSymbol)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (lastMove != NULL && i == lastMove->row && j == lastMove->col)
            {
                fprintf(file, "[%c]", lastSymbol);
            }
            else
            {
                fprintf(file, " %c ", game->board[i][j]);
            }
            if (j < BOARD_SIZE - 1)
            {
                fprintf(file, "|");
            }
        }
        fprintf(file, "\n");
        if (i < BOARD_SIZE - 1)
        {
            fprintf(file, "---+---+---\n");
        }
    }
    fprintf(file, "\n");
}

int isBoardFull(const Game *const game)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (game->board[i][j] == ' ')
            {
                return 0;
            }
        }
    }
    return 1;
}

int isGameOver(const Game *const game, const char symbol)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (game->board[i][0] == symbol && game->board[i][1] == symbol && game->board[i][2] == symbol)
        {
            return 1;
        }
    }

    for (int j = 0; j < BOARD_SIZE; j++)
    {
        if (game->board[0][j] == symbol && game->board[1][j] == symbol && game->board[2][j] == symbol)
        {
            return 1;
        }
    }

    if (game->board[0][0] == symbol && game->board[1][1] == symbol && game->board[2][2] == symbol)
    {
        return 1;
    }
    if (game->board[0][2] == symbol && game->board[1][1] == symbol && game->board[2][0] == symbol)
    {
        return 1;
    }

    return 0;
}

int isMoveValid(const Game *const game, const int row, const int col)
{
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && game->board[row][col] == ' ';
}

void getPlayerMove(Game *const game, int *const row, int *const col)
{
    while (1)
    {
        printf("Enter row and column (0-2): ");
        int inputCount = scanf("%d %d", row, col);

        if (inputCount == 2 && isMoveValid(game, *row, *col))
        {
            break;
        }
        else
        {
            if (inputCount != 2)
            {
                while (getchar() != '\n')
                    ;
            }
            printf("Invalid move. The cell is already occupied or out of bounds. Try again.\n");
        }
    }
}

void makeMove(Game *const game, const int row, const int col, const char symbol)
{
    game->board[row][col] = symbol;
}

int minimax(Game *const game, const int depth, const int isMax, const char playerSymbol, const char computerSymbol)
{
    if (isGameOver(game, computerSymbol))
        return 10 - depth;

    if (isGameOver(game, playerSymbol))
        return depth - 10;

    if (isBoardFull(game))
        return 0;

    if (isMax)
    {
        int bestScore = -1000;
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                if (game->board[i][j] == ' ')
                {
                    game->board[i][j] = computerSymbol;
                    int score = minimax(game, depth + 1, 0, playerSymbol, computerSymbol);
                    bestScore = (score > bestScore) ? score : bestScore;
                    game->board[i][j] = ' ';
                }
            }
        }
        return bestScore;
    }
    else
    {
        int bestScore = 1000;
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                if (game->board[i][j] == ' ')
                {
                    game->board[i][j] = playerSymbol;
                    int score = minimax(game, depth + 1, 1, playerSymbol, computerSymbol);
                    bestScore = (score < bestScore) ? score : bestScore;
                    game->board[i][j] = ' ';
                }
            }
        }
        return bestScore;
    }
}

void computerMove(Game *const game, const char playerSymbol, const char computerSymbol, Move *bestMove)
{
    int bestScore = -1000;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (game->board[i][j] == ' ')
            {
                game->board[i][j] = computerSymbol;
                int moveScore = minimax(game, 0, 0, playerSymbol, computerSymbol);
                game->board[i][j] = ' ';
                if (moveScore > bestScore)
                {
                    bestScore = moveScore;
                    bestMove->row = i;
                    bestMove->col = j;
                }
            }
        }
    }

    makeMove(game, bestMove->row, bestMove->col, computerSymbol);
}

void playGame(Player *const player, Player *const computer, FILE *const file)
{
    Game game;
    initializeBoard(&game);

    fprintf(file, "Last Tic Tac Toe Game History\n\n");

    while (!isGameOver(&game, player->symbol) && !isGameOver(&game, computer->symbol) && !isBoardFull(&game))
    {
        int row, col;
        getPlayerMove(&game, &row, &col);
        makeMove(&game, row, col, player->symbol);
        fprintf(file, "%s's move:\n", player->name);
        Move lastMove = {row, col};
        saveBoard(&game, file, &lastMove, player->symbol);
        printBoard(&game);

        if (isGameOver(&game, player->symbol))
        {
            printf("Congratulations! You won!\n");
            fprintf(file, "Congratulations! %s won!\n", player->name);
            return;
        }

        if (isBoardFull(&game))
        {
            printf("It's a draw!\n");
            fprintf(file, "It's a draw!\n");
            return;
        }

        printf("Computer's move:\n");
        Move bestMove;
        computerMove(&game, player->symbol, computer->symbol, &bestMove);
        fprintf(file, "Computer's move:\n");
        saveBoard(&game, file, &bestMove, computer->symbol);
        printBoard(&game);

        if (isGameOver(&game, computer->symbol))
        {
            printf("Sorry, you lost!\n");
            fprintf(file, "Sorry, %s lost!\n", player->name);
            return;
        }

        if (isBoardFull(&game))
        {
            printf("It's a draw!\n");
            fprintf(file, "It's a draw!\n");
            return;
        }
    }
}

void showHistory(const char *const filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Failed to open history file.\n");
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF)
    {
        putchar(ch);
    }

    fclose(file);
}

void initializePlayer(Player *player, const char *name, char symbol)
{
    player->name = (char *)malloc((strlen(name) + 1) * sizeof(char));
    if (player->name == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strcpy(player->name, name);
    player->symbol = symbol;
}

int main()
{
    Player player;
    Player computer;

    char playerName[50];
    printf("Enter your name: ");
    scanf("%s", playerName);
    initializePlayer(&player, playerName, 'X');
    initializePlayer(&computer, "Computer", 'O');

    printf("Welcome, %s! Let's play Tic-Tac-Toe!\n", player.name);
    printf("You are X and the computer is O.\n");

    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL)
    {
        printf("Failed to open file for writing.\n");
        free(player.name);
        return 1;
    }

    playGame(&player, &computer, file);

    fclose(file);

    char choice;
    printf("Do you want to see the game history? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y')
    {
        showHistory(FILE_NAME);
    }

    free(player.name);
    free(computer.name);
    return 0;
}