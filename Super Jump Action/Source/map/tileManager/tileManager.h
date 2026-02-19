#pragma once

#define TILE_SIZE 8
#define TILE_MAX 256

#define  SCALE 4

class TileManager
{
public:

    static bool LoadTiles(const char* filename, int tileSizeX, int tileSizeY);

    static void DrawTile(int tileID, int x, int y);

    //ägëÂä÷êî
    static void SetScale(float scale);
    static float GetScale();


private:

    static int m_TileHandle[TILE_MAX];

    static int m_TileNum;

    static float m_Scale;

};
