#pragma once

#define MAP_WIDTH  26
#define MAP_HEIGHT 8


extern int g_Map[MAP_HEIGHT][MAP_WIDTH];

bool LoadMapCSV(const char* filename);
void DrawMap();

#define TILE_SIZE 8


#define TILE_PLAYER_START 99


extern int g_PlayerStartX;
extern int g_PlayerStartY;