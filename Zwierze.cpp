#include "Zwierze.h"
#include "Swiat.h"

#include <vector>
#include <algorithm>
#include <typeinfo>

Zwierze::Zwierze(int sila, int inicjatywa, int x, int y, Swiat& swiat)
     : Organizm(sila, inicjatywa, x, y, swiat) { }

void Zwierze::akcja(Swiat& swiat) {
    // osiem kierunków, losujemy
    std::vector<std::pair<int,int>> dirs = {
        { -1,-1 }, { -1,0 }, { -1,1 },
        {  0,-1 },           {  0,1 },
        {  1,-1 }, {  1,0 }, {  1,1 }
    };
    std::random_shuffle(dirs.begin(), dirs.end());

    for (auto [dx, dy] : dirs) {
        int nx = x_ + dx, ny = y_ + dy;
        if (!swiat.czyWZakresie(nx, ny)) continue;

        auto occupant = swiat.zwrocOrganizm(nx, ny);
        if (!occupant) {
            // ruch na puste pole
            swiat.przesunOrganizm(shared_from_this(), nx, ny);
        } else {
            // walka/rozmnażanie
            kolizja(occupant);
        }
        break;  // tylko jeden ruch/koliduje
    }
}

void Zwierze::kolizja(const std::shared_ptr<Organizm>& inny) {
    // sprawdzanie gatunku czy ten sam
    if (typeid(*inny) == typeid(*this)) {
        // wolne pole obok finder
        auto [px, py] = swiat_.znajdzWolnePoleObok(x_, y_);
        if (px != -1) {
            auto dziecko = utworzPotomka(px, py);
            swiat_.dodajOrganizm(dziecko);
            swiat_.dodajDoLogu(
                std::string("Rozmnozenie: ") +
                std::string(1, rysowanie()) +
                " na " + std::to_string(px) + "," + std::to_string(py)
            );
        }
    } else {
        // wygrywa wieksza sila -> atakuje this
        if (sila_ >= inny->getSila()) {
            swiat_.dodajDoLogu(
                std::string("Walczacy: ") +
                std::string(1, rysowanie()) +
                " zabil " +
                std::string(1, inny->rysowanie()) +
                " na " + std::to_string(inny->getX()) + "," + std::to_string(inny->getY())
            );
            swiat_.usunOrganizm(inny);
            swiat_.przesunOrganizm(shared_from_this(), inny->getX(), inny->getY());
        } else {
            swiat_.dodajDoLogu(
                std::string("Wygral: ") +
                std::string(1, inny->rysowanie()) +
                " zabil " +
                std::string(1, rysowanie()) +
                " na " + std::to_string(x_) + "," + std::to_string(y_)
            );
            swiat_.usunOrganizm(shared_from_this());
        }
    }
}
