#pragma once

#define MAP_WIDTH  100
#define MAP_HEIGHT 15

extern int g_Map[MAP_HEIGHT][MAP_WIDTH];

bool LoadMapCSV(const char* filename);
void DrawMap();

#define TILE_SIZE 8
