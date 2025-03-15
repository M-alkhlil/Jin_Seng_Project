#include"collision.h"


int IsSolidTileAt(float x, float y) {
    int col = (int)(x / TILE_SIZE);
    int row = (int)(y / TILE_SIZE);

    if (row < 0 || row >= MAP_HEIGHT || col < 0 || col >= MAP_WIDTH)
        return 1; // Treat out-of-bounds as solid

    int solidTiles[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28 };

    int tile = map[row][col];

    for (int i = 0; i < sizeof(solidTiles) / sizeof(solidTiles[0]); i++) {
        if (tile == solidTiles[i])
            return 1; // Collision detected
    }
    return 0; // No collision
}

int CheckCollision(float x, float y, float width, float height) {
    return IsSolidTileAt(x, y) ||          // Top-left corner
        IsSolidTileAt(x + width, y) ||  // Top-right corner
        IsSolidTileAt(x, y + height) || // Bottom-left corner
        IsSolidTileAt(x + width, y + height); // Bottom-right corner
}