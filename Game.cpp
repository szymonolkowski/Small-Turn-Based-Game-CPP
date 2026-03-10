#include "Game.h"
#include "Swiat.h"
#include "Czlowiek.h"
#include "Antylopa.h"
#include "Owca.h"
#include "Wilk.h"
#include "Lis.h"
#include "Zolw.h"
#include "CyberOwca.h"
#include "Trawa.h"
#include "Mlecz.h"
#include "Guarana.h"
#include "WilczeJagody.h"
#include "BarszczSosnowskiego.h"

#include <iostream>
#include <ctime>
#include <cctype>
#include <conio.h>

#ifdef _WIN32
  #include <windows.h>
#endif

Game::Game(int width, int height)
  : swiat_(width, height),
    saveMgr_("saves.idx")
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Game::start() {
    showSaveMenu();
    gameLoop();
}

void Game::showSaveMenu() {
    auto names = saveMgr_.listSaves();

    std::cout << "### Menu Zapisów ###\n";
    for (size_t i = 0; i < names.size(); ++i) {
        std::cout << "  " << (i+1) << ") " << names[i] << "\n";
    }
    std::cout << "  N) Nowy świat\n"
              << "Wybierz [1-" << names.size() << "] lub N: ";

    char c = std::toupper(static_cast<char>(std::getchar()));
    if (c == 'N' || names.empty()) {
        std::cout << "Podaj nazwę nowego świata: ";
        std::string name;
        std::cin >> name;
        currentSaveName_ = name;
        initWorld();
        std::string fname = name + ".sav";
        saveMgr_.addSave(name, fname);
        saveMgr_.saveWorld(fname, swiat_);
    } else {
        size_t idx = c - '1';
        if (idx < names.size()) {
            currentSaveName_ = names[idx];
            std::string fname = saveMgr_.listSaves().at(idx) + ".sav";
            saveMgr_.loadWorld(fname, swiat_);

            for (auto& org : swiat_.getOrganizmy()) {
                if (auto c = std::dynamic_pointer_cast<Czlowiek>(org)) {
                    player_ = c;
                    break;
                }
            }
        } else {
            std::cerr << "Nieprawidłowy wybór, tworzę nowy świat.\n";
            std::cin.ignore(10000,'\n');
            showSaveMenu();
        }
    }
}

void Game::initWorld() {
    auto place = [&](auto factory){
        int x,y;
        do {
            x = std::rand() % swiat_.getWidth();
            y = std::rand() % swiat_.getHeight();
        } while (swiat_.zwrocOrganizm(x,y));
        swiat_.dodajOrganizm(factory(x,y,swiat_));
    };

    player_ = std::make_shared<Czlowiek>(5, 2, swiat_);
    swiat_.dodajOrganizm(player_);

    for (int i = 0; i < 10; ++i) {
        place([](int x,int y,Swiat& s){ return std::make_shared<Wilk>(x,y,s); });
        place([](int x,int y,Swiat& s){ return std::make_shared<Owca>(x,y,s); });
        place([](int x,int y,Swiat& s){ return std::make_shared<Antylopa>(x,y,s); });
        place([](int x,int y,Swiat& s){ return std::make_shared<Lis>(x,y,s); });
        place([](int x,int y,Swiat& s){ return std::make_shared<Zolw>(x,y,s); });
        place([](int x,int y,Swiat& s){ return std::make_shared<CyberOwca>(x,y,s); });
    }
    for (int i = 0; i < 2; ++i) {
        place([](int x,int y,Swiat& s){ return std::make_shared<Trawa>(x,y,s); });
        place([](int x,int y,Swiat& s){ return std::make_shared<Mlecz>(x,y,s); });
        place([](int x,int y,Swiat& s){ return std::make_shared<Guarana>(x,y,s); });
        place([](int x,int y,Swiat& s){ return std::make_shared<WilczeJagody>(x,y,s); });
    }
    for (int i = 0; i < 6; ++i) {
        place([](int x,int y,Swiat& s){ return std::make_shared<BarszczSosnowskiego>(x,y,s); });
    }
}

void Game::gameLoop() {
    while (true) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        std::ios::sync_with_stdio(0);
        std::cin.tie(0);
        std::cout << "Sterowanie: Strzalki-ruch, E-tarcza, Q-wyjscie\n";
        swiat_.rysujSwiat();


        int key = _getch();
        if (key == 224) {
            key = _getch();
            switch (key) {
                case 72: player_->ustawKierunek(Kierunek::GORA);  break;
                case 80: player_->ustawKierunek(Kierunek::DOL);   break;
                case 75: player_->ustawKierunek(Kierunek::LEWO);  break;
                case 77: player_->ustawKierunek(Kierunek::PRAWO); break;
                default: player_->ustawKierunek(Kierunek::BRAK); break;
            }
        } else {
            key = std::tolower(key);
            if      (key == 'e') player_->aktywujUmiejetnosc();
            else if (key == 'q') {
                // zapis
                saveMgr_.saveWorld(currentSaveName_ + ".sav", swiat_);
                std::cout << "Koniec gry.\n";
                break;
            } else {
                player_->ustawKierunek(Kierunek::BRAK);
            }
        }

        swiat_.wykonajTure();

        #ifdef _WIN32
            Sleep(50);
        #endif
    }
}
