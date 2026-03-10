#ifndef GAME_H
#define GAME_H

#include <memory>
#include <string>
#include "SaveManager.h"
#include "Swiat.h"
#include "Czlowiek.h"

class Game {
public:
    Game(int width = 15, int height = 15);
    void start();

private:
    void showSaveMenu();
    void initWorld();
    void gameLoop();

    Swiat swiat_;
    std::shared_ptr<Czlowiek> player_;
    SaveManager saveMgr_;
    std::string currentSaveName_;
};

#endif
