#include "Zolw.h"
#include "Swiat.h"

#include <cstdlib>

Zolw::Zolw(int x, int y, Swiat& swiat)
    : Zwierze(2, 1, x, y, swiat) {}

void Zolw::akcja(Swiat& swiat) {
    // 25% szans na ruch
    if (std::rand() % 100 < 25) {
        Zwierze::akcja(swiat);
    }
}

void Zolw::kolizja(const std::shared_ptr<Organizm>& inny) {
    if (typeid(*inny) == typeid(*this)) {
        Zwierze::kolizja(inny);
        return;
    }
//odpychanie
    auto zw = dynamic_cast<Zwierze*>(inny.get());
    if (zw && inny->getSila() < 5) {
        auto [px, py] = swiat_.znajdzWolnePoleObok(x_, y_);
        if (px != -1) {
            swiat_.przesunOrganizm(inny, px, py);
            swiat_.dodajDoLogu("Zolw odparl atak zwierzecia o sile <5");
            return;
        }
    }

    Zwierze::kolizja(inny);
}


char Zolw::rysowanie() const {
    return 'Z';
}

std::shared_ptr<Organizm> Zolw::utworzPotomka(int x, int y) {
    return std::make_shared<Zolw>(x, y, swiat_);
}
