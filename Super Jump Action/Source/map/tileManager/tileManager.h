#pragma once

#define TILE_SIZE 8
#define TILE_MAX 256

class TileManager
{
public:

    static bool LoadTiles(const char* filename, int tileSizeX, int tileSizeY);

    static void DrawTile(int tileID, int x, int y);

private:

    static int m_TileHandle[TILE_MAX];

    static int m_TileNum;
};
