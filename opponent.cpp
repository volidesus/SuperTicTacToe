#include <algorithm>
#include "raylib.h"
#include "declaration.h"

int evaluateTopMove(int computedMoves[]) {
    int computedMoveScores[boardSize] = {};

    if (checkWinningMoves(baseBoard, 'o')) {
        computedMoveScores[computedMove] += 50;
    } else if (checkWinningMoves(baseBoard, 'x')) {
        computedMoveScores[computedMove] += 40;
    }

    computationDetails.clear();
    for (size_t index = 0; index < boardSize; ++index) {
        int move = computedMoves[index];

        if (checkWinningMoves(superBoard[index], 'o')) computedMoveScores[index] += 6;
        else if (checkWinningMoves(superBoard[index], 'x')) computedMoveScores[index] += 5;
        else if (checkDangerPosition(superBoard[index])) computedMoveScores[index] += 4;

        if (checkCentre(superBoard[index])) computedMoveScores[index] += 3;
        else if (checkCorner(superBoard[index])) computedMoveScores[index] += 2;
        else if (checkEdge(superBoard[index])) computedMoveScores[index] += 1;

        if (std::all_of(std::begin(superBoard[index]), std::end(superBoard[index]), [](char c) { return c == ' '; })) computedMoveScores[index] -= 5;
        if (move < 0 || superBoard[index][move] != ' ') computedMoveScores[index] = 0;
        computationDetails += "Board: " + std::to_string(index) + " Move: " + std::to_string(move) + " Score: " + std::to_string(computedMoveScores[index]) + "\n\n\n";
    }
    return static_cast<int>(std::distance(std::begin(computedMoveScores), std::max_element(std::begin(computedMoveScores), std::end(computedMoveScores))));
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

bool checkWinner(char board[], char player) {
    for (size_t index = 0; index < 8; ++index) {
        if (board[winners[index][0]] == player && board[winners[index][1]] == player && board[winners[index][2]] == player) {
            return true;
        } 
    }
    return false;
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

bool checkDangerPosition(char board[]) {
    for (size_t index = 0; index < boardSize; ++index) {
        if (board == dangerPositions[index] &&
            board[dangerPositionComputedMove[index]] == ' ') {
            computedMove = dangerPositionComputedMove[index];
            return false;
        }
    }
    return true;
}

bool checkCentre(char board[]) {
    if (board[4] == ' ') {
        computedMove = 4;
        return false;
    }
    return true;
}

bool checkCorner(char board[]) {
    for (size_t corner : corners) {
        if (board[corner] == ' ') {
            computedMove = static_cast<int>(corner);
            return false;
        }
    }
    return true;
}

bool checkEdge(char board[]) {
    for (size_t edge : edges) {
        if (board[edge] == ' ') {
            computedMove = static_cast<int>(edge);
            return false;
        }
    }
    return true;
}