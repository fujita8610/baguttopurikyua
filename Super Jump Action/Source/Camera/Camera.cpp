#include "DxLib.h"
#include "../System/Config.h"
#include "Camera.h"
#include "../Player/Player.h"

static float camX, camY;

void InitCamera(int targetX, int targetY)
{
    camX = targetX - SCREEN_WIDTH / 2.0f;
    camY = targetY - SCREEN_HEIGHT / 2.0f;

    if (camX < 0) camX = 0;
    if (camY < 0) camY = 0;
}

void UpdateCamera(int targetX, int targetY)
{
    int targetCamX = targetX - SCREEN_WIDTH / 2;
    int targetCamY = targetY - SCREEN_HEIGHT / 2;

    const float followSpeed = 0.07f;
    camX += (targetCamX - camX) * followSpeed;
    camY += (targetCamY - camY) * followSpeed;
}

int GetCameraX() { return camX; }
int GetCameraY() { return camY; }