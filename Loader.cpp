#include "Loader.h"

SDL_Texture* Loader::LoadTexture(const std::string& filePath, SDL_Renderer* renderer)
{
    const std::string& path = "Textures/" + filePath + ".png";
    SDL_Surface* surface = IMG_Load(path.c_str());

    if (!surface)
        std::cerr << "Hubo un problema al cargar la textura " << filePath << ".bmp, verifica si el nombre esta correcto, o si el archivo existe." << std::endl;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture)
        std::cerr << "Hubo un problema al crear la textura desde la superficie." << std::endl;

    return texture;
    /*const std::string& path = "Textures/" + filePath + ".bmp";
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture)
        cerr << "Hubo un problema al cargar la textura " << filePath << ".bmp, verifica si el nombre esta correcto, o si el archivo existe." << endl;
    return texture;*/
}

bool comp = true;

int Loader::randomNumber(int i, int j)
{
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

vector<SDL_Texture*> Loader::loadTextures(string nameFile[], SDL_Renderer* renderer, int sizeNames)
{
    SDL_Texture* texture;
    vector<SDL_Texture*> textures;
    int contTexture = 1;
    for (int i = 0; i < sizeNames; i++)
    {
        texture = LoadTexture(nameFile[i] + to_string(contTexture), renderer);
        while (texture)
        {
            textures.push_back(texture);
            contTexture++;
            texture = LoadTexture(nameFile[i] + to_string(contTexture), renderer);
        }
        contTexture = 1;
    }
    return textures;
}

Level* Loader::LoadLevel(int level, SDL_Renderer* renderer, AudioPlayer* audioPlayer)
{
    tinyxml2::XMLDocument doc;
    Level* gameLevel = new Level(renderer, audioPlayer);
    // Cargar el archivo XML
    string levelS = "Levels/Level" + to_string(level) + ".xml";
    cout << levelS << endl;
    if (doc.LoadFile(levelS.c_str()) != tinyxml2::XML_SUCCESS)
        std::cerr << "Error al cargar el archivo XML." << std::endl;

    tinyxml2::XMLElement* root = doc.RootElement();
    if (!root)
        std::cerr << "Error: No se pudo obtener el elemento raíz." << std::endl;

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
                    //int cant, double y, int movetype, bool direction
                    int cant = stoi(enemy->FirstChildElement("quantity")->GetText());
                    double y = atof(enemy->FirstChildElement("Y")->GetText());
                    int movetype = stoi(enemy->FirstChildElement("MoveType")->GetText());
                    int direction = stoi(enemy->FirstChildElement("direction")->GetText());
                    int bulletSpeed = stoi(enemy->FirstChildElement("bulletSpeed")->GetText());
                    gameLevel->setEnemyBase(cant, y, movetype, direction, bulletSpeed);
                    std::cout << "      Cantidad: " << enemy->FirstChildElement("quantity")->GetText() << std::endl;
                    std::cout << "      Y: " << enemy->FirstChildElement("Y")->GetText() << std::endl;
                    std::cout << "      Tipo de movimiento: " << enemy->FirstChildElement("MoveType")->GetText() << std::endl;
                    std::cout << "      Dirección: " << enemy->FirstChildElement("direction")->GetText() << std::endl;
                } else if (std::string(enemy->Name()) == "EnemyLaser")
                {
                    int cant = stoi(enemy->FirstChildElement("quantity")->GetText());
                    double y = atof(enemy->FirstChildElement("Y")->GetText());
                    int movetype = stoi(enemy->FirstChildElement("MoveType")->GetText());
                    int direction = stoi(enemy->FirstChildElement("direction")->GetText());
                    double moveTo = atof(enemy->FirstChildElement("moveTo")->GetText());
                    int bulletSpeed = stoi(enemy->FirstChildElement("bulletSpeed")->GetText());
                    gameLevel->setEnemyLaser(cant, y, movetype, direction, moveTo, bulletSpeed);
                    std::cout << "      Cantidad: " << enemy->FirstChildElement("quantity")->GetText() << std::endl;
                    std::cout << "      Y: " << enemy->FirstChildElement("Y")->GetText() << std::endl;
                    std::cout << "      Tipo de movimiento: " << enemy->FirstChildElement("MoveType")->GetText() << std::endl;
                    std::cout << "      Dirección: " << enemy->FirstChildElement("direction")->GetText() << std::endl;
                    std::cout << "      Mover a : " << enemy->FirstChildElement("moveTo")->GetText() << std::endl;
                } else if (std::string(enemy->Name()) == "EnemyMid")
                {
                    int cant = stoi(enemy->FirstChildElement("quantity")->GetText());
                    double x = atof(enemy->FirstChildElement("X")->GetText());
                    double y = atof(enemy->FirstChildElement("Y")->GetText());
                    double moveTo = atof(enemy->FirstChildElement("moveTo")->GetText());
                    int bulletSpeed = stoi(enemy->FirstChildElement("bulletSpeed")->GetText());
                    gameLevel->setEnemyMid(cant, x, y, moveTo, bulletSpeed);
                    std::cout << "      Cantidad: " << enemy->FirstChildElement("quantity")->GetText() << std::endl;
                    std::cout << "      X: " << enemy->FirstChildElement("X")->GetText() << std::endl;
                    std::cout << "      Y: " << enemy->FirstChildElement("Y")->GetText() << std::endl;
                    std::cout << "      Mover a : " << enemy->FirstChildElement("moveTo")->GetText() << std::endl;
                } else if (std::string(enemy->Name()) == "Obstacles")
                {
                    gameLevel->setObstacles(stoi(enemy->FirstChildElement("SpawnProbability")->GetText()));
                    std::cout << "      Probabilidad de spawn: " << enemy->FirstChildElement("SpawnProbability")->GetText() << std::endl;
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
