#include "Loader.h"

HBITMAP Loader::LoadSprite(const std::string& name)
{
    const std::string& path = "Textures/" + name + ".bmp";
    return (HBITMAP)LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}
