#include "level.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global variable definitions
Level current_level;
Deco flag;
DecoInstance tree;
DecoInstance ridges;
DecoInstance bushes[4];
CP_Image willows;
CP_Image Ridges;
CP_Image Bushes;
CP_Image Bushes2;

// Tile image mapping (adjust paths to match your assets)
static const char* tile_paths[] = {
    "Assets/Tile/Tile_01.png", // ID 0 (Tiled ID 1)
    "Assets/Tile/Tile_02.png", // ID 1 (Tiled ID 2)
    "Assets/Tile/Tile_03.png", // ID 2 (Tiled ID 3)
    "Assets/Tile/Tile_04.png", // ID 3 (Tiled ID 4)
    "Assets/Tile/Tile_05.png", // ID 4 (Tiled ID 5)
    "Assets/Tile/Tile_06.png", // ID 5 (Tiled ID 6)
    "Assets/Tile/Tile_07.png", // ID 6 (Tiled ID 7)
    "Assets/Tile/Tile_08.png", // ID 7 (Tiled ID 8)
    "Assets/Tile/Tile_09.png", // ID 8 (Tiled ID 9)
    "Assets/Tile/Tile_10.png", // ID 9 (Tiled ID 10)
    "Assets/Tile/Tile_11.png", // ID 10 (Tiled ID 11)
    "Assets/Tile/Tile_12.png", // ID 11 (Tiled ID 12)
    "Assets/Tile/Tile_13.png", // ID 12 (Tiled ID 13)
    "Assets/Tile/Tile_14.png", // ID 13 (Tiled ID 14)
    "Assets/Tile/Tile_15.png", // ID 14 (Tiled ID 15)
    "Assets/Tile/Tile_16.png", // ID 15 (Tiled ID 16)
    "Assets/Tile/Tile_17.png", // ID 16 (Tiled ID 17)
    "Assets/Tile/Tile_18.png", // ID 17 (Tiled ID 18)
    "Assets/Tile/Tile_19.png", // ID 18 (Tiled ID 19)
    "Assets/Tile/Tile_20.png", // ID 19 (Tiled ID 20)
    "Assets/Tile/Tile_21.png", // ID 20 (Tiled ID 21)
    "Assets/Tile/Tile_22.png", // ID 21 (Tiled ID 22)
    "Assets/Tile/Tile_23.png", // ID 22 (Tiled ID 23)
    "Assets/Tile/Tile_24.png", // ID 23 (Tiled ID 24)
    "Assets/Tile/Tile_25.png", // ID 24 (Tiled ID 25)
    "Assets/Tile/Tile_26.png", // ID 25 (Tiled ID 26)
    "Assets/Tile/Tile_27.png", // ID 26 (Tiled ID 27)
    "Assets/Tile/Tile_28.png", // ID 27 (Tiled ID 28)
    "Assets/Tile/Tile_29.png", // ID 28 (Tiled ID 29)
    "Assets/Tile/Tile_30.png", // ID 29 (Tiled ID 30)
    "Assets/Tile/Tile_31.png", // ID 30 (Tiled ID 31)
    "Assets/Tile/Tile_32.png", // ID 31 (Tiled ID 32)
    "Assets/Tile/Tile_33.png", // ID 32 (Tiled ID 33)
    "Assets/Tile/Tile_34.png", // ID 33 (Tiled ID 34)
    "Assets/Tile/Tile_35.png", // ID 34 (Tiled ID 35)
    "Assets/Tile/Tile_36.png", // ID 35 (Tiled ID 36)
    "Assets/Tile/Tile_37.png", // ID 36 (Tiled ID 37)
    "Assets/Tile/Tile_38.png", // ID 37 (Tiled ID 38)
    "Assets/Tile/Tile_39.png", // ID 38 (Tiled ID 39)
    "Assets/Tile/Tile_40.png", // ID 39 (Tiled ID 40)
    "Assets/Tile/Tile_41.png", // ID 40 (Tiled ID 41)
    "Assets/Tile/Tile_42.png", // ID 41 (Tiled ID 42)
    "Assets/Tile/Tile_43.png", // ID 42 (Tiled ID 43)
    "Assets/Tile/Tile_44.png", // ID 43 (Tiled ID 44)
    "Assets/Tile/Tile_45.png", // ID 44 (Tiled ID 45)
    "Assets/Tile/Tile_46.png", // ID 45 (Tiled ID 46)
    "Assets/Tile/Tile_47.png", // ID 46 (Tiled ID 47)
    "Assets/Tile/Tile_48.png", // ID 47 (Tiled ID 48)
    "Assets/Tile/Tile_49.png", // ID 48 (Tiled ID 49)
    "Assets/Tile/Tile_50.png", // ID 49 (Tiled ID 50)
    "Assets/Tile/Tile_51.png", // ID 50 (Tiled ID 51)
    "Assets/Tile/Tile_52.png", // ID 51 (Tiled ID 52)
    "Assets/Tile/Tile_53.png", // ID 52 (Tiled ID 53)
    "Assets/Tile/Tile_54.png", // ID 53 (Tiled ID 54)
    "Assets/Tile/Tile_55.png", // ID 54 (Tiled ID 55)
    "Assets/Tile/Tile_56.png", // ID 55 (Tiled ID 56)
    "Assets/Tile/Tile_57.png", // ID 56 (Tiled ID 57)
    "Assets/Tile/Tile_58.png", // ID 57 (Tiled ID 58)
    "Assets/Tile/Tile_59.png", // ID 58 (Tiled ID 59)
    "Assets/Tile/Tile_60.png", // ID 59 (Tiled ID 60)
};

static char* load_file(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* content = malloc(length + 1);
    fread(content, 1, length, file);
    content[length] = '\0';
    fclose(file);
    return content;
}

void initializeLevel(void) {
    char* json_string = load_file("Assets/map.json");
    if (!json_string) {
        printf("Failed to load map.json\n");
        return;
    }

    cJSON* json = cJSON_Parse(json_string);
    if (!json) {
        printf("Failed to parse JSON: %s\n", cJSON_GetErrorPtr());
        free(json_string);
        return;
    }

    current_level.map_width = cJSON_GetObjectItem(json, "width")->valueint;
    current_level.map_height = cJSON_GetObjectItem(json, "height")->valueint;
    current_level.tile_width = TILE_SIZE;
    current_level.tile_height = TILE_SIZE;

    cJSON* tilesets = cJSON_GetObjectItem(json, "tilesets");
    current_level.tileset_count = cJSON_GetArraySize(tilesets);
    current_level.tilesets = malloc(sizeof(Tileset) * current_level.tileset_count);

    for (int i = 0; i < current_level.tileset_count; i++) {
        cJSON* tileset = cJSON_GetArrayItem(tilesets, i);
        Tileset* ts = &current_level.tilesets[i];  // Take address of the struct

        ts->tile_count = cJSON_GetObjectItem(tileset, "tilecount")->valueint;
        ts->tile_width = TILE_SIZE;
        ts->tile_height = TILE_SIZE;
        ts->tileset_path = _strdup("Assets/Tile/Tileset.png"); // Kept for reference, not used

        ts->tiles = malloc(sizeof(CP_Image) * ts->tile_count);
        ts->colliders = calloc(ts->tile_count, sizeof(int));

        cJSON* tiles = cJSON_GetObjectItem(tileset, "tiles");
        int tile_count = cJSON_GetArraySize(tiles);
        for (int j = 0; j < tile_count; j++) {
            cJSON* tile = cJSON_GetArrayItem(tiles, j);
            int id = cJSON_GetObjectItem(tile, "id")->valueint;
            cJSON* props = cJSON_GetObjectItem(tile, "properties");
            cJSON* prop = cJSON_GetArrayItem(props, 0);
            if (prop && strcmp(cJSON_GetObjectItem(prop, "name")->valuestring, "iscollider") == 0) {
                ts->colliders[id] = cJSON_GetObjectItem(prop, "value")->valueint;
            }
        }

        // Load individual tile images
        for (int j = 0; j < ts->tile_count; j++) {
            if (j < sizeof(tile_paths) / sizeof(tile_paths[0])) {
                ts->tiles[j] = CP_Image_Load(tile_paths[j]);
                if (!ts->tiles[j]) {
                    printf("Failed to load tile %d: %s\n", j, tile_paths[j]);
                }
            }
            else {
                ts->tiles[j] = NULL; // Handle case where tile_count exceeds tile_paths
                printf("Warning: No tile image for ID %d\n", j);
            }
        }
    }

    cJSON* layers = cJSON_GetObjectItem(json, "layers");
    current_level.layer_count = cJSON_GetArraySize(layers);
    current_level.layers = malloc(sizeof(Layer) * current_level.layer_count);

    for (int i = 0; i < current_level.layer_count; i++) {
        cJSON* layer = cJSON_GetArrayItem(layers, i);
        Layer* l = &current_level.layers[i];  // Take address of the struct

        l->width = cJSON_GetObjectItem(layer, "width")->valueint;
        l->height = cJSON_GetObjectItem(layer, "height")->valueint;
        l->name = _strdup(cJSON_GetObjectItem(layer, "name")->valuestring);

        cJSON* data = cJSON_GetObjectItem(layer, "data");
        int data_size = cJSON_GetArraySize(data);
        l->data = malloc(sizeof(int) * data_size);

        for (int j = 0; j < data_size; j++) {
            l->data[j] = cJSON_GetArrayItem(data, j)->valueint;
        }
    }

    initializeDecoration();
    flag_init(&flag);

    cJSON_Delete(json);
    free(json_string);
}

void drawMap(void) {
    for (int l = 0; l < current_level.layer_count; l++) {
        Layer* layer = &current_level.layers[l];
        for (int y = 0; y < layer->height; y++) {
            for (int x = 0; x < layer->width; x++) {
                int tile_id = layer->data[y * layer->width + x];
                if (tile_id == 0) continue;

                Tileset* ts = &current_level.tilesets[0];
                int local_id = tile_id - 1; // Tiled uses 1-based indexing
                if (local_id < ts->tile_count && ts->tiles[local_id]) {
                    CP_Image_Draw(ts->tiles[local_id],
                        x * TILE_SIZE + TILE_SIZE / 2,
                        y * TILE_SIZE + TILE_SIZE / 2,
                        TILE_SIZE,
                        TILE_SIZE,
                        255);
                }
            }
        }
    }
}

int isTileCollider(int x, int y) {
    Layer* layer = &current_level.layers[0];
    if (x < 0 || x >= layer->width || y < 0 || y >= layer->height) return 0;

    int tile_id = layer->data[y * layer->width + x];
    if (tile_id == 0) return 0;

    Tileset* ts = &current_level.tilesets[0];
    return ts->colliders[tile_id - 1];
}

void initializeDecoration(void) {
    willows = CP_Image_Load("Assets/Willows/3.png");
    Ridges = CP_Image_Load("Assets/Ridges/4_resized.png");
    Bushes = CP_Image_Load("Assets/Bushes/5.png");
    Bushes2 = CP_Image_Load("Assets/Bushes/1.png");

    tree.image = willows;
    tree.x = 1150;
    tree.y = 170;

    ridges.image = Ridges;
    ridges.x = 530;
    ridges.y = 550;

    bushes[0].image = Bushes;
    bushes[0].x = 200;
    bushes[0].y = 222;

    bushes[1].image = Bushes2;
    bushes[1].x = 320;
    bushes[1].y = 352;

    bushes[2].image = Bushes;
    bushes[2].x = 600;
    bushes[2].y = 605;

    bushes[3].image = Bushes;
    bushes[3].x = 470;
    bushes[3].y = 605;
}

void drawDecoration(void) {
    CP_Image_Draw(tree.image, tree.x, tree.y, 398, 366, 255);
    CP_Image_Draw(ridges.image, ridges.x, ridges.y, 195, 183, 255);
    CP_Image_Draw(bushes[0].image, bushes[0].x, bushes[0].y, 100, 73, 255);
    CP_Image_Draw(bushes[1].image, bushes[1].x, bushes[1].y, 100, 73, 255);
    CP_Image_Draw(bushes[2].image, bushes[2].x, bushes[2].y, 100, 73, 255);
    CP_Image_Draw(bushes[3].image, bushes[3].x, bushes[3].y, -100, 73, 255);
    drawFlag(&flag, 1000, 500, 100, 100);
    drawFlag(&flag, 200, 500, 100, 100);
    drawFlag(&flag, 1200, 300, 100, 100);
    drawFlag(&flag, 620, 335, 100, 100);
}

void exitLevel(void) {
    for (int i = 0; i < current_level.tileset_count; i++) {
        for (int j = 0; j < current_level.tilesets[i].tile_count; j++) {
            if (current_level.tilesets[i].tiles[j]) {
                CP_Image_Free(&current_level.tilesets[i].tiles[j]);
            }
        }
        free(current_level.tilesets[i].tiles);
        free(current_level.tilesets[i].colliders);
        free(current_level.tilesets[i].tileset_path);
    }
    free(current_level.tilesets);

    for (int i = 0; i < current_level.layer_count; i++) {
        free(current_level.layers[i].data);
        free(current_level.layers[i].name);
    }
    free(current_level.layers);

    CP_Image_Free(&willows);
    CP_Image_Free(&Ridges);
    CP_Image_Free(&Bushes);
    CP_Image_Free(&Bushes2);
    for (int i = 0; i < FRAME_COUNT; i++) {
        CP_Image_Free(&flag.frame_flag[i]);
    }
}

void flag_init(Deco* flag) {
    flag->frame_flag[0] = CP_Image_Load("Assets/Flag/Flag_Frame_1.png");
    flag->frame_flag[1] = CP_Image_Load("Assets/Flag/Flag_Frame_2.png");
    flag->frame_flag[2] = CP_Image_Load("Assets/Flag/Flag_Frame_3.png");
    flag->frame_flag[3] = CP_Image_Load("Assets/Flag/Flag_Frame_4.png");
    flag->frametimer = 0.0f;
    flag->currentframe = 0;
}

void update_flag(Deco* flag, float deltatime) {
    flag->frametimer += deltatime;
    if (flag->frametimer >= FRAME_TIME) {
        flag->frametimer = 0.0f;
        flag->currentframe = (flag->currentframe + 1) % FRAME_COUNT;
    }
}

void drawFlag(Deco* flag, float x, float y, float width, float height) {
    CP_Image_Draw(flag->frame_flag[flag->currentframe], x, y, width, height, 255);
}

void drawLevel(void) {
    drawDecoration();
    drawMap();
}