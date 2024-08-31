#include "raylib.h"
#include "declaration.h"
#include <stdio.h>

void drawTiles(void) {
    for (size_t boardIndex = 0; boardIndex < boardSize; ++boardIndex) {
        int boardX = (int)(boardIndex) % 3 * 3 * tileSize + boardMargin;
        int boardY = (int)(boardIndex) / 3 * 3 * tileSize + boardMargin;

        for (size_t tileIndex = 0; tileIndex < boardSize; ++tileIndex) {
            int tileX = (int)(boardIndex) % 3 * 3 * tileSize + (int)(tileIndex) % 3 * tileSize + boardMargin;
            int tileY = (int)(boardIndex) / 3 * 3 * tileSize + (int)(tileIndex) / 3 * tileSize + boardMargin;

            Color color = (baseBoard[boardIndex] != ' ') ? GRAY : BLACK;
            DrawRectangleLines(tileX, tileY, tileSize, tileSize, color);
            if (superBoard[boardIndex][tileIndex] == 'x') DrawText("X", tileX + 10, tileY, tileSize, color);
            if (superBoard[boardIndex][tileIndex] == 'o') DrawText("O", tileX + 10, tileY, tileSize, color);
        }
        
        DrawRectangleLinesEx((Rectangle){(float)boardX, (float)boardY, (float)tileSize * 3, (float)tileSize * 3}, 5, BLACK);
        if (baseBoard[boardIndex] == 'x') DrawText("X", boardX + 30, boardY, tileSize * 3, BLACK);
        if (baseBoard[boardIndex] == 'o') DrawText("O", boardX + 30, boardY, tileSize * 3, BLACK);
    }
}

void drawComputationDetails(void) {
    int x = tileSize * boardSize + boardMargin * 2;
    int y = boardMargin;
    DrawText(computationDetails, x, y, 30, BLACK);
}