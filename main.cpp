#include "raylib.h"
#include "declaration.h"

char superBoard[boardSize][boardSize];
char baseBoard[boardSize];
std::string computationDetails;
char turn = 'x';
int computedMove = 4;
bool win = false;

int main() {
    const int screenWidth = 950;
    const int screenHeight = 550;
    InitWindow(screenWidth, screenHeight, "Super TicTacToe!");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);

    for (size_t boardIndex = 0; boardIndex < boardSize; ++boardIndex) {
        baseBoard[boardIndex] = ' ';
        for (size_t tileIndex = 0; tileIndex < boardSize; ++ tileIndex) {
            superBoard[boardIndex][tileIndex] = ' ';
        }
    }

    while (!WindowShouldClose()) {
        if (checkWinner(baseBoard, 'o')) win = true;
        if (checkWinner(baseBoard, 'x')) win = true;
        for (size_t index = 0; index < boardSize; ++index) {
            if (checkWinner(superBoard[index], 'o')) baseBoard[index] = 'o';
            if (checkWinner(superBoard[index], 'x')) baseBoard[index] = 'x';
        }

        if (!win) {
            if (turn == 'o') moveOpponent();
            checkInput();
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            drawTiles();
            drawComputationDetails();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

void checkInput() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && turn == 'x') {
        for (size_t boardIndex = 0; boardIndex < boardSize; ++boardIndex) {
            int boardCol = static_cast<int>(boardIndex) / 3;
            int boardRow = static_cast<int>(boardIndex) % 3;

            for (size_t tileIndex = 0; tileIndex < boardSize; ++tileIndex) {
                int tileCol = static_cast<int>(tileIndex) / 3;
                int tileRow = static_cast<int>(tileIndex) % 3;
                int x = boardRow * 3 * tileSize + tileRow * tileSize + boardMargin;
                int y = boardCol * 3 * tileSize + tileCol * tileSize + boardMargin;

                Rectangle tile = { static_cast<float>(x), static_cast<float>(y), 
                    static_cast<float>(tileSize), static_cast<float>(tileSize) };

                if (CheckCollisionPointRec(GetMousePosition(), tile) && superBoard[boardIndex][tileIndex] == ' ' && 
                    baseBoard[boardIndex] == ' ') {
                    superBoard[boardIndex][tileIndex] = 'x';
                    turn = 'o';
                }
            }
        }
    }
}

bool checkWinner(char board[], char player) {
    for (size_t index = 0; index < 8; ++index) {
        if (board[winners[index][0]] == player && board[winners[index][1]] == player && board[winners[index][2]] == player) {
            return true;
        } 
    }
    return false;
}