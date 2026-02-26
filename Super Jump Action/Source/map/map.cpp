#include "map.h"
#include "DxLib.h"
#include "tileManager/tileManager.h"
#include <stdio.h>

//Debugの表示
#include "../GameDebug/GameDebug.h"

int g_Map[MAP_HEIGHT][MAP_WIDTH];

//プレイヤーの初期位置
int g_PlayerStartX = 0;
int g_PlayerStartY = 0;

//Enemy
int g_EnemyStartX[ENEMY_MAX];
int g_EnemyStartY[ENEMY_MAX];
int g_EnemyCount = 0;
int g_EnemyType[ENEMY_MAX];

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

            //プレイヤー開始位置
            if (g_Map[y][x] == TILE_PLAYER_START)
            {
                g_PlayerStartX = x;
                g_PlayerStartY = y;

                g_Map[y][x] = -1;
            }

            // 敵開始位置
            if (g_Map[y][x] == TILE_ENEMY1_START||
                g_Map[y][x] == TILE_ENEMY2_START||
                g_Map[y][x] == TILE_ENEMY3_START||
                g_Map[y][x] == TILE_ENEMY4_START||
                g_Map[y][x] == TILE_ENEMY5_START||
                g_Map[y][x] == TILE_ENEMY6_START)
            {
                g_EnemyStartX[g_EnemyCount] = x;
                g_EnemyStartY[g_EnemyCount] = y;

                // 種類保存
                g_EnemyType[g_EnemyCount] = g_Map[y][x];

                g_EnemyCount++;

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



//マップの当たり判定
bool IsWall(int mapX, int mapY)
{
    // 範囲外は壁扱い
    if (mapX < 0 || mapY < 0 || mapX >= MAP_WIDTH || mapY >= MAP_HEIGHT)
    {
        return true;
    }

    if (mapX < 0 || mapY < 0 || mapX >= MAP_WIDTH || mapY >= MAP_HEIGHT)
    {
        return true;
    }

    int tile = g_Map[mapY][mapX];

    // 当たり判定つけるタイルはここに書く
    //　例　(tile == タイル番号) return true;
    if (tile == -1) return false; // 空


    // 1985_tiles.png内の当たり判定
    if (tile == 0) return true; // 地面茶色１
    if (tile == 1) return true; // 地面茶色２
    if (tile == 3) return true; // かたい枠アリブロック
    if (tile == 5) return true; // 地面茶色レンガ１
    if (tile == 6) return true; // 地面茶色レンガ２
    if (tile == 7) return true; // かたい枠無しブロック明
    if (tile == 8) return true; // 土壁１
    if (tile == 9) return true; // 土壁２
    if (tile == 11) return true; // かたい枠アリブロック暗
    if (tile == 12) return true; // 茶色
    if (tile == 13) return true; // レンガ１
    if (tile == 14) return true; // レンガ２
    if (tile == 15) return true; // かたい枠無しブロック暗
    if (tile == 44) return true; // かたい枠アリブロック青明
    if (tile == 45) return true; // 地面青レンガ１
    if (tile == 46) return true; // 地面青レンガ２
    if (tile == 50) return true; // かたい青ブロック
    if (tile == 52) return true; // かたい枠アリブロック青暗
    if (tile == 53) return true; // 青レンガ１
    if (tile == 54) return true; // 青レンガ２
    if (tile == 56) return true; // 石地面１
    if (tile == 57) return true; // 石地面２
    if (tile == 64) return true; // 石壁１
    if (tile == 65) return true; // 石壁２
    if (tile == 68) return true; // 白レンガ地面１
    if (tile == 69) return true; // 白レンガ地面２
    if (tile == 76) return true; // 白レンガ１
    if (tile == 77) return true; // 白レンガ２
  



    return false;
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

            int drawX = (int)(x * TILE_SIZE * scale);
            int drawY = (int)(y * TILE_SIZE * scale);

            TileManager::DrawTile(
                id,
                (int)(x * TILE_SIZE * scale),
                (int)(y * TILE_SIZE * scale)
            );


            //当たり判定の表示
            if (GameDebug::IsDebug())
            {
                // タイル番号
                DrawFormatString(
                    x * TILE_SIZE * scale,
                    y * TILE_SIZE * scale,
                    //黄色
                    GetColor(255, 255, 0),
                    "%d",
                    id);

                // 当たり判定BOX
                if (IsWall(x, y))
                {
                    DrawBox(
                        drawX,
                        drawY,
                        drawX + TILE_SIZE * scale,
                        drawY + TILE_SIZE * scale,
                        //緑
                        GetColor(0, 255, 0),
                        FALSE);
                }

            }
        }
    }

   
}



