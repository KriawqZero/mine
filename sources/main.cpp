#include "Game/Game.hpp"

#define PROJECT_NAME "OpenGl Legacy"
#define PROJECT_VERSION "0.1a"
#define FPS_LIMIT 150
#include <thread>

int main() {
    Minecraft::Game game(1280, 720, FPS_LIMIT,
        PROJECT_NAME, PROJECT_VERSION);

    //std::thread debugConsoleThread([&game] { game.debugConsole(); });

    game.run();

    //debugConsoleThread.join();
    return 0;
}
