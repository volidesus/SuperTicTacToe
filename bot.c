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
    
    for (int i = 0; i < boardSize; i++) {
        computedMoves[i] = (baseBoard[i] == ' ') ? computeMove(superBoard[i]) : -1;
    }

    int baseComputedMove = evaluateTopMove(computedMoves);
    
    if (baseComputedMove >= 0 && baseComputedMove < boardSize && baseBoard[baseComputedMove] == ' ') {
        int superComputedMove = computedMoves[baseComputedMove];
        
        if (superComputedMove >= 0 && superComputedMove < boardSize && superBoard[baseComputedMove][superComputedMove] == ' ') {
            superBoard[baseComputedMove][superComputedMove] = 'o';
        } else {
            for (int i = 0; i < boardSize; i++) {
                if (superBoard[baseComputedMove][i] == ' ') {
                    superBoard[baseComputedMove][i] = 'o';
                    break;
                }
            }
        }
        turn = 'x';
    } else {
        resetGame();
    }
}

int evaluateTopMove(int computedMoves[]) {
    int computedMoveScores[boardSize] = {0};
    char buffer[100];

    computedMoveScores[computedMove] += checkWinningMoves(baseBoard, 'o') ? 50 : (checkWinningMoves(baseBoard, 'x') ? 40 : 0);

    snprintf(computationDetails, sizeof(computationDetails), "Board || Move || Score");
    
    for (int i = 0; i < boardSize; i++) {
        int move = computedMoves[i];
        if (checkWinningMoves(superBoard[i], 'o')) computedMoveScores[i] += 6;
        else if (checkWinningMoves(superBoard[i], 'x')) computedMoveScores[i] += 5;
        else if (checkDangerPosition(superBoard[i])) computedMoveScores[i] += 4;
        else if (checkCentre(superBoard[i])) computedMoveScores[i] += 3;
        else if (checkCorner(superBoard[i])) computedMoveScores[i] += 2;
        else if (checkEdge(superBoard[i])) computedMoveScores[i] += 1;

        int allEmpty = 1;
        for (int j = 0; j < boardSize; j++) {
            if (superBoard[i][j] != ' ') {
                allEmpty = 0;
                break;
            }
        }
        if (allEmpty) computedMoveScores[i] -= 5;
        if (move < 0 || superBoard[i][move] != ' ') computedMoveScores[i] = 0;

        if (computedMoveScores[i] != 0) {
            snprintf(buffer, sizeof(buffer), "\n\n\n%d     ||   %d  ||    %d", i, move, computedMoveScores[i]);
            size_t remaining = sizeof(computationDetails) - strlen(computationDetails) - 1;
            strncat(computationDetails, buffer, remaining);
        }
    }
    
    int maxScore = computedMoveScores[0];
    int maxIndex = 0;
    for (int i = 1; i < boardSize; i++) {
        if (computedMoveScores[i] > maxScore) {
            maxScore = computedMoveScores[i];
            maxIndex = i;
        }
    }
    return maxIndex;
}

int computeMove(char board[]) {
    if (!checkWinningMoves(board, 'o') &&
        !checkWinningMoves(board, 'x') &&
        !checkDangerPosition(board) &&
        !checkCentre(board) &&
        !checkCorner(board) &&
        !checkEdge(board)) {
        return -1;
    }
    return computedMove;
}

bool checkWinningMoves(char board[], char player) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[winners[i][j]] == ' ' &&
                board[winners[i][(j+1)%3]] == player &&
                board[winners[i][(j+2)%3]] == player) {
                computedMove = winners[i][j];
                return true;
            }
        }
    }
    return false;
}

bool checkDangerPosition(const char board[]) {
    for (int i = 0; i < boardSize; i++) {
        if (memcmp(board, dangerPositions[i], boardSize) == 0 &&
            board[dangerPositionComputedMove[i]] == ' ') {
            computedMove = dangerPositionComputedMove[i];
            return true;
        }
    }
    return false;
}

bool checkCentre(const char board[]) {
    if (board[4] == ' ') {
        computedMove = 4;
        return true;
    }
    return false;
}

bool checkCorner(const char board[]) {
    for (int i = 0; i < 4; i++) {
        if (board[corners[i]] == ' ') {
            computedMove = corners[i];
            return true;
        }
    }
    return false;
}

bool checkEdge(const char board[]) {
    for (int i = 0; i < 4; i++) {
        if (board[edges[i]] == ' ') {
            computedMove = edges[i];
            return true;
        }
    }
    return false;
}