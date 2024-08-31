#include <array>
#include <algorithm>
#include "raylib.h"
#include "declaration.h"

int evaluateTopMove(const std::vector<int>& computedMoves) {
    std::vector<int> computedMoveScores(computedMoves.size(), 0);

    if (checkWinningMoves(baseBoard, 'o')) {
        computedMoveScores[computedMove] += 50;
    } else if (checkWinningMoves(baseBoard, 'x')) {
        computedMoveScores[computedMove] += 40;
    }

    computationDetails = "";
    for (size_t i = 0; i < computedMoves.size(); ++i) {
        int move = computedMoves[i];
        
        for (size_t j = 0; j < 8; ++j) {
            if (checkWinningMoves(superBoard[i], 'o')) {
                computedMoveScores[i] += 6;
            } else if (checkWinningMoves(superBoard[i], 'x')) {
                computedMoveScores[i] += 5;
            } else if (checkDangerPosition(superBoard[i])) {
                computedMoveScores[i] += 4;
            } 
            
            if (checkCentre(superBoard[i])) {
                computedMoveScores[i] += 3;
            } else if (checkCorner(superBoard[i])) {
                computedMoveScores[i] += 2;
            } else if (checkEdge(superBoard[i])) {
                computedMoveScores[i] += 1;
            }
        }
        
        std::vector<char> emptyBoard = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
        if (superBoard[i] == emptyBoard) {
            computedMoveScores[i] -= 5;
        }

        if (move < 0 || superBoard[i][move] != ' ') {
            computedMoveScores[i] = 0;
        }

        computationDetails += "Board: " + std::to_string(i) + " Move: " + std::to_string(move) + " Score: " + std::to_string(computedMoveScores[i]) + "\n\n\n";
    }
    return static_cast<int>(std::distance(computedMoveScores.begin(), std::max_element(computedMoveScores.begin(), computedMoveScores.end())));
}

void computeMove(std::vector<char>& board, size_t index) {
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

bool checkWinner(const std::vector<char> board, char player) {
    for (size_t index = 0; index < 8; ++index) {
        if (board[winners[index][0]] == player && board[winners[index][1]] == player && board[winners[index][2]] == player) {
            return true;
        } 
    }
    return false;
}

bool checkWinningMoves(const std::vector<char> board, char player) {
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

bool checkDangerPosition(const std::vector<char> board) {
    for (size_t index = 0; index < boardSize; ++index) {
        if (std::equal(board.begin(), board.end(), std::begin(dangerPositions[index]), std::end(dangerPositions[index])) &&
            board[dangerPositionComputedMove[index]] == ' ') {
            computedMove = dangerPositionComputedMove[index];
            return false;
        }
    }
    return true;
}

bool checkCentre(std::vector<char> board) {
    if (board[4] == ' ') {
        computedMove = 4;
        return false;
    }
    return true;
}

bool checkCorner(std::vector<char> board) {
    for (size_t corner : corners) {
        if (board[corner] == ' ') {
            computedMove = static_cast<int>(corner);
            return false;
        }
    }
    return true;
}

bool checkEdge(std::vector<char> board) {
    for (size_t edge : edges) {
        if (board[edge] == ' ') {
            computedMove = static_cast<int>(edge);
            return false;
        }
    }
    return true;
}