#include "Loader.h"

using namespace std;

SDL_Texture* Loader::loadTexture(const std::string& filePath, SDL_Renderer* renderer)
{
    const std::string& path = "Textures/" + filePath + ".png";
    SDL_Surface* surface = IMG_Load(path.c_str());

    if (!surface)
        std::cerr << "Hubo un problema al cargar la textura " << filePath << ".png, verifica si el nombre esta correcto, o si el archivo existe." << std::endl;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture)
        std::cerr << "Hubo un problema al crear la textura desde la superficie." << std::endl;

    return texture;
}

static bool comp = true;

int Loader::randomNumber(int i, int j)
{
    j--;
    auto now = std::chrono::system_clock::now();
    auto seed = 0;
    if (comp)
        seed = static_cast<int> (std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count());
    else
        seed = static_cast<int> (std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count());
    comp = !comp;
    auto independentClock = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    seed += static_cast<int> (independentClock);
    std::random_device rd;
    seed += rd();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(i, j);
    return distribution(generator);
}

vector<SDL_Texture*> Loader::loadTextures(std::string nameFile[], SDL_Renderer* renderer, int sizeNames)
{
    SDL_Texture* texture;
    std::vector<SDL_Texture*> textures;
    int contTexture = 1;
    for (int i = 0; i < sizeNames; i++)
    {
        texture = loadTexture(nameFile[i] + to_string(contTexture), renderer);
        while (texture)
        {
            textures.push_back(texture);
            contTexture++;
            texture = loadTexture(nameFile[i] + to_string(contTexture), renderer);
        }
        contTexture = 1;
    }
    return textures;
}

void Loader::updateLeaderBoard(string name, int score, int deaths, string nameTodelete, int numPlayers)
{
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile("Levels/Leaderboard.xml") != tinyxml2::XML_SUCCESS)
    {
        std::cerr << "Error al cargar el archivo XML." << std::endl;
        return;
    }

    tinyxml2::XMLElement* root = doc.RootElement();
    if (!root)
    {
        std::cerr << "Error: No se pudo obtener el elemento raíz." << std::endl;
        return;
    }

    tinyxml2::XMLElement* playerList = nullptr;
    if (numPlayers < 2)
        playerList = root->FirstChildElement("SinglePlayer");
    else 
        playerList = root->FirstChildElement("MultiPlayer");

    if (!playerList) 
    {
        std::cerr << "Error: No se pudo encontrar el elemento de la lista de jugadores." << std::endl;
        return;
    }

    // Buscar el elemento a eliminar y eliminarlo
    tinyxml2::XMLElement* playerToDelete = playerList->FirstChildElement("Player");
    while (playerToDelete) 
    {
        if (playerToDelete->FirstChildElement("name")->GetText() == nameTodelete) 
        {
            playerList->DeleteChild(playerToDelete);
            break;
        }
        playerToDelete = playerToDelete->NextSiblingElement("Player");
    }

    // Agregar el nuevo elemento
    tinyxml2::XMLElement* newPlayer = doc.NewElement("Player");
    tinyxml2::XMLElement* playerName = doc.NewElement("name");
    playerName->SetText(name.c_str());
    newPlayer->InsertEndChild(playerName);

    tinyxml2::XMLElement* playerScore = doc.NewElement("score");
    playerScore->SetText(score);
    newPlayer->InsertEndChild(playerScore);

    tinyxml2::XMLElement* playerDeaths = doc.NewElement("deaths");
    playerDeaths->SetText(deaths);
    newPlayer->InsertEndChild(playerDeaths);

    playerList->InsertEndChild(newPlayer);

    // Guardar el documento modificado
    if (doc.SaveFile("Levels/Leaderboard.xml") != tinyxml2::XML_SUCCESS) 
    {
        std::cerr << "Error al guardar el archivo XML modificado." << std::endl;
        return;
    }

    std::cout << "XML modificado y guardado exitosamente." << std::endl;
}

vector<string> Loader::loadLeaderBoard(int numPlayers)
{
    vector<string> learboard;
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile("Levels/Leaderboard.xml") != tinyxml2::XML_SUCCESS)
    {
        std::cerr << "Error al cargar el archivo XML." << std::endl;
        return learboard;
    }

    tinyxml2::XMLElement* root = doc.RootElement();
    if (!root)
    {
        std::cerr << "Error: No se pudo obtener el elemento raíz." << std::endl;
        return learboard;
    }

    if (numPlayers < 2)
    {
        tinyxml2::XMLElement* singleplayer = root->FirstChildElement("SinglePlayer");
        for (tinyxml2::XMLElement* players = singleplayer->FirstChildElement(); players; players = players->NextSiblingElement())
        {
            learboard.push_back(players->FirstChildElement("name")->GetText());
            learboard.push_back(players->FirstChildElement("score")->GetText());
            learboard.push_back(players->FirstChildElement("deaths")->GetText());
        }
    } else
    {
        tinyxml2::XMLElement* multiplayer = root->FirstChildElement("MultiPlayer");
        for (tinyxml2::XMLElement* players = multiplayer->FirstChildElement(); players; players = players->NextSiblingElement())
        {
            learboard.push_back(players->FirstChildElement("name")->GetText());
            learboard.push_back(players->FirstChildElement("score")->GetText());
            learboard.push_back(players->FirstChildElement("deaths")->GetText());
        }
    }
    return learboard;
}

class Level* Loader::loadLevel(int level, SDL_Renderer* renderer, AudioPlayer** audioPlayer)
{
    tinyxml2::XMLDocument doc;
    Level* gameLevel = new Level(renderer, audioPlayer);
    // Cargar el archivo XML
    string levelS = "Levels/Level" + to_string(level) + ".xml";
    cout << levelS << endl;
    if (doc.LoadFile(levelS.c_str()) != tinyxml2::XML_SUCCESS)
    {
        std::cerr << "Error al cargar el archivo XML." << std::endl;
        return nullptr;
    }

    tinyxml2::XMLElement* root = doc.RootElement();
    if (!root)
    {
        std::cerr << "Error: No se pudo obtener el elemento raíz." << std::endl;
        return nullptr;
    }

    int contParts = 0;
    // Iterar a través de los elementos hijos
    for (tinyxml2::XMLElement* part = root->FirstChildElement(); part; part = part->NextSiblingElement())
    {
        std::cout << "Parte: " << part->Name() << std::endl;
        for (tinyxml2::XMLElement* enemys = part->FirstChildElement(); enemys; enemys = enemys->NextSiblingElement())
        {
            std::cout << "  Enemigos: " << enemys->Name() << std::endl;
            for (tinyxml2::XMLElement* enemy = enemys->FirstChildElement(); enemy; enemy = enemy->NextSiblingElement())
            {
                std::cout << "    Tipo de enemigo: " << enemy->Name() << std::endl;
                if (std::string(enemy->Name()) == "EnemyBase")
                {
                    //int cant, float y, int movetype, bool direction
                    int cant = stoi(enemy->FirstChildElement("quantity")->GetText());
                    float y = atof(enemy->FirstChildElement("Y")->GetText());
                    int movetype = stoi(enemy->FirstChildElement("MoveType")->GetText());
                    int direction = stoi(enemy->FirstChildElement("direction")->GetText());
                    int bulletSpeed = stoi(enemy->FirstChildElement("bulletSpeed")->GetText());
                    gameLevel->setEnemyBase(cant, y, movetype, direction, bulletSpeed);
                } else if (std::string(enemy->Name()) == "EnemyLaser")
                {
                    int cant = stoi(enemy->FirstChildElement("quantity")->GetText());
                    float y = atof(enemy->FirstChildElement("Y")->GetText());
                    int movetype = stoi(enemy->FirstChildElement("MoveType")->GetText());
                    int direction = stoi(enemy->FirstChildElement("direction")->GetText());
                    float moveTo = atof(enemy->FirstChildElement("moveTo")->GetText());
                    int bulletSpeed = stoi(enemy->FirstChildElement("bulletSpeed")->GetText());
                    gameLevel->setEnemyLaser(cant, y, movetype, direction, moveTo, bulletSpeed);
                }
                else if (std::string(enemy->Name()) == "EnemyAngry")
                {
                    int cant = stoi(enemy->FirstChildElement("quantity")->GetText());
                    float y = atof(enemy->FirstChildElement("Y")->GetText());
                    int direction = stoi(enemy->FirstChildElement("direction")->GetText());
                    int bulletSpeed = stoi(enemy->FirstChildElement("bulletSpeed")->GetText());
                    gameLevel->setEnemyAngry(cant, y, direction, bulletSpeed);
                }
                else if (string(enemy->Name()) == "EnemyKamikaze")
                {
                    int cant = stoi(enemy->FirstChildElement("quantity")->GetText());
                    float x = atof(enemy->FirstChildElement("X")->GetText());
                    float y = atof(enemy->FirstChildElement("Y")->GetText());
                    float speed = 0;
                    tinyxml2::XMLElement* speedE = enemy->FirstChildElement("speed");
                    if (speedE)
                        speed = atof(speedE->GetText());
                    if(speed > 0)
                        gameLevel->setEnemyKamikaze(cant, x, y, speed);
                    else
                        gameLevel->setEnemyKamikaze(cant, x, y);
                }
                else if (string(enemy->Name()) == "EnemyStar")
                {
                    float y = atof(enemy->FirstChildElement("Y")->GetText());
                    int movetype = stoi(enemy->FirstChildElement("MoveType")->GetText());
                    int direction = stoi(enemy->FirstChildElement("direction")->GetText());
                    float moveTo = atof(enemy->FirstChildElement("moveTo")->GetText());
                    int bulletSpeed = stoi(enemy->FirstChildElement("bulletSpeed")->GetText());
                    gameLevel->setEnemyStar(y, movetype, direction, moveTo, bulletSpeed);
                }
                else if (std::string(enemy->Name()) == "EnemyMid")
                {
                    float x = atof(enemy->FirstChildElement("X")->GetText());
                    float y = atof(enemy->FirstChildElement("Y")->GetText());
                    float moveTo = atof(enemy->FirstChildElement("moveTo")->GetText());
                    int bulletSpeed = stoi(enemy->FirstChildElement("bulletSpeed")->GetText());
                    gameLevel->setEnemyMid(x, y, moveTo, bulletSpeed);
                }
                else if (std::string(enemy->Name()) == "EnemyMidGuide")
                {
                    float x = atof(enemy->FirstChildElement("X")->GetText());
                    float y = atof(enemy->FirstChildElement("Y")->GetText());
                    float moveTo = atof(enemy->FirstChildElement("moveTo")->GetText());
                    int bulletSpeed = stoi(enemy->FirstChildElement("bulletSpeed")->GetText());
                    gameLevel->setEnemyMidGuide(x, y, moveTo, bulletSpeed);
                }
                else if (std::string(enemy->Name()) == "EnemyBoss")
                {
                    float x = atof(enemy->FirstChildElement("X")->GetText());
                    float y = atof(enemy->FirstChildElement("Y")->GetText());
                    float moveTo = atof(enemy->FirstChildElement("moveTo")->GetText());
                    int bulletSpeed = stoi(enemy->FirstChildElement("bulletSpeed")->GetText());
                    gameLevel->setEnemyBoss(x, y, moveTo, bulletSpeed, 0);
                }
                else if (std::string(enemy->Name()) == "EnemySecondBoss")
                {
                    float x = atof(enemy->FirstChildElement("X")->GetText());
                    float y = atof(enemy->FirstChildElement("Y")->GetText());
                    float moveTo = atof(enemy->FirstChildElement("moveTo")->GetText());
                    int bulletSpeed = stoi(enemy->FirstChildElement("bulletSpeed")->GetText());
                    gameLevel->setEnemyBoss(x, y, moveTo, bulletSpeed, 1);
                }
                else if (std::string(enemy->Name()) == "Obstacles")
                {
                    gameLevel->setObstacles(stoi(enemy->FirstChildElement("SpawnProbability")->GetText()));
                    gameLevel->setPowerUps(stoi(enemy->FirstChildElement("SpawnProbabilityPowerUp")->GetText()));
                }
            }
        }

        gameLevel->numParts++;
        gameLevel->enemies.push_back(std::vector<EnemyBase*>());
        contParts++;
    }
    gameLevel->numParts = 0;
    gameLevel->setMaxNumParts(contParts);
    return gameLevel;
}

static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string Loader::base64_encode(const std::string& in)
{
    std::string out;
    int val = 0, valb = -6;
    for (unsigned char c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back(base64_chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) out.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4) out.push_back('=');
    return out;
}

std::string Loader::base64_decode(const std::string& in)
{
    std::string out;
    std::vector<int> T(256, -1);
    for (int i = 0; i < 64; i++) T[base64_chars[i]] = i;
    int val = 0, valb = -8;
    for (unsigned char c : in) 
    {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
}

Uint32 Loader::getElapsedTime(Uint32 start) 
{
    return (SDL_GetTicks() - start) / 1000; 
}