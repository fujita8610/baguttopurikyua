#include "tileManager.h"
#include "DxLib.h"

int TileManager::m_TileHandle[TILE_MAX];
int TileManager::m_TileNum = 0;


bool TileManager::LoadTiles(const char* filename, int tileSizeX, int tileSizeY)
{
    int AllNumX;
    int AllNumY;

    int ImageHandle = LoadGraph("Data/Map/1985_tiles.png");

    if (ImageHandle == -1)
        return false;

    int SizeX, SizeY;

    GetGraphSize(ImageHandle, &SizeX, &SizeY);

    AllNumX = SizeX / tileSizeX;
    AllNumY = SizeY / tileSizeY;

    m_TileNum = AllNumX * AllNumY;

    LoadDivGraph(
        "Data/Map/1985_tiles.png",
        m_TileNum,
        AllNumX,
        AllNumY,
        tileSizeX,
        tileSizeY,
        m_TileHandle
    );

    return true;
}


void TileManager::DrawTile(int tileID, int x, int y)
{
    if (tileID < 0) return;
    if (tileID >= m_TileNum) return;

    DrawGraph(x, y, m_TileHandle[tileID], TRUE);
}
