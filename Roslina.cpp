#include "Roslina.h"
#include "Swiat.h"
#include "Zwierze.h"

#include <ctime>

Roslina::Roslina(int x, int y, Swiat& swiat)
     : Organizm(0, 0, x, y, swiat) { }

void Roslina::akcja(Swiat& swiat) {
    // losowa szansa na zasianie
    if ((std::rand() % 100) >= PROB_SIANIA)
        return;

    // wybranie pola do siania
    constexpr int DX[8] = { -1,-1,-1, 0, 0, 1, 1, 1 };
    constexpr int DY[8] = { -1, 0, 1,-1, 1,-1, 0, 1 };
    int i = std::rand() % 8;
    int nx = x_ + DX[i];
    int ny = y_ + DY[i];

    if (!swiat.czyWZakresie(nx, ny))
        return;

    auto occ = swiat.zwrocOrganizm(nx, ny);
    // sprawdzanie czy jest na polu zwierze
    if (occ && std::dynamic_pointer_cast<Zwierze>(occ))
        return;
    if (occ)
        return;

    auto sadzonka = utworzSadzonke(nx, ny);
    swiat.dodajOrganizm(sadzonka);
    swiat.dodajDoLogu(
        std::string("Rozsiala sie roslina na ")
        + std::to_string(nx) + "," + std::to_string(ny)
    );
}

void Roslina::kolizja(const std::shared_ptr<Organizm>& /*inny*/) {
    swiat_.usunOrganizm(shared_from_this());
    swiat_.dodajDoLogu(std::string("Roslina na ")
                      + std::to_string(x_) + "," + std::to_string(y_)
                      + " zostala zjedzona");
}
