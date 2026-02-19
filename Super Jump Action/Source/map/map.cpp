#include "map.h"
#include "tileManager/tileManager.h"
#include <stdio.h>

int g_Map[MAP_HEIGHT][MAP_WIDTH];


//マップのロード
bool LoadMapCSV(const char* filename)
{
    FILE* fp = nullptr;

    fopen_s(&fp, filename, "r");

    if (fp == nullptr)
        return false;

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            fscanf_s(fp, "%d", &g_Map[y][x]);

            fgetc(fp); // カンマ or 改行読み飛ばし
        }
    }

    fclose(fp);

    return true;
}

void DrawMap()
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            int id = g_Map[y][x];

            if (id < 0) continue;

            TileManager::DrawTile(
                id,
                x * TILE_SIZE,
                y * TILE_SIZE
            );
        }
    }
}

