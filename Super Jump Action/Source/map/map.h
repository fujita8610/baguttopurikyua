#pragma once

#define MAP_WIDTH  26
#define MAP_HEIGHT 8


extern int g_Map[MAP_HEIGHT][MAP_WIDTH];

bool LoadMapCSV(const char* filename);
void DrawMap();

#define TILE_SIZE 8
