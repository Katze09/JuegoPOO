#include "Menu.h"

Loader lod;
bool selectPlayer;

Menu::Menu(SDL_Renderer* renderer)
{
    background = Background(lod.LoadTexture("Background", renderer));
    int fontSize = 80;
    play = Button("Play", 250, 300, fontSize);
    textsTile = Texts("VerminVibes1989", 120);
    textsExtra = Texts("VerminVibes1989", 20);
    player1 = Button("SinglePlayer", 95, 300, fontSize);
    player2 = Button("MultiPlayer", 100, 400, fontSize);
    back = Button("Back", 250, 500, fontSize);
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

Shop::Shop(){}

Shop::Shop(SDL_Renderer* renderer)
{
    background = Background(lod.LoadTexture("Background", renderer));
    //play = Button("Play", 250, 300);
    textsTile = Texts("VerminVibes1989", 120);
    textsMid = Texts("VerminVibes1989", 60);
    textsExtra = Texts("VerminVibes1989", 30);
    int fontSize = 40;
    int x = 100;
    for (int i = 0; i < 3; i++)
    {
        itemsButton[i] = Button("Buy", x, 400, fontSize);
        //items[i] = Item(lod.LoadTexture("PowerUpDoubleP1",renderer), 0, 500, x, 300, 70,70);
        x += 220;
    }
    finishShop = Button("End Shopping", 230, 700, fontSize);
    endShop = false;
    
    itemTextures[0] = lod.LoadTexture("PowerUpDouble1", renderer);
    itemTextures[1] = lod.LoadTexture("PowerUpDoubleP1", renderer);
    itemTextures[2] = lod.LoadTexture("Shield1", renderer);
    itemTextures[3] = lod.LoadTexture("SpecialAttack", renderer);
    itemTextures[4] = lod.LoadTexture("PowerUpShot1", renderer);
}

Shop::~Shop()
{
}

void Shop::startShopping(int point, Player* player[], int numPlayers)
{
    this->player = player;
    this->numPlayers = numPlayers;
    totalPoints = point;
    endShop = false;
    int itemsSelect[3];
    int x = 100;
    for (int i = 0; i < 3; i++)
    {
        int ran;
        bool isInArray;
        do
        {
            ran = lod.randomNumber(0, 5);
            isInArray = false;
            for (int j = 0; j < i; j++)
                if (ran == itemsSelect[j])
                {
                    isInArray = true;
                    break;
                }
        } while (isInArray);
        itemsSelect[i] = ran;
        items[i] = Item(itemTextures[ran], ran, 300, x, 300, 70, 70);
        x += 220;
    }

}

void Shop::endShopping()
{
    endShop = true;
}

int Shop::click(int x, int y)
{

    /*if (!selectPlayer)
    {
        if (play.isPresed(x, y))
        {
            selectPlayer = true;
        }
    }
    else
    {
        if (player1.isPresed(x, y))
            return 1;
        if (player2.isPresed(x, y))
            return 2;
        if (back.isPresed(x, y))
            selectPlayer = false;
    }*/
    if (finishShop.isPresed(x, y))
        endShopping();
    return 0;
}

void Shop::hover(int x, int y)
{
    for (int i = 0;i < 3;i++)
        itemsButton[i].isHover(x, y);
    finishShop.isHover(x, y);
}

void Shop::update(float deltaTime)
{
    background.update(deltaTime);
}

void Shop::draw(SDL_Renderer* renderer)
{
    background.draw(renderer);
    textsTile.drawText("Item Shop", 110, 100, renderer);
    textsMid.drawText("Score: " + std::to_string(totalPoints), 210, 220, renderer);
    for (int i = 0; i < 3; i++)
    {
        itemsButton[i].draw(renderer);
        textsExtra.drawText("Cost: " + std::to_string(items[i].getCost()), itemsButton[i].getX() - 30, itemsButton[i].getY() + 50, renderer);
        items[i].draw(renderer);
    }
    finishShop.draw(renderer);
}

Item::Item(){}

Item::Item(SDL_Texture* texture, int type, int cost, float X, float Y, int WIDTH, int HEIGHT)
{
    this->texture = texture;
    //SDL_QueryTexture(texture, NULL, NULL, &WIDTH, &HEIGHT);
    this->WIDTH = WIDTH;
    this->HEIGHT = HEIGHT;
    this->X = X;
    this->Y = Y;
    this->type = type;
    this->cost = cost;
}

void Item::update(float deltaTime){}

void Item::draw(SDL_Renderer* renderer)
{
    SDL_Rect destRect = { static_cast<int> (X), static_cast<int> (Y), WIDTH, HEIGHT };
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
}

Button::Button()
{
}

Button::Button(string showText, float x, float y, int fontSize)
{
    texts = Texts("VerminVibes1989", fontSize);
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

