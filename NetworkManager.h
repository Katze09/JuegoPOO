#pragma once

#include <SDL_net.h>
#include <string>
#include <vector>
#include <thread>

class NetworkManager {
public:
    NetworkManager();
    ~NetworkManager();

    bool init();
    void cleanup();

    std::string generateGameCode();
    bool startServer(const std::string& gameCode);
    bool joinGame(const std::string& gameCode);

    void stopServer();
    void disconnect();

    void update();  // To handle incoming messages

private:
    bool isServer;
    TCPsocket serverSocket;
    TCPsocket clientSocket;
    std::vector<TCPsocket> clientSockets;
    IPaddress ip;

    std::thread serverThread;

    void serverLoop();
    void handleClient(TCPsocket client);

    std::string ipToString(Uint32 ip);
    Uint32 stringToIp(const std::string& ipStr);
};