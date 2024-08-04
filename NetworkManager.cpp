// NetworkManager.cpp
#include "NetworkManager.h"
#include "Loader.h"
#include <iostream>
#include <cstring>

NetworkManager::NetworkManager() : isServer(false), serverSocket(nullptr), clientSocket(nullptr) {}

NetworkManager::~NetworkManager() {
    cleanup();
}

bool NetworkManager::init() {
    if (SDLNet_Init() < 0) {
        std::cerr << "SDLNet_Init: " << SDLNet_GetError() << std::endl;
        return false;
    }
    return true;
}

void NetworkManager::cleanup() {
    if (isServer) {
        stopServer();
    }
    else {
        disconnect();
    }
    SDLNet_Quit();
}

std::string NetworkManager::generateGameCode() {
    if (SDLNet_ResolveHost(&ip, nullptr, 0) < 0) {
        std::cerr << "SDLNet_ResolveHost: " << SDLNet_GetError() << std::endl;
        return "";
    }
    Uint32 hostIP = SDL_SwapBE32(ip.host);
    std::string ipStr = ipToString(hostIP);
    return Loader::base64_encode(ipStr).substr(0, 6); // Limitar a 6 caracteres
}

bool NetworkManager::startServer(const std::string& gameCode) {
    std::string decodedIP = Loader::base64_decode(gameCode);
    Uint32 ipHost = stringToIp(decodedIP);

    ip.host = SDL_SwapBE32(ipHost);
    ip.port = SDL_SwapBE16(12345);

    serverSocket = SDLNet_TCP_Open(&ip);
    if (!serverSocket) {
        std::cerr << "SDLNet_TCP_Open: " << SDLNet_GetError() << std::endl;
        return false;
    }

    isServer = true;
    serverThread = std::thread(&NetworkManager::serverLoop, this);
    return true;
}

bool NetworkManager::joinGame(const std::string& gameCode) {
    std::string decodedIP = Loader::base64_decode(gameCode);
    Uint32 ipHost = stringToIp(decodedIP);

    ip.host = SDL_SwapBE32(ipHost);
    ip.port = SDL_SwapBE16(12345);

    clientSocket = SDLNet_TCP_Open(&ip);
    if (!clientSocket) {
        std::cerr << "SDLNet_TCP_Open: " << SDLNet_GetError() << std::endl;
        return false;
    }
    SDLNet_TCP_Send(clientSocket, gameCode.c_str(), gameCode.length() + 1);
    return true;
}

void NetworkManager::stopServer() {
    if (isServer) {
        for (auto& client : clientSockets) {
            SDLNet_TCP_Close(client);
        }
        clientSockets.clear();
        SDLNet_TCP_Close(serverSocket);
        if (serverThread.joinable()) {
            serverThread.join();
        }
        isServer = false;
    }
}

void NetworkManager::disconnect() {
    if (clientSocket) {
        SDLNet_TCP_Close(clientSocket);
        clientSocket = nullptr;
    }
}

void NetworkManager::update() {
    if (isServer) {
        for (auto& client : clientSockets) {
            // TODO: Add code to read and handle messages from clients
        }
    }
    else if (clientSocket) {
        // TODO: Add code to read and handle messages from server
    }
}

void NetworkManager::serverLoop() {
    while (isServer) {
        TCPsocket newClient = SDLNet_TCP_Accept(serverSocket);
        if (newClient) {
            char buffer[512];
            SDLNet_TCP_Recv(newClient, buffer, 512);
            std::string clientCode(buffer);
            std::string serverCode = generateGameCode().substr(0, 6);
            if (clientCode == serverCode) {
                std::cout << "Player joined with correct code!" << std::endl;
                clientSockets.push_back(newClient);
                std::thread clientThread(&NetworkManager::handleClient, this, newClient);
                clientThread.detach();
            }
            else {
                std::cout << "Incorrect game code: " << buffer << std::endl;
                SDLNet_TCP_Close(newClient);
            }
        }
        SDL_Delay(100); // Prevent busy-wait
    }
}

void NetworkManager::handleClient(TCPsocket client) {
    char buffer[512];
    while (SDLNet_TCP_Recv(client, buffer, 512) > 0) {
        // Process received data from client
        std::cout << "Received message from client: " << buffer << std::endl;
        // TODO: Add code to handle client messages
    }
    SDLNet_TCP_Close(client);
}

std::string NetworkManager::ipToString(Uint32 ip) {
    std::string ipStr;
    for (int i = 0; i < 4; ++i) {
        ipStr.push_back((ip >> (i * 8)) & 0xFF);
    }
    return ipStr;
}

Uint32 NetworkManager::stringToIp(const std::string& ipStr) {
    Uint32 ip = 0;
    for (int i = 0; i < 4 && i < ipStr.size(); ++i) {
        ip |= (static_cast<Uint32>(ipStr[i]) << (i * 8));
    }
    return ip;
}
