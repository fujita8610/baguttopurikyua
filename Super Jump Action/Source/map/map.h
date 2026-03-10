#pragma once

//マップの縦横
#define MAP_WIDTH  100
#define MAP_HEIGHT 100

extern int g_Map[MAP_HEIGHT][MAP_WIDTH];

bool LoadMapCSV(const char* filename);
bool IsWall(int mapX, int mapY);
void DrawMap(float camX, float camY);

#define TILE_SIZE 8

// 空白タイル
#define TILE_EMPTY -1

//透明ブロック
#define TILE_INVINSIBLE -2

//プレイヤー関連
//マップ番号99　プレイヤー
#define TILE_PLAYER_START 99

extern int g_PlayerStartX;
extern int g_PlayerStartY;


//Enemy関連
#define ENEMY_MAX 100

//マップ番号　９７　Enemy１キノコ
#define TILE_ENEMY1_START 97

//マップ番号　９６　Enemy２
#define TILE_ENEMY2_START 96

//マップ番号　９５　Enemy３
#define TILE_ENEMY3_START 95

//マップ番号　９４　Enemy４
#define TILE_ENEMY4_START 94

//マップ番号　９３　Enemy５
#define TILE_ENEMY5_START 93

//マップ番号　９２　Enemy６
#define TILE_ENEMY6_START 92

extern int g_EnemyStartX[ENEMY_MAX];
extern int g_EnemyStartY[ENEMY_MAX];
extern int g_EnemyCount;
extern int g_EnemyType[ENEMY_MAX];

//ボス関連

//マップ番号９９９　チュートリアルボス
#define TILE_TUTORIAL_BOSS 999

extern int g_BossStartX;
extern int g_BossStartY;
extern bool g_BossExist;

