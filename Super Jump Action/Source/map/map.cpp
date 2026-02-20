#include "map.h"
#include "tileManager/tileManager.h"
#include <stdio.h>
#include "DxLib.h"

int g_Map[MAP_HEIGHT][MAP_WIDTH];

//プレイヤーの初期位置
int g_PlayerStartX = 0;
int g_PlayerStartY = 0;


//マップのロード
bool LoadMapCSV(const char* filename)
{
    FILE* fp = nullptr;

    fopen_s(&fp, filename, "r");

    if (!fp)
    {
        printfDx("File open error\n");
        return false;
    }

    // BOMスキップ
    unsigned char bom[3];
    fread(bom, 1, 3, fp);

    if (!(bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF))
    {
        fseek(fp, 0, SEEK_SET);
    }

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            if (fscanf_s(fp, "%d", &g_Map[y][x]) != 1)
            {
                printfDx("Read error y=%d x=%d\n", y, x);
                fclose(fp);
                return false;
            }

            if (g_Map[y][x] == TILE_PLAYER_START)
            {
                g_PlayerStartX = x;
                g_PlayerStartY = y;

                g_Map[y][x] = -1;
            }

            // 区切り文字スキップ
            int c = fgetc(fp);

            if (c == '\r') fgetc(fp);
        }
    }

    fclose(fp);

    printfDx("CSV Load Success\n");

    return true;
}




void DrawMap()
{
    float scale = TileManager::GetScale();

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            int id = g_Map[y][x];

            if (id < 0) continue;

            TileManager::DrawTile(
                id,
                (int)(x * TILE_SIZE * scale),
                (int)(y * TILE_SIZE * scale)
            );
        }
    }
}



