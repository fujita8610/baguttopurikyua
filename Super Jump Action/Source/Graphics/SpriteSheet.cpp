#include "SpriteSheet.h"

SpriteSheet::SpriteSheet()
{
    total = 0;
}

bool SpriteSheet::Load(const char* path,
    int divX,
    int divY,
    int frameW,
    int frameH)
{
    total = divX * divY;

    if (LoadDivGraph(path,
        total,
        divX,
        divY,
        frameW,
        frameH,
        handle) == -1)
    {
        return false;
    }

    return true;
}

int SpriteSheet::Get(int index) const
{
    if (index < 0 || index >= total)
        return -1;

    return handle[index];
}

int SpriteSheet::GetTotal() const
{
    return total;
}
