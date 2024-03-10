#ifndef TEXTS_H
#define TEXTS_H

#include <sdl.h>
#include <string>
#include <sdl_ttf.h>
#include <iostream>
#include <vector>

class Texts 
{
public:
    Texts();
    Texts(std::string nameFont, int size);
    virtual ~Texts();
    void drawText(std::string text, int X, int Y, SDL_Renderer* renderer);
    void drawText(std::string text, int X, int Y, SDL_Renderer* renderer, SDL_Color textColor);
    std::vector<int>getTextSize(std::string texts);
private:
    TTF_Font* font;
    int size;
};

#endif /* TEXTS_H */

