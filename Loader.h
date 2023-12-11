#ifndef LOADER_H
#define LOADER_H

#include <iostream>
#include <windows.h>
#include <string>
#include <tchar.h>

using namespace std;

class Loader
{
public:
    HBITMAP LoadSprite(const std::string& name);
};
#endif /* LOADER_H */

