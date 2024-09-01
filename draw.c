#include "raylib.h"
#include "declaration.h"
#include <stdio.h>

void drawMenu(void) {
    DrawTextEx(prstart, "Super TicTacToe!", (Vector2){ (float)GetScreenWidth() / 2 - 250, 50 }, 30, 2, BLACK);
    DrawRectangleLinesEx((Rectangle){ (float)GetScreenWidth() / 2 - 250, 200, 500, 60 }, 4,  BLACK);
    DrawTextEx(prstart, "Single Player", (Vector2){ (float)GetScreenWidth() / 2 - 200, 215 }, 30, 2, BLACK);
    DrawRectangleLinesEx((Rectangle){ (float)GetScreenWidth() / 2 - 250, 300, 500, 60 }, 4,  BLACK);
    DrawTextEx(prstart, "Two Players", (Vector2){ (float)GetScreenWidth() / 2 - 175, 315 }, 30, 2, BLACK);
}

void drawTiles(void) {
    for (size_t boardIndex = 0; boardIndex < boardSize; ++boardIndex) {
        int boardX = (int)(boardIndex) % 3 * 3 * tileSize + boardMargin;
        int boardY = (int)(boardIndex) / 3 * 3 * tileSize + boardMargin;

        for (size_t tileIndex = 0; tileIndex < boardSize; ++tileIndex) {
            int tileX = (int)(boardIndex) % 3 * 3 * tileSize + (int)(tileIndex) % 3 * tileSize + boardMargin;
            int tileY = (int)(boardIndex) / 3 * 3 * tileSize + (int)(tileIndex) / 3 * tileSize + boardMargin;

            Color tileColor = (baseBoard[boardIndex] != ' ') ? GRAY : BLACK;
            DrawRectangleLines(tileX, tileY, tileSize, tileSize, tileColor);
            if (superBoard[boardIndex][tileIndex] == 'x') DrawTextEx(prstart, "X", (Vector2){ (float)tileX + 8, (float)tileY + 8 }, (float)tileSize - 10, 2, tileColor);
            if (superBoard[boardIndex][tileIndex] == 'o') DrawTextEx(prstart, "O", (Vector2){ (float)tileX + 8, (float)tileY + 8 }, (float)tileSize - 10, 2, tileColor);
        }
        
        DrawRectangleLinesEx((Rectangle){(float)boardX, (float)boardY, (float)tileSize * 3, (float)tileSize * 3}, 2, BLACK);
        if (baseBoard[boardIndex] == 'x') DrawTextEx(prstart, "X", (Vector2){ (float)boardX + 24, (float)boardY + 24 }, ((float)tileSize - 10) * 3, 2, BLACK);
        if (baseBoard[boardIndex] == 'o') DrawTextEx(prstart, "O", (Vector2){ (float)boardX + 24, (float)boardY + 24 }, ((float)tileSize - 10) * 3, 2, BLACK);
    }
}

void drawComputationDetails(void) {
    int x = tileSize * boardSize + boardMargin * 2;
    int y = boardMargin;
    DrawTextEx(prstart, computationDetails, (Vector2){ (float)x, (float)y }, 17, 2, BLACK);
}