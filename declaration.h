#ifndef DECLARATION_H
#define DECLARATION_H

#include <stdbool.h>

#define boardMargin 50
#define tileSize 50
#define boardSize 9

extern const int winners[8][3];
extern const int dangerPositionComputedMove[9];
extern const int corners[4];
extern const int edges[4];
extern const char dangerPositions[9][9];

extern int state;
extern char computationDetails[1000];
extern char superBoard[boardSize][boardSize];
extern char baseBoard[boardSize];
extern char turn;
extern int computedMove;

extern Font prstart;

void drawTiles(void);
void drawComputationDetails(void);
void drawMenu(void);

void resetGame(void);
void initializeGame(void);
void cleanupGame(void);

void checkMenuInput(void);
void checkGameInput(char player);
void moveOpponent(void);

int evaluateTopMove(int computedMoves[]);
int computeMove(char board[]);

bool checkWinner(const char board[], char player);
bool checkWinningMoves(char board[], char player);
bool checkDangerPosition(const char board[]);
bool checkCentre(const char board[]);
bool checkCorner(const char board[]);
bool checkEdge(const char board[]);

#endif