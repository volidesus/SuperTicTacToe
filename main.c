#include "raylib.h"
#include "declaration.h"
#include <string.h>

char superBoard[boardSize][boardSize];
char baseBoard[boardSize];
char computationDetails[1000] = "";
char turn = 'x';
int computedMove = 4;
int state = 0;
Font prstart;

int main(void) {
    initializeGame();
    while (!WindowShouldClose()) {
        for (int index = 0; index < boardSize; ++index) {
            if (checkWinner(superBoard[index], 'o')) baseBoard[index] = 'o';
            if (checkWinner(superBoard[index], 'x')) baseBoard[index] = 'x';
        }

        if (checkWinner(baseBoard, 'o')) resetGame();
        if (checkWinner(baseBoard, 'x')) resetGame();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (state == 0) {
            checkMenuInput();
            drawMenu();
        } else if (state == 1) {
            if (turn == 'o') moveOpponent();
            checkGameInput('x');
            drawTiles();
            drawComputationDetails();
        } else if (state == 2) {
            checkGameInput('x');
            checkGameInput('o');
            drawTiles();
        }
        EndDrawing();
    }
    cleanupGame();
    return 0;
}

void resetGame(void) {
    state = 0;
    memset(superBoard, ' ', sizeof(superBoard));
    memset(baseBoard, ' ', sizeof(baseBoard));
}

void initializeGame(void) {
    const int screenWidth = 1200;
    const int screenHeight = 550;
    InitWindow(screenWidth, screenHeight, "Super TicTacToe!");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);
    
    prstart = LoadFont("res/prstart.ttf");

    for (int boardIndex = 0; boardIndex < boardSize; ++boardIndex) {
        baseBoard[boardIndex] = ' ';
        for (int tileIndex = 0; tileIndex < boardSize; ++tileIndex) {
            superBoard[boardIndex][tileIndex] = ' ';
        }
    }
}

void cleanupGame(void) {
    UnloadFont(prstart);
    CloseWindow();
}

void checkMenuInput(void) {
    Rectangle singlePlayerButton = { GetScreenWidth() / 2.0f - 250, 200, 500, 60 };
    Rectangle twoPlayersButton = { GetScreenWidth() / 2.0f - 250, 300, 500, 60 };
    
    Vector2 mousePosition = GetMousePosition();
    
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(mousePosition, singlePlayerButton)) {
            state = 1;
        } else if (CheckCollisionPointRec(mousePosition, twoPlayersButton)) {
            state = 2;
        }
    }
}

void checkGameInput(char player) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && turn == player) {
        for (int boardIndex = 0; boardIndex < boardSize; ++boardIndex) {
            for (int tileIndex = 0; tileIndex < boardSize; ++tileIndex) {
                int x = boardIndex % 3 * 3 * tileSize + tileIndex % 3 * tileSize + boardMargin;
                int y = boardIndex / 3 * 3 * tileSize + tileIndex / 3 * tileSize + boardMargin;

                Rectangle tile = { (float)x, (float)y, (float)tileSize, (float)tileSize };
                if (CheckCollisionPointRec(GetMousePosition(), tile) && superBoard[boardIndex][tileIndex] == ' ' && 
                    baseBoard[boardIndex] == ' ') {
                    superBoard[boardIndex][tileIndex] = player;
                    turn = (player == 'x') ? 'o' : 'x';
                }
            }
        }
    }
}

bool checkWinner(const char board[], char player) {
    for (int index = 0; index < 8; ++index) {
        if (board[winners[index][0]] == player && board[winners[index][1]] == player && board[winners[index][2]] == player) {
            return true;
        } 
    }
    return false;
}