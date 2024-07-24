#include "Menu.h"

using namespace std;

Loader lod;

Menu::Menu(SDL_Renderer* renderer)
{
    background = Background(lod.LoadTexture("Background", renderer));
    int fontSize = 80;
    play = Button("Play", 250, 300, fontSize);
    instructions = Button("Instructions", 100, 400, fontSize);
    options = Button("Options", 190, 500, fontSize);
    textsTile = Texts("VerminVibes1989", 120);
    textsMid = Texts("VerminVibes1989", 70);
    textsLittle = Texts("VerminVibes1989", 45);
    textsExtra = Texts("VerminVibes1989", 20);
    player1 = Button("SinglePlayer", 95, 300, fontSize);
    player2 = Button("MultiPlayer", 100, 400, fontSize);
    back = Button("Back", 250, 500, fontSize);
    backIns = Button("Back", 100, 650, fontSize);
    backOpti = Button("Back", 100, 650, fontSize);
    next = Button("Next", 450, 650, fontSize);
    selectPlayer = false;
    instruc = false;
    opti = false;
    nextBool = false;
}

Menu::~Menu()
{
}

int Menu::click(int x, int y)
{
    if (selectPlayer)
    {
        if (player1.isPresed(x, y))
            return 1;
        if (player2.isPresed(x, y))
            return 2;
        if (back.isPresed(x, y))
            selectPlayer = false;
    }
    if (!selectPlayer && !instruc && !opti)
    {
        if (play.isPresed(x, y))
            selectPlayer = true;
        if (instructions.isPresed(x, y))
            instruc = true;
        if (options.isPresed(x, y))
            opti = true;
    } 
    if (instruc)
    {
        if(backIns.isPresed(x , y) && !nextBool)
            instruc = false;
        if (backIns.isPresed(x, y) && nextBool)
            nextBool = false;
        if (next.isPresed(x, y) && !nextBool)
            nextBool = true;
    }
    if (opti)
    {
        if (backOpti.isPresed(x, y))
            opti = false;
    }
    return 0;
}

void Menu::hover(int x, int y)
{
    if (!selectPlayer && !instruc && !opti)
    {
        play.isHover(x, y);
        instructions.isHover(x, y);
        options.isHover(x, y);
    } 
    if (instruc)
    {
        backIns.isHover(x, y);
        if(!nextBool)
            next.isHover(x, y);
    }
    if(selectPlayer)
    {
        player1.isHover(x, y);
        player2.isHover(x, y);
        back.isHover(x, y);
    }
    if (opti)
    {
        backOpti.isHover(x, y);
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
    if (!selectPlayer && !instruc && !opti)
    {
        play.draw(renderer);
        instructions.draw(renderer);
        options.draw(renderer);
    }
    if (selectPlayer)
    {
        player1.draw(renderer);
        player2.draw(renderer);
        back.draw(renderer);
    }
    if(instruc)
    {
        if (!nextBool)
        {
            textsMid.drawText("Player 1", 220, 220, renderer);
            textsMid.drawText("Movement", 205, 300, renderer);
            textsMid.drawText("W", 320, 350, renderer);
            textsMid.drawText("A S D", 260, 400, renderer);
            textsLittle.drawText("Space - Shot", 200, 500, renderer);
            textsLittle.drawText("E - Special Attack", 150, 550, renderer);
            textsLittle.drawText("Q - Shield Item", 180, 600, renderer);
            next.draw(renderer);
        }
        else 
        {
            textsMid.drawText("Player 2", 220, 220, renderer);
            textsMid.drawText("Movement", 205, 300, renderer);
            textsMid.drawText("U", 320, 350, renderer);
            textsMid.drawText("H J K", 260, 400, renderer);
            textsLittle.drawText("Shift - Shot", 200, 500, renderer);
            textsLittle.drawText("I - Special Attack", 150, 550, renderer);
            textsLittle.drawText("Y - Shield Item", 180, 600, renderer);
        }
        backIns.draw(renderer);
    } 
    if (opti)
    {

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

void Shop::startShopping(int score, Player* player[], int numPlayers)
{
    this->player = player;
    this->numPlayers = numPlayers;
    this->score = score;
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
        items[i] = Item(itemTextures[ran], ran, itemCost[ran], x, 300, 70, 70);
        x += 220;
    }

}

void Shop::endShopping()
{
    for (int i = 0; i < 5; i++)
        itemCost[i] += itemCost[i] * 0.1;
    for (int i = 0; i < 3; i++)
    {
        itemsButton[i].setTextColor({ 255, 255, 255 });
        itemsButton[i].setText("Buy");
    }
    endShop = true;
}

int Shop::click(int x, int y)
{

    for (int i = 0; i < 3; i++)
        if (itemsButton[i].isPresed(x, y) && score >= items[i].getCost() && !items[i].sold)
        {
            for (int p = 0; p < numPlayers; p++)
                player[p]->setItemEffect(items[i].getType());
            score -= items[i].getCost();
            itemsButton[i].setText("Sold");
            items[i].sold = true;
            itemsButton[i].setTextColor({ 136, 136, 136 });
            itemsButton[i].isHover(-10, -10);
        }
    if (finishShop.isPresed(x, y))
        endShopping();
    return 0;
}

void Shop::hover(int x, int y)
{
    for (int i = 0;i < 3;i++)
        if(!items[i].sold)
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
    textsMid.drawText("Score: " + std::to_string(score), 210, 220, renderer);
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

Leaderboard::Leaderboard() {}

Leaderboard::Leaderboard(SDL_Renderer* renderer)
{
    background = Background(lod.LoadTexture("Background", renderer));
    textsTile = Texts("VerminVibes1989", 90);
    textsMid = Texts("VerminVibes1989", 60);
    textsExtra = Texts("VerminVibes1989", 40);
    accept = Button("Continue", 200, 720, 70);
}

Leaderboard::~Leaderboard()
{
}

int Leaderboard::click(int x, int y)
{
    if (accept.isPresed(x, y))
    {
        if (!end && namePlayer.length() > 2)
        {
            string nameTodelete = "";
            if (sizeLeaderboard >= 5)
                nameTodelete = leaderNames[indexLeader[4]];
            lod.updateLeaderBoard(namePlayer, score, deaths, nameTodelete, numPlayers);
            sizeLeaderboard = 0;
            loadLeaderboard(numPlayers);
            accept.setText("Go To Menu");
            end = true;
        } else if(end)
        {
            
        }
    }
    return 0;
}

void Leaderboard::hover(int x, int y)
{
    accept.isHover(x, y);
}

void Leaderboard::loadLeaderboard(int numPlayers)
{
    vector<string> leader = lod.loadLeaderBoard(numPlayers);
    this->numPlayers = numPlayers;
    int tempScore[5];
    for (int i = 0; i < leader.size(); i+=3)
    {
        leaderNames[sizeLeaderboard] = leader[i];
        leaderScores[sizeLeaderboard] = atoi(leader[i + 1].c_str());
        leaderDeaths[sizeLeaderboard] = atoi(leader[i + 2].c_str());
        tempScore[sizeLeaderboard] = leaderScores[sizeLeaderboard] - (leaderScores[sizeLeaderboard] * (leaderDeaths[sizeLeaderboard] * 0.0001) * 5);
        indexLeader[sizeLeaderboard] = sizeLeaderboard;
        sizeLeaderboard++;
    }

    std::sort(indexLeader, indexLeader + sizeLeaderboard, [&](int a, int b) { return tempScore[a] > tempScore[b]; });
}

void Leaderboard::update(float deltaTime)
{
    background.update(deltaTime);
    accept.update(deltaTime);
}

void Leaderboard::draw(SDL_Renderer* renderer)
{
    background.draw(renderer);
    textsTile.drawText("Leaderboard", 80, 50, renderer);
    textsMid.drawText("Score: " + std::to_string(score), 180, 150, renderer);
    textsMid.drawText("Deaths: " + std::to_string(deaths), 180, 200, renderer);
    textsMid.drawText("Player: " + namePlayer, 50, 620, renderer);
    textsExtra.drawText("Player Name", 20, 300, renderer);
    textsExtra.drawText("Score", 350, 300, renderer);
    textsExtra.drawText("Deaths", 530, 300, renderer);
    int y = 350;
    for (int i = 0; i < sizeLeaderboard; i++)
    {
        textsExtra.drawText(to_string(i + 1) + ". " + leaderNames[indexLeader[i]], 30, y, renderer);
        textsExtra.drawText(to_string(leaderScores[indexLeader[i]]), 360, y, renderer);
        textsExtra.drawText(to_string(leaderDeaths[indexLeader[i]]), 550, y, renderer);
        y += 50;
    }
    accept.draw(renderer);
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
    textcolor = {255, 255, 255};
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
        texts.drawText(showText, X1, Y1, renderer, textcolor);
    else
        texts.drawText(showText, X1, Y1, renderer, { 0, 82, 234 });
}
