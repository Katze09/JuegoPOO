#include "Texts.h"

using namespace std;

Texts::Texts()
{
}

Texts::Texts(string nameFont, int size)
{
    TTF_Init();
    nameFont = "Textures/Fonts/" + nameFont + ".ttf";
    const char* textCStr = nameFont.c_str();
    font = TTF_OpenFont(textCStr, size);
    if (!font)
        cout << "Error a cargar la font" << endl;
    this->size = size;
}

Texts::~Texts()
{
}

void Texts::drawText(string text, int X, int Y, SDL_Renderer* renderer)
{
    const char* textCStr = text.c_str();
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textCStr,{255, 255, 255}); // Color: blanco
    if (!textSurface)
        cout << "Error surface" << endl;
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect destRect = {X, Y, textSurface->w, textSurface->h}; 

    SDL_RenderCopy(renderer, textTexture, nullptr, &destRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void Texts::drawText(string text, int X, int Y, SDL_Renderer* renderer, SDL_Color textColor)
{
    const char* textCStr = text.c_str();
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textCStr, textColor);
    if (!textSurface)
        cout << "Error surface" << endl;
    
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect destRect = {X, Y, textSurface->w, textSurface->h};

    SDL_RenderCopy(renderer, textTexture, nullptr, &destRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

vector<int> Texts::getTextSize(string texts)
{
    const char* text = texts.c_str();
    int textWidth, textHeight;
    TTF_SizeText(font, text, &textWidth, &textHeight);
    return {textWidth, textHeight};
}

