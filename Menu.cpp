#include "Menu.h"

Loader lod;

Menu::Menu(SDL_Renderer* renderer)
{
    background = Background(lod.LoadTexture("Background", renderer));
    play = Button("Play", 260, 300);
    textsTile = Texts("8-bit ArcadeIn", 120);
}

Menu::~Menu()
{
}

int Menu::click(int x, int y)
{
    if (play.isPresed(x, y))
        return 1;
    return 0;
}

void Menu::hover(int x, int y)
{
    play.isHover(x, y);
}

void Menu::update(double deltaTime)
{
    background.update(deltaTime);
}

void Menu::draw(SDL_Renderer* renderer)
{
    background.draw(renderer);
    textsTile.drawText("The Game", 130, 100, renderer);
    play.draw(renderer);
}

Button::Button()
{
}

Button::Button(string showText, double x, double y)
{
    texts = Texts("8-bit ArcadeIn", 80);
    this->showText = showText;
    hover = false;
    X1 = x;
    Y1 = y;
    vector<int> sizeText = texts.getTextSize(showText);
    X2 = x + sizeText[0] + 10;
    Y2 = y + sizeText[1] + 10;
}

Button::~Button()
{
}

bool Button::isPresed(int x, int y)
{
    return ((X1 - 10) < x && X2 > x && Y1 < y && Y2 > y);
}

void Button::isHover(int x, int y)
{
    if ((X1 - 10) < x && X2 > x && Y1 < y && Y2 > y)
        hover = true;
    else
        hover = false;
}

void Button::update(double deltaTime)
{
}

void Button::draw(SDL_Renderer* renderer)
{
    if (!hover)
        texts.drawText(showText, X1, Y1, renderer);
    else
    {
        SDL_Color color = {0, 82, 234};
        texts.drawText(showText, X1, Y1, renderer, color);
    }
}

