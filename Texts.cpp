/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Texts.cpp
 * Author: Katze
 * 
 * Created on 15 de enero de 2024, 09:28
 */

#include "Texts.h"

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
    SDL_Rect destRect = {X, Y, textSurface->w, textSurface->h}; // Cambia las coordenadas según tus necesidades

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

std::vector<int> Texts::getTextSize(string texts)
{
    const char* text = texts.c_str();
    int textWidth, textHeight;
    TTF_SizeText(font, text, &textWidth, &textHeight);
    return {textWidth, textHeight};
}

