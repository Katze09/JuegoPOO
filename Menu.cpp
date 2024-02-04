#include "Menu.h"

Loader lod;
bool selectPlayer;

Menu::Menu(SDL_Renderer* renderer)
{
    background = Background(lod.LoadTexture("Background", renderer));
    play = Button("Play", 250, 300);
    textsTile = Texts("VerminVibes1989", 120);
    textsExtra = Texts("VerminVibes1989", 20);
    player1 = Button("SinglePlayer", 95, 300);
    player2 = Button("MultiPlayer", 100, 400);
    back = Button("Back", 250, 500);
    selectPlayer = false;
}

Menu::~Menu()
{
}

int Menu::click(int x, int y)
{
    if (!selectPlayer)
    {
        if (play.isPresed(x, y))
        {
            selectPlayer = true;
        }
    } else
    {
        if (player1.isPresed(x, y))
            return 1;
        if (player2.isPresed(x, y))
            return 2;
        if (back.isPresed(x, y))
            selectPlayer = false;
    }
    return 0;
}

void Menu::hover(int x, int y)
{
    if (!selectPlayer)
    {
        play.isHover(x, y);
    } else
    {
        player1.isHover(x, y);
        player2.isHover(x, y);
        back.isHover(x, y);
    }
}

void Menu::numPlayers()
{

}

void Menu::update(float deltaTime)
{
    background.update(deltaTime);
}

void Menu::draw(SDL_Renderer* renderer)
{
    background.draw(renderer);
    textsTile.drawText("The Game", 110, 100, renderer);
    textsExtra.drawText("Copyright Katze090", 0, 780, renderer);
    if (!selectPlayer)
        play.draw(renderer);
    else
    {
        player1.draw(renderer);
        player2.draw(renderer);
        back.draw(renderer);
    }

}

Button::Button()
{
}

Button::Button(string showText, float x, float y)
{
    texts = Texts("VerminVibes1989", 80);
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

void Button::update(float deltaTime)
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

