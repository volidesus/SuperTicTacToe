#include "raylib.h"
#include "declaration.h"
#include <string.h>
#include <stdio.h>

const int winners[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
const int dangerPositionComputedMove[9] = {1, 3, 0, 3, 6, 8, 8, 6, 8};
const int corners[4] = {0, 2, 6, 8};
const int edges[4] = {1, 3, 5, 7};
const char dangerPositions[9][9] = {
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

void moveOpponent(void) {
    int computedMoves[boardSize];
    
    for (size_t index = 0; index < boardSize; ++index) {
        if (baseBoard[index] == ' ') {
            computeMove(superBoard[index], index);
            computedMoves[index] = computedMove;
        } else {
            computedMoves[index] = -1;
        }
    }

    int baseComputedMove = evaluateTopMove(computedMoves);
    
    if (baseComputedMove >= 0 && baseComputedMove < boardSize && baseBoard[baseComputedMove] == ' ') {
        int superComputedMove = computedMoves[baseComputedMove];
        
        if (superComputedMove >= 0 && superComputedMove < boardSize && superBoard[baseComputedMove][superComputedMove] == ' ') {
            superBoard[baseComputedMove][superComputedMove] = 'o';
            turn = 'x';
        } else {
            for (int i = 0; i < boardSize; ++i) {
                if (superBoard[baseComputedMove][i] == ' ') {
                    superBoard[baseComputedMove][i] = 'o';
                    turn = 'x';
                    break;
                }
            }
        }
    } else {
        win = true;
    }
}

int evaluateTopMove(int computedMoves[]) {
    int computedMoveScores[boardSize] = {0};

    if (checkWinningMoves(baseBoard, 'o')) {
        computedMoveScores[computedMove] += 50;
    } else if (checkWinningMoves(baseBoard, 'x')) {
        computedMoveScores[computedMove] += 40;
    }

    memset(computationDetails, 0, sizeof(computationDetails));
    strcat(computationDetails, "Board || Move || Score");
    for (size_t index = 0; index < boardSize; ++index) {
        int move = computedMoves[index];

        if (checkWinningMoves(superBoard[index], 'o')) computedMoveScores[index] += 6;
        else if (checkWinningMoves(superBoard[index], 'x')) computedMoveScores[index] += 5;
        else if (checkDangerPosition(superBoard[index])) computedMoveScores[index] += 4;

        if (checkCentre(superBoard[index])) computedMoveScores[index] += 3;
        else if (checkCorner(superBoard[index])) computedMoveScores[index] += 2;
        else if (checkEdge(superBoard[index])) computedMoveScores[index] += 1;

        int allEmpty = 1;
        for (int i = 0; i < boardSize; ++i) {
            if (superBoard[index][i] != ' ') {
                allEmpty = 0;
                break;
            }
        }
        if (allEmpty) computedMoveScores[index] -= 5;
        if (move < 0 || superBoard[index][move] != ' ') computedMoveScores[index] = 0;

        if (computedMoveScores[index] != 0) {
            char buffer[100];
            sprintf(buffer, "\n\n\n%zu       ||   %d    ||    %d", index, move, computedMoveScores[index]);
            strcat(computationDetails, buffer);
        }
    }
    
    int maxScore = computedMoveScores[0];
    int maxIndex = 0;
    for (int i = 1; i < boardSize; ++i) {
        if (computedMoveScores[i] > maxScore) {
            maxScore = computedMoveScores[i];
            maxIndex = i;
        }
    }
    return maxIndex;
}

void computeMove(char board[], size_t index) {
    if (baseBoard[index] != ' ') {
        computedMove = -1;
        return;
    }

    bool move = true;
    computedMove = 4;
    move = checkWinningMoves(board, 'o');
    if (move) move = checkWinningMoves(board, 'x');
    if (move) move = checkDangerPosition(board);
    if (move) move = checkCentre(board);
    if (move) move = checkCorner(board);
    if (move) move = checkEdge(board);
    if (move) computedMove = -1;
}

bool checkWinningMoves(char board[], char player) {
    for (size_t index = 0; index < 8; ++index) {
        if (board[winners[index][0]] == player && board[winners[index][1]] == player && board[winners[index][2]] == ' ') {
            computedMove = winners[index][2];
            return false;
        } 
        else if (board[winners[index][0]] == player && board[winners[index][1]] == ' ' && board[winners[index][2]] == player) {
            computedMove = winners[index][1];
            return false;
        } 
        else if (board[winners[index][0]] == ' ' && board[winners[index][1]] == player && board[winners[index][2]] == player) {
            computedMove = winners[index][0];
            return false;
        }
    }
    return true;
}

bool checkDangerPosition(const char board[]) {
    for (size_t index = 0; index < boardSize; ++index) {
        if (memcmp(board, dangerPositions[index], boardSize) == 0 &&
            board[dangerPositionComputedMove[index]] == ' ') {
            computedMove = dangerPositionComputedMove[index];
            return false;
        }
    }
    return true;
}

bool checkCentre(const char board[]) {
    if (board[4] == ' ') {
        computedMove = 4;
        return false;
    }
    return true;
}

bool checkCorner(const char board[]) {
    for (size_t i = 0; i < 4; ++i) {
        if (board[corners[i]] == ' ') {
            computedMove = corners[i];
            return false;
        }
    }
    return true;
}

bool checkEdge(const char board[]) {
    for (size_t i = 0; i < 4; ++i) {
        if (board[edges[i]] == ' ') {
            computedMove = edges[i];
            return false;
        }
    }
    return true;
}