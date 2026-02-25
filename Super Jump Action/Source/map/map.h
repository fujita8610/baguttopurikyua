#pragma once

//マップ関連
#define MAP_WIDTH  26
#define MAP_HEIGHT 8

extern int g_Map[MAP_HEIGHT][MAP_WIDTH];

bool LoadMapCSV(const char* filename);
bool IsWall(int mapX, int mapY);
void DrawMap();

#define TILE_SIZE 8

//プレイヤー関連
//マップ番号99
#define TILE_PLAYER_START 99

extern int g_PlayerStartX;
extern int g_PlayerStartY;


//Enemy関連
#define ENEMY_MAX 100

extern int g_EnemyStartX[ENEMY_MAX];
extern int g_EnemyStartY[ENEMY_MAX];
extern int g_EnemyCount;

//マップ番号　９７　Enemy１
#define TILE_ENEMY1_START 97