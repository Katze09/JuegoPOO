/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   Texts.h
 * Author: Katze
 *
 * Created on 15 de enero de 2024, 09:28
 */

#ifndef TEXTS_H
#define TEXTS_H

#include <sdl.h>
#include <string>
#include <sdl_ttf.h>
#include <iostream>

using namespace std;

class Texts 
{
public:
    Texts();
    Texts(string nameFont, int size);
    virtual ~Texts();
    void drawText(string text, int X, int Y, SDL_Renderer* renderer);
private:
    TTF_Font* font;
    int size;
};

#endif /* TEXTS_H */

