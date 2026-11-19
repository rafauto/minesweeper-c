# 💣 Minesweeper Path (C)

![CI](https://github.com/rafauto/minesweeper-c/actions/workflows/ci.yml/badge.svg)
![Language](https://img.shields.io/badge/language-C99-blue)
![License](https://img.shields.io/badge/license-MIT-green)
![Status](https://img.shields.io/badge/status-academic%20project-lightgrey)

A terminal game written in C, built for an elective programming course at university.
Cross a 15×15 minefield from the left edge to the right edge without stepping on a hidden bomb.

## Why I built this

This was a course assignment to practice the fundamentals of structured programming in C:
2D arrays, loops, conditionals, user input and pseudo-random number generation.
I keep it here as a record of where my programming journey started.

## How to play

1. Choose a difficulty level: `1` (10% of cells are bombs), `2` (20%) or `3` (30%).
2. You start at a random row on the left edge of the board, marked `[X]`.
3. Every turn, choose your next move:
   - `1` – move right
   - `2` – move diagonally up-right
   - `3` – move diagonally down-right
4. Reach the last column to win. Step on a bomb and the board is revealed (`[*]`) — game over.

The game's on-screen text is in Portuguese, as it was delivered for the course.

```text
[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
[X][X][X][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
...
Escolha a direcao da proxima jogada - digite 1 para andar para direita, ...
```

## How it works

```mermaid
flowchart LR
    A[Player picks level] --> B[Place bombs at random cells]
    B --> C[Random start row, column 0]
    C --> D{Current cell is a bomb?}
    D -- yes --> E[Reveal board: game over]
    D -- no --> F[Mark path and print board]
    F --> G[Player picks direction 1/2/3]
    G --> H{Reached last column?}
    H -- no --> D
    H -- yes --> I[You win]
```

The board is a `15×15` integer matrix: `0` = empty, `1` = bomb, `-1` = visited path.
Everything lives in a single `main()` function, as required by the course scope.

## Tech stack

| Item | Choice |
| --- | --- |
| Language | C (C99) |
| Compiler | GCC or Clang |
| Build | Make |
| CI | GitHub Actions (build with GCC and Clang + scripted smoke test) |

## Getting started

Requirements: a C compiler (`gcc` or `clang`) and `make`.

```bash
git clone https://github.com/rafauto/minesweeper-c.git
cd minesweeper-c
make
./minesweeper
```

Without `make`:

```bash
gcc -std=c99 -Wall -Wextra -o minesweeper src/campo_minado.c
```

## Project structure

```text
minesweeper-c/
├── src/campo_minado.c        # the whole game
├── Makefile
├── .github/workflows/ci.yml  # build + smoke test
├── LICENSE
└── README.md
```

## Known limitations

Kept as originally submitted. Things I would improve today:

- Random positions use `rand() % 14`, so the last row and column never get bombs.
- Diagonal moves are not bounded, so moving off the top or bottom edge reads outside the array.
- An invalid difficulty level prints an error but the game keeps going.
- Bombs can be placed on the same cell twice, so the real count can be lower than the target.
- No input validation for non-numeric input.

## License

MIT — see [LICENSE](LICENSE).

## Author

**Rafaela Uto** — [GitHub](https://github.com/rafauto)
