#include <vector>
#include <array>
#include <string>
#ifndef DECLARATION_H
#define DECLARATION_H

constexpr int boardMargin = 50;
constexpr int tileSize = 50;
constexpr int boardSize = 9;

constexpr int winners[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
constexpr int dangerPositionComputedMove[9] = {1, 3, 0, 3, 6, 8, 8, 6, 8};
constexpr int corners[4] = {0, 2, 6, 8};
constexpr int edges[4] = {1, 3, 5, 7};
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

extern std::string computationDetails;
extern std::vector<std::vector<char>> superBoard;
extern std::vector<char> baseBoard;
extern int computedMove;
extern char turn;

void checkInput();
void drawTiles();
void drawComputationDetails();

void moveOpponent();
int evaluateTopMove(const std::vector<int>& computedMoves);
void computeMove(std::vector<char>& board, size_t index);
bool checkWinner(const std::vector<char> board, char player);
bool checkWinningMoves(const std::vector<char> board, char player);
bool checkDangerPosition(std::vector<char> board);
bool checkCentre(std::vector<char> board);
bool checkCorner(std::vector<char> board);
bool checkEdge(std::vector<char> board);

#endif