#include <vector>
#include <string>
#ifndef DECLARATION_H
#define DECLARATION_H

constexpr int boardMargin = 50;
constexpr int tileSize = 50;
constexpr int boardSize = 9;

constexpr int winners[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}},
              dangerPositionComputedMove[9] = {1, 3, 0, 3, 6, 8, 8, 6, 8},
              corners[4] = {0, 2, 6, 8},
              edges[4] = {1, 3, 5, 7};
constexpr char dangerPositions[9][9] = {
    {'x', ' ', ' ', ' ', 'o', ' ', ' ', ' ', 'x'},
    {' ', ' ', ' ', 'x', ' ', 'o', ' ', 'x', ' '},
    {' ', ' ', ' ', 'x', 'x', 'o', ' ', ' ', ' '},
    {'x', ' ', ' ', ' ', ' ', 'o', 'x', ' ', ' '},
    {' ', ' ', ' ', ' ', 'x', 'o', ' ', ' ', 'x'},
    {' ', ' ', ' ', ' ', ' ', 'o', 'x', 'x', ' '},
    {' ', ' ', ' ', ' ', ' ', 'o', 'x', ' ', 'x'},
    {'x', ' ', ' ', ' ', ' ', 'o', ' ', ' ', 'x'},
    {' ', ' ', ' ', 'x', ' ', 'o', ' ', ' ', 'x'}
};

extern bool win;
extern std::string computationDetails;
extern char superBoard[boardSize][boardSize],
            baseBoard[boardSize],
            turn;
extern int computedMove;

void checkInput();
void drawTiles();
void drawComputationDetails();

void moveOpponent();
int evaluateTopMove(int computedMoves[]);
void computeMove(char board[], size_t index);
bool checkWinner(char board[] , char player);
bool checkWinningMoves(char board[] , char player);
bool checkDangerPosition(char board[]);
bool checkCentre(char board[]);
bool checkCorner(char board[]);
bool checkEdge(char board[]);

#endif