#include <vector>
#include <algorithm>
#include <array>
#include <cmath>
#include "raylib.h"
#include "declaration.h"

void drawTiles() {
    for (size_t boardIndex = 0; boardIndex < boardSize; ++boardIndex) {
        int boardX = static_cast<int>(boardIndex) % 3 * 3 * tileSize + boardMargin;
        int boardY = static_cast<int>(boardIndex) / 3 * 3 * tileSize + boardMargin;

        for (size_t tileIndex = 0; tileIndex < boardSize; ++tileIndex) {
            int tileX = static_cast<int>(boardIndex) % 3 * 3 * tileSize + static_cast<int>(tileIndex) % 3 * tileSize + boardMargin;
            int tileY = static_cast<int>(boardIndex) / 3 * 3 * tileSize + static_cast<int>(tileIndex) / 3 * tileSize + boardMargin;

            Color color = (baseBoard[boardIndex] != ' ') ? GRAY : BLACK;
            DrawRectangleLines(tileX, tileY, tileSize, tileSize, color);
            if (superBoard[boardIndex][tileIndex] == 'x') DrawText("X", tileX + 10, tileY, tileSize, color);
            if (superBoard[boardIndex][tileIndex] == 'o') DrawText("O", tileX + 10, tileY, tileSize, color);
        }
        
        DrawRectangleLinesEx({static_cast<float>(boardX), static_cast<float>(boardY), static_cast<float>(tileSize) * 3, static_cast<float>(tileSize) * 3}, 5, BLACK);
        if (baseBoard[boardIndex] == 'x') DrawText("X", boardX + 30, boardY, tileSize * 3, BLACK);
        if (baseBoard[boardIndex] == 'o') DrawText("O", boardX + 30, boardY, tileSize * 3, BLACK);
    }
}

void drawComputationDetails() {
    int x = tileSize * boardSize + boardMargin * 2;
    int y = boardMargin;
    DrawText(computationDetails.c_str(), x, y, 30, BLACK);
}