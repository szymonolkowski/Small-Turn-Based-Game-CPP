#include "Lis.h"
#include "Swiat.h"

#include <vector>
#include <algorithm>

Lis::Lis(int x, int y, Swiat& swiat)
     : Zwierze(3, 7, x, y, swiat) { }

void Lis::akcja(Swiat& swiat) {
    // lista możliwych kierunków
    std::vector<std::pair<int,int>> dirs = {
        { -1,-1 }, { -1,0 }, { -1,1 },
        {  0,-1 },           {  0,1 },
        {  1,-1 }, {  1,0 }, {  1,1 }
    };
    std::random_shuffle(dirs.begin(), dirs.end());

    for (auto [dx, dy] : dirs) {
        int nx = x_ + dx;
        int ny = y_ + dy;
        if (!swiat.czyWZakresie(nx, ny)) continue;

        auto occupant = swiat.zwrocOrganizm(nx, ny);
        if (occupant) {
            // jeżeli zajęte przez silniejszy → skip
            if (occupant->getSila() > this->getSila()) {
                continue;
            }
            // walka/rozmnażanie z równym lub słabszym
            kolizja(occupant);
        } else {
            // puste pole → ruch
            swiat.przesunOrganizm(shared_from_this(), nx, ny);
        }
        break;  // wykonujemy tylko jedną akcję
    }
}

char Lis::rysowanie() const {
    return 'L';
}

std::shared_ptr<Organizm> Lis::utworzPotomka(int x, int y) {
    return std::make_shared<Lis>(x, y, swiat_);
}
