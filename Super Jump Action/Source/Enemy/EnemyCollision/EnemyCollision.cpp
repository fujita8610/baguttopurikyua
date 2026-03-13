#include "EnemyCollision.h"

bool EnemyCollision::CheckRect(const Rect& a, const Rect& b)
{
    if (a.right < b.left) return false;
    if (b.right < a.left) return false;
    if (a.bottom < b.top) return false;
    if (b.bottom < a.top) return false;

    return true;
}