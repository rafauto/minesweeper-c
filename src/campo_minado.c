/*
 * Minesweeper Path - cross a 15x15 minefield from the left edge to the right edge.
 * Originally written for a university elective course; refactored afterwards.
 * On-screen text is kept in Portuguese, as in the original assignment.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 15

enum Cell { EMPTY = 0, BOMB = 1, VISITED = -1 };

enum Move { MOVE_RIGHT = 1, MOVE_UP_RIGHT = 2, MOVE_DOWN_RIGHT = 3 };

/* Reads an integer in [min, max], asking again until the input is valid.
 * Returns -1 if the input stream ends. */
static int read_int_in_range(const char *prompt, int min, int max)
{
    int value;
    int status;

    for (;;) {
        printf("%s", prompt);
        status = scanf("%d", &value);
        if (status == EOF) {
            return -1;
        }
        if (status == 1 && value >= min && value <= max) {
            return value;
        }
        /* Discard the rest of the invalid line. */
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        printf("Entrada invalida! Digite um numero entre %d e %d.\n", min, max);
    }
}

/* Places exactly `count` bombs on distinct cells, never on the start cell. */
static void place_bombs(int board[SIZE][SIZE], int count, int start_row)
{
    int placed = 0;

    while (placed < count) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;

        if (board[row][col] == BOMB || (row == start_row && col == 0)) {
            continue;
        }
        board[row][col] = BOMB;
        placed++;
    }
}

static void print_board(int board[SIZE][SIZE], int reveal_bombs)
{
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            if (board[row][col] == VISITED) {
                printf("[X]");
            } else if (reveal_bombs && board[row][col] == BOMB) {
                printf("[*]");
            } else {
                printf("[ ]");
            }
        }
        printf("\n");
    }
}

/* Usage: minesweeper [seed]  - an optional seed makes the game reproducible. */
int main(int argc, char *argv[])
{
    int board[SIZE][SIZE] = {{0}};
    const int total_cells = SIZE * SIZE;

    unsigned int seed = (argc > 1) ? (unsigned int)strtoul(argv[1], NULL, 10)
                                   : (unsigned int)time(NULL);
    srand(seed);

    int level = read_int_in_range("Digite o nivel de dificuldade desejado (entre 1 e 3): ", 1, 3);
    if (level < 0) {
        return 0;
    }
    int bomb_count = total_cells * level / 10; /* 10%, 20% or 30% of the board */

    int row = rand() % SIZE;
    int col = 0;
    place_bombs(board, bomb_count, row);
    board[row][col] = VISITED;

    for (;;) {
        print_board(board, 0);

        if (col == SIZE - 1) {
            printf("Voce ganhou o jogo!\n");
            return 0;
        }

        int move = read_int_in_range(
            "Escolha a direcao da proxima jogada - digite 1 para andar para direita, "
            "2 para andar em diagonal para cima e 3 para andar em diagonal para baixo: ",
            MOVE_RIGHT, MOVE_DOWN_RIGHT);
        if (move < 0) {
            return 0;
        }

        int next_row = row;
        if (move == MOVE_UP_RIGHT) {
            next_row--;
        } else if (move == MOVE_DOWN_RIGHT) {
            next_row++;
        }
        if (next_row < 0 || next_row >= SIZE) {
            printf("Movimento invalido: voce sairia do tabuleiro. Tente outra direcao.\n");
            continue;
        }

        row = next_row;
        col++;

        if (board[row][col] == BOMB) {
            print_board(board, 1);
            printf("BOMBA! Perdeu o jogo\n");
            return 0;
        }
        board[row][col] = VISITED;
    }
}
