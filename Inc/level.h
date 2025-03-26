#ifndef LEVEL_H
#define LEVEL_H

#include "cJSON.h"
#include "game.h"

#define TILE_SIZE 32
#define FRAME_COUNT 4
#define FRAME_TIME 0.1f

typedef struct {
    CP_Image* tiles;       // Array of tile images
    int tile_count;        // Number of tiles in the tileset
    int tile_width;        // Width of each tile
    int tile_height;       // Height of each tile
    char* tileset_path;    // Path to the tileset (optional, for reference)
    int* colliders;        // Array indicating which tiles are colliders
} Tileset;

typedef struct {
    int* data;             // Tile data array
    int width;             // Layer width in tiles
    int height;            // Layer height in tiles
    char* name;            // Layer name
} Layer;

typedef struct {
    Tileset* tilesets;     // Array of tilesets
    int tileset_count;     // Number of tilesets
    Layer* layers;         // Array of layers
    int layer_count;       // Number of layers
    int map_width;         // Map width in tiles
    int map_height;        // Map height in tiles
    int tile_width;        // Tile width in pixels
    int tile_height;       // Tile height in pixels
} Level;

typedef struct {
    float x, y;            // Position
    CP_Image image;        // Decoration image
} DecoInstance;

typedef struct {
    CP_Image frame_flag[FRAME_COUNT];  // Animation frames
    float frametimer;                  // Animation timer
    int currentframe;                  // Current frame index
} Deco;

extern Level current_level;
extern Deco flag;
extern DecoInstance tree;
extern DecoInstance ridges;
extern DecoInstance bushes[4];
extern CP_Image willows;
extern CP_Image Ridges;
extern CP_Image Bushes;
extern CP_Image Bushes2;

void initializeLevel(void);
void drawLevel(void);
void drawMap(void);
void initializeDecoration(void);
void drawDecoration(void);
void exitLevel(void);
void flag_init(Deco* flag);
void update_flag(Deco* flag, float deltatime);
void drawFlag(Deco* flag, float x, float y, float width, float height);
int isTileCollider(int x, int y);

#endif // LEVEL_H