#include "Mlecz.h"

#include <algorithm>

#include "Swiat.h"
#include <cstdlib>
#include <numeric>
#include <string>

#include "Zwierze.h"

Mlecz::Mlecz(int x, int y, Swiat& swiat)
    : Roslina(x, y, swiat) {}

void Mlecz::akcja(Swiat& swiat) {
    constexpr int DX[8] = { -1,-1,-1, 0, 0, 1, 1, 1 };
    constexpr int DY[8] = { -1, 0, 1,-1, 1,-1, 0, 1 };

    // trzy próby zasiania
    for (int próba = 0; próba < 3; ++próba) {
        if ((std::rand() % 100) >= PROB_SIANIA)
            continue;

        int i = std::rand() % 8;
        int nx = x_ + DX[i];
        int ny = y_ + DY[i];

        if (!swiat.czyWZakresie(nx, ny))
            continue;

        auto occ = swiat.zwrocOrganizm(nx, ny);
        if (occ && std::dynamic_pointer_cast<Zwierze>(occ))
            continue;
        if (occ)
            continue;

        auto sadzonka = utworzSadzonke(nx, ny);
        swiat.dodajOrganizm(sadzonka);
        swiat.dodajDoLogu(
            std::string("Mlecz rozsial sie na ")
            + std::to_string(nx) + "," + std::to_string(ny)
        );
        break;
    }
}

char Mlecz::rysowanie() const {
    return 'm';
}

std::shared_ptr<Organizm> Mlecz::utworzSadzonke(int x, int y) {
    return std::make_shared<Mlecz>(x, y, swiat_);
}
